#include "SOM.h"
#include "Node.h"
#include <limits>
SOM::SOM(int height, int width, int numCellsX, int numCellsY, int numIterations) :
	mNumIterations(numIterations)
{
	mCellWidth = width / numCellsX;
	mCellHeight = height / numCellsY;
	
	for (auto i = 0; i < numCellsY; i++)
	{
		for (auto j = 0; j < numCellsX; j++)
		{
			mNodes.push_back(std::make_unique<Node>(3, j*mCellWidth, i*mCellHeight, mRandEngine));
		}
	}

	mRadius = (height + width) / 2;
	mTimeConstant = numCellsX*numCellsY / std::log(mRadius);
}

SOM::~SOM()
{
}

//Initialize weights
//for 0 to num of maxIterations
//w is a randomly selected sample
void SOM::train(int i, const std::vector<double>& w)
{
	mIterationCount = i;
	//Find best matching node
	auto winningNode = findBestMatchingNode(w);
	//Scale neighbours
	scaleNeighbours(winningNode, w);
}

void SOM::draw(sf::RenderWindow& window)
{
	auto rect = sf::RectangleShape(sf::Vector2f(mCellWidth, mCellHeight));

	for (auto i = 0; i < mNodes.size(); i++)
	{
		auto color = sf::Color(255 * mNodes[i]->getWeights()[0], 255 * mNodes[i]->getWeights()[1], 255 * mNodes[i]->getWeights()[2]);
		/*c.r = ;
		c.g = 255 * mNodes[i]->getWeights()[1];
		c.b = 255 * mNodes[i]->getWeights()[2];*/
		rect.setFillColor(color);
		rect.setPosition(mNodes[i]->x(), mNodes[i]->y());
		auto size = rect.getSize();
		window.draw(rect);
	}
}

void SOM::scaleNeighbours(Node* node, const std::vector<double>& w)
{
	auto learningRate = 0.1 * exp(-mIterationCount / mNumIterations);
	auto neighbourhoodRadius = mRadius * exp(-mIterationCount / mTimeConstant);

	for (auto i = 0; i < mNodes.size(); i++)
	{
		auto distToNodeSquared = node->calculateDistance(mNodes[i].get());
		auto widthSquared = neighbourhoodRadius * neighbourhoodRadius;

		if (distToNodeSquared < widthSquared)
		{
			auto influence = exp(-(distToNodeSquared / (2 * widthSquared)));
			mNodes[i]->adjustWeights(w, learningRate, influence);
		}
	}
}

Node* SOM::findBestMatchingNode(const std::vector<double>& w)
{
	Node* best;
	auto shortestDistance = DBL_MAX;

	for (auto i = 0; i < mNodes.size(); i++) 
	{
		auto tmp = mNodes[i]->calculateDistance(w);
		if (tmp < shortestDistance)
		{
			shortestDistance = tmp;
			best = mNodes[i].get();
		}
	}
	return best;
}