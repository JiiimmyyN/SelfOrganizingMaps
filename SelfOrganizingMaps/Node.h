#pragma once
#include <random>
#include <vector>
#include <cassert>
class Node
{
public:
	Node(int numWeights, double x, double y, std::mt19937& randEngine) :
		mX(x), mY(y), mWeightCount(numWeights)
	{
		std::uniform_real_distribution<double> dist(0, 1.0);
		
		for (auto i = 0; i < mWeightCount; i++)
		{
			mWeights.push_back(dist(randEngine));
		}
	}
	~Node()
	{}


	double calculateDistance(const std::vector<double>& w)
	{
		assert(mWeightCount == w.size());

		auto distance = 0.0;
		for (auto i = 0; i < w.size(); i++)
		{
			distance += (w[i] - mWeights[i]) * (w[i] - mWeights[i]);
		}
		return distance;
	}

	double calculateDistance(const Node* n) const
	{
		return ((mX - n->mX) * (mX - n->mX)) + ((mY - n->mY) * (mY - n->mY));
	}

	void adjustWeights(const std::vector<double>& w, double learningRate, double influence)
	{
		assert(mWeightCount == w.size());

		for (auto i = 0; i < mWeights.size(); i++)
		{
			mWeights[i] += learningRate * influence * (w[i] - mWeights[i]);
		}
	}

	std::vector<double> getWeights() const { return mWeights; }
	double x() const { return mX; }
	double y() const { return mY; }
private:
	double		mX, mY;
	int		mWeightCount;
	std::vector<double>	mWeights;

};

