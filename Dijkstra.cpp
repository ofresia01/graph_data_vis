/*
* Implementation file for the Dijkstra class.
* Implements Dijkstra's algorithm for pathfinding. Used with Graph and Grid class.
*/
#include "Dijkstra.h"
#include <iostream>

// Constructor for Dijkstra object
Dijkstra::Dijkstra(Graph& graph) : graph(graph) {}

// Calculate path using Dijkstra's algorithm given starting and ending position, wall positions, a grid, and a render window
void Dijkstra::findPath(const Position &aStartPosition, const Position& anEndPosition, const std::vector<Position>& theWalls, Grid& aGrid, sf::RenderWindow& aWindow) {
	// Define start and end positions for this object
	startPosition = aStartPosition;
	endPosition = anEndPosition;

	// Instantiate walls within Graph
	for (const auto& wall : theWalls) {
		graph.getVertex(wall).isWall = true;
	}

	// Determine cheaper route
	auto startToVertexDistanceComparison = [](graphVertex *leftVertex, graphVertex *rightVertex) {
		return leftVertex->startToVertexDistance < rightVertex->startToVertexDistance;
	};

	// Define starting and ending squares as vertices
	graphVertex* startVertex = &(graph.getVertex(startPosition));
	startVertex->startToVertexDistance = 0; // This is starting vertex so distance is 0
	graphVertex* endVertex = &(graph.getVertex(endPosition));

	// Start Dijkstra's algorithm by pushing startVertex to priority queue
	priorityQueue.emplace_back(startVertex);

	// Iterate while priority queue is not empty, indicating potential vertices to process, or until endPosition is found
	while (!priorityQueue.empty() && !endPositionFound) {
		priorityQueue.sort(startToVertexDistanceComparison); // Sort vertices within queue by their startToVertexDistance

		// Copy cheapestVertex from priorityQueue, then pop it from the queue
		graphVertex* currentVertex = priorityQueue.front();
		priorityQueue.pop_front();

		// This vertex has now been processed, color it as such within grid
		currentVertex->processedVertex = true;
		aGrid.colorProcessedSquare(currentVertex->vertexPosition);

		// Check if currentVertex is at endPosition
		if (currentVertex->vertexPosition == endPosition) {
			endPositionFound = true; // Exit condition
		}

		// Draw Grid object to render window for this instance of computation
		aGrid.drawGrid();
		aWindow.display();

		// Iterate through currentVertex's neighboringVertices
		for (auto& neighbor : currentVertex->neighboringVertices) {
			// If neighbor already processed or wall, skip this iteration
			if (neighbor->processedVertex || neighbor->isWall) {
				continue;
			}
			else {
				double approxStartToVertexDistance = currentVertex->startToVertexDistance + vertexDistance(currentVertex, neighbor); // Euclidean distance from currentVertex to neighbor
				// Conditional that indicates more optimal path from startPosition to neighbor
				if (approxStartToVertexDistance < neighbor->startToVertexDistance) {
					neighbor->parent = currentVertex; // A vertex's parent is the cheapest vertex to reach it
					neighbor->startToVertexDistance = approxStartToVertexDistance;

					// Find neighbor in neighboringVertices of current Vertex
					auto find = availableVertices.find(neighbor);
					
					// Conditional that indicates neighbor was not found in availableVertices
					if (find == availableVertices.end()) {
						// Indicate node is being processed
						aGrid.colorProcessingSquare(neighbor->vertexPosition);

						// Add neighbor to priority queue and availableVertices
						priorityQueue.emplace_back(neighbor);
						availableVertices.insert(neighbor);
					}
				}
			}
		}
	}
	return;
}

// Method that adds path to aGrid's path vector
void Dijkstra::loadPath(Grid& aGrid) {
	// Define vertex to traverse grid, instantiated at endPosition
	graphVertex* traversingVertex = &graph.getVertex(endPosition);

	// Check for empty vertex at endPosition
	if (traversingVertex != nullptr) {
		// Iterate through vertices' parents, starting at end position
		while (traversingVertex->parent != nullptr) {
			// Color the path from current vertex to its parent in each iteration, indicating path found by Dijkstra's
			aGrid.loadPath(traversingVertex->vertexPosition, traversingVertex->parent->vertexPosition);
			traversingVertex = traversingVertex->parent;
		}
	}
}

// Method that calculates Euclidean distance between two vertices
double Dijkstra::vertexDistance(graphVertex *leftVertex, graphVertex *rightVertex) {
	// Calculate differentials of x and y coordinates
	int dx = (leftVertex->vertexPosition.xPosition - rightVertex->vertexPosition.xPosition);
	int dy = (leftVertex->vertexPosition.yPosition - rightVertex->vertexPosition.yPosition);

	// Return Euclidean distance
	return sqrt((dx * dx) + (dy * dy));
}