#pragma once
#include <random>
#include <vector>
class Node
{
public:
	Node(int numWeights, int x, int y):
		mX(x), mY(y), mWeightCount(numWeights)
	{
		std::mt19937 randEngine;
		std::uniform_real_distribution<> dist(0, 1.0);
		
		for (auto i = 0; i < mWeightCount; i++)
		{
			mWeights.push_back(dist(randEngine));
		}
	}
	~Node()
	{}
private:
	int		mX, mY;
	int		mWeightCount;
	std::vector<double>	mWeights;

};

