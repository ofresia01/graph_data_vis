/*
* Driver for pathfinder application.
*/
#include <iostream>
#include "Grid.h"
#include "Graph.h"
#include "AStar.h"
#include "Dijkstra.h"

int main() {
	// Declare 1024x1024 SFML window at 60 FPS
	sf::RenderWindow window(sf::VideoMode(900, 900), "PATHFINDER");
	window.setFramerateLimit(60);
	while (window.isOpen()) {
		// Declare a grid and graph
		Grid aGrid(1024, 1024, window);
		Graph aGraph(aGrid.getNumberOfSquares());

		// Menu that prompts for desired algorithm, wall coordinates, and start/end coordinates
		char graphChoice;
		int xCoord = 0, yCoord = 0, index = 0;
		std::cout << "\t-----PATHFINDER-----\n";
		std::cout << "Choose pathfinding algorithm ('A' for A*, 'D' for Dijkstra): \n";
		std::cin >> graphChoice;
		std::cout << "Choose coordinates of walls, one integer at a time. (-1 to continue): \n";
		while (xCoord != -1 || yCoord != -1) {
			std::cin >> xCoord >> yCoord;
			aGrid.setWall(sf::Vector2i(xCoord, yCoord));
		}
		std::cout << "Choose coordinates of start position: \n";
		std::cin >> xCoord >> yCoord;
		aGrid.setStart(sf::Vector2i(xCoord, yCoord));
		std::cout << "Choose coordinates of end position: \n";
		std::cin >> xCoord >> yCoord;
		aGrid.setEnd(sf::Vector2i(xCoord, yCoord));
		Position startPosition = aGrid.getStartPosition();
		Position endPosition = aGrid.getEndPosition();
		std::vector<Position> walls = aGrid.getWallPositions();
		aGrid.drawGrid();
		// Instantiate an object of desired algorithm class and display results
		if (graphChoice == 'D') {
			std::cout << "Calculating path using Dijkstra's algorithm...\n";
			Dijkstra dijkstraAlgorithm(aGraph);
			dijkstraAlgorithm.findPath(startPosition, endPosition, walls, aGrid, window);
			dijkstraAlgorithm.loadPath(aGrid);
			aGrid.drawPath();
			window.display();
		}
		if (graphChoice == 'A') {
			std::cout << "Calculating path using A* algorithm...\n";
			AStar aStarAlgorithm(aGraph);
			aStarAlgorithm.findPath(startPosition, endPosition, walls, aGrid, window);
			aStarAlgorithm.loadPath(aGrid);
			aGrid.drawPath();
			window.display();
		}
	}
	return 0;
}