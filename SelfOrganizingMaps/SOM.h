#pragma once
#include <SFML\Graphics.hpp>
#include <random>
#include <vector>
#include <memory>
class Node;

class SOM
{
public:
	SOM(int height, int width, int numCellsX, int numCellsY, int numIterations);
	~SOM();
	void train(int i, const std::vector<double>& w);
	void draw(sf::RenderWindow& window);
private:
	Node* findBestMatchingNode(const std::vector<double>& w);
	void scaleNeighbours(Node* node, const std::vector<double>& w);

	std::vector<std::unique_ptr<Node>> mNodes;
	float mTimeConstant;
	float mRadius;
	double mCellWidth, mCellHeight;
	int mCellsX, mCellsY;
	int mIterationCount, mNumIterations;

	std::mt19937 mRandEngine;
};

