/*
* Implementation file for the Astar class.
* Implements Astar algorithm for pathfinding. Used with Graph and Grid classes.
*/
#include "AStar.h"
#include <iostream>

// Constructor for Astar object
AStar::AStar(Graph& graph) : graph(graph) {}

// Method that calculates path using Astar algorithm given start and end position, walls, a grid, and an SFML render window
void AStar::findPath(const Position &aStartPosition, const Position &anEndPosition, const std::vector<Position> &theWalls, Grid &aGrid, sf::RenderWindow &aWindow) {
	// Define start and end positions of this instance
	startPosition = aStartPosition;
	endPosition = anEndPosition;

	// Instantiate the wall flag for each wall
	for (const auto& wall : theWalls) {
		graph.getVertex(wall).isWall = true;
	}

	// Small function for comparing totalDistance (startToVertex + vertexToEnd distances) between two vertices, determines cheaper route
	auto totalDistanceComparison = [](graphVertex *leftVertex, graphVertex *rightVertex) // Auto used as this is for sorting, not boolean
	{
		return leftVertex->totalDistance < rightVertex->totalDistance;
	};

	// Define starting and ending squares as vertices
	graphVertex* startingVertex = &(graph.getVertex(startPosition));
	startingVertex->startToVertexDistance = 0; // This is starting vertex to startToVertexDistance is 0
	graphVertex* endingVertex = &(graph.getVertex(endPosition));
	startingVertex->vertexToEndDistance = vertexDistance(startingVertex, endingVertex); // Define distance from start to end

	// Start Astar algorithm by pushing startingVertex to the priority queue
	priorityQueue.emplace_back(startingVertex);

	// Iterate while priority queue is not empty, indicating potential vertices to process, or until endPosition is found
	while (!priorityQueue.empty() && !endPositionFound) {
		priorityQueue.sort(totalDistanceComparison); // Sort vertices within priority queue by their total distance

		// Copy cheapest vertex from priority queue, then pop it and color it accordingly in aGrid
		graphVertex *currentVertex = priorityQueue.front();
		priorityQueue.pop_front();
		currentVertex->processedVertex = true;
		aGrid.colorProcessedSquare(currentVertex->vertexPosition);

		// Check if currentVertex is at endPosition
		if (currentVertex->vertexPosition == endPosition) {
			endPositionFound = true; // Exit condition
		}
		
		// Update grid representation
		aGrid.drawGrid();
		aWindow.display();

		// Iterate through neighboring vertices
		for (auto& neighbor : currentVertex->neighboringVertices) {
			// If neighbor is already processed or a wall, skip iteration
			if (neighbor->processedVertex || neighbor->isWall) {
				continue;
			}
			else {
				// Define approximate startToVertexDistance for neighboringVertex by adding startToVertexDistance from currentVertex and Euclidean distance from currentVertex to neighbor
				double approxStartToVertexDistance = currentVertex->startToVertexDistance + vertexDistance(currentVertex, neighbor);
				
				// This condition indicates a more optimal path exists from startingVertex to the neighbor
				if (approxStartToVertexDistance < neighbor->startToVertexDistance) {
					neighbor->parent = currentVertex; // For loading the path
					// Update heuristics
					neighbor->startToVertexDistance = approxStartToVertexDistance;
					neighbor->vertexToEndDistance = vertexDistance(neighbor, endingVertex); // Using Euclidean distance calculation
					neighbor->totalDistance = neighbor->startToVertexDistance + neighbor->vertexToEndDistance;
					
					// Find neighbor in neighboringVertices of currentVertex
					auto find = neighboringVertices.find(neighbor);

					// Verify that neighbor is within neighboringVertices of currentVertex
					if (find == neighboringVertices.end()) {
						// Indicate this neighbor is being processed in grid representation and add it to priority queue and neighboringVertices
						aGrid.colorProcessingSquare(neighbor->vertexPosition);
						priorityQueue.emplace_back(neighbor);
						neighboringVertices.insert(neighbor);
					}
				}
			}
		}
	}
}

// Method that adds path to aGrid's path vector
void AStar::loadPath(Grid &aGrid) {
	// Define vertex to traverse grid, instantiated at endPosition
	graphVertex* traversingVertex = &graph.getVertex(endPosition);

	// Check for empty vertex at endPosition
	if (traversingVertex != nullptr) {
		// Iterate through vertices' parents, starting at end position
		while (traversingVertex->parent != nullptr) {
			// Load the path from current vertex to its parent in each iteration, indicating path found by Astar
			aGrid.loadPath(traversingVertex->vertexPosition, traversingVertex->parent->vertexPosition);
			traversingVertex = traversingVertex->parent;
		}
	}
}

// Method that calculates Euclidean distance between two vertices
double AStar::vertexDistance(graphVertex *leftVertex, graphVertex *rightVertex) {
	// Calculate differentials
	int dx = (leftVertex->vertexPosition.xPosition - rightVertex->vertexPosition.xPosition);
	int dy = (leftVertex->vertexPosition.yPosition - rightVertex->vertexPosition.yPosition);

	// Return Euclidean distance
	return sqrt((dx * dx) + (dy * dy));	
}