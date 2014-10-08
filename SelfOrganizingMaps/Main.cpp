#include <iostream>
#include <vector>
#include <random>
#include <SFML\Graphics.hpp>
#include "SOM.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");
	
	std::mt19937 randEngine;
	
	//Initialize inputVectors
	std::vector<std::vector<double>> inputVectors = 
	{	{ 1.0, 0.0, 0.0 },
		{ 0.0, 1.0, 0.0 },
		{ 0.0, 0.0, 1.0 },
		{ 1.0, 1.0, 0.0 },
		/*{ 0.0, 0.0, 0.0 },*/
		//{ 1.0, 1.0, 1.0 }
	};
	std::uniform_int_distribution<> dist(0, inputVectors.size()-1);
	//Set size of the map
	auto xCells = 400, yCells = 400;
	auto numIterations = xCells*yCells;
	SOM som(400, 400, xCells, yCells, numIterations);


	int i = 0;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}


		if (i < numIterations)
		{
			som.train(i, inputVectors[dist(randEngine)]);
			i++;
		}
		window.clear();
		som.draw(window);
		
		window.display();
		
	}


	return 0;
}