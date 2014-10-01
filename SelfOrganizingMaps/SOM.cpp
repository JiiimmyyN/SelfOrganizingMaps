#include "SOM.h"
#include "Node.h"

SOM::SOM(int height, int width, int numCellsX, int numCellsY, int numIterations)
{
	for (auto i = 0; i < numCellsY; i++)
	{
		for (auto j = 0; j < numCellsX; i++)
		{
			mNodes.push_back(std::make_unique<Node>(3, j, i));
		}
	}
}


SOM::~SOM()
{
}
