/*
* Header file for the Dijkstra class.
* Implementation of Dijkstra's algorithm for pathfinding using the Graph and Grid class.
*/
#pragma once
#include "Graph.h"
#include "Grid.h"
#include <unordered_set>
#include <list>

class Dijkstra {
public:
	// Constructor for Dijkstra object
	Dijkstra(Graph &);

	// Method that calculates path using Dijkstra's algorithm given starting and ending position, wall positions, a grid, and a render window
	void findPath(const Position &, const Position &, const std::vector<Position> &, Grid &, sf::RenderWindow &);

	// Method that draws path to the grid
	void loadPath(Grid &);
private:
	// Each instance of Dijkstra operates on a Graph object
	Graph &graph;

	// Each instance of Dijkstra needs a start and end position for calculating path
	Position startPosition;
	Position endPosition;
	bool endPositionFound = false; // Flag indicating endPosition reached and cessation of findPath
	
	// Priority queue for storing available vertices, sorted by least to greatest distance to startPosition
	std::list<graphVertex *> priorityQueue;

	// Unordered set which provides quick container for storing all available vertices
	std::unordered_set<graphVertex *> availableVertices;

	// Helper function for findPath that calculates Euclidean distance between two vertices, used for finding more optimal paths when processing vertices
	double vertexDistance(graphVertex *, graphVertex *);
};