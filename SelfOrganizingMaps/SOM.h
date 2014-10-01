#pragma once
#include <vector>
#include <memory>
class Node;

class SOM
{
public:
	SOM(int height, int width, int numCellsX, int numCellsY, int numIterations);
	~SOM();
private:
	std::vector<std::unique_ptr<Node>> mNodes;
};

