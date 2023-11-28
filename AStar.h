/*
* Header file for the Astar class.
* Implementation of the Astar algorithm for use with the Grid and Graph class.
*/
#pragma once
#include "Graph.h"
#include "Grid.h"
#include <unordered_set>
#include <list>

class AStar {
public:
	// Constructor for Astar object
	AStar(Graph &);

	// Method that calculates path using Astar algorithm given start and end position, walls, a grid, and an SFML render window
	void findPath(const Position &, const Position &, const std::vector<Position> &, Grid &, sf::RenderWindow &);

	// Assigns the shortest path to the pathVertices vector within Grid
	void loadPath(Grid &);

private:
	// Each instance of Astar must have to graph to operate upon
	Graph &graph;

	// Astar must have access to start and end positions to calculate path
	Position startPosition;
	Position endPosition;
	bool endPositionFound = false; // Flag indicating endPosition reached and cessation of findPath

	// Priority queue for storing available vertices, sorted by least to greatest distance to startPosition
	std::list<graphVertex *> priorityQueue;

	// Unordered set which provides quick container for storing all neighboring vertices
	std::unordered_set<graphVertex *> neighboringVertices;

	// Helper function for findPath that calculates Euclidean distance between two vertices, used for finding more optimal paths when processing vertices
	double vertexDistance(graphVertex *, graphVertex *);
};