/*
* Header file for the Graph class, representation of Grid for use with Dijkstra's and Astar.
* Defines member attributes and methods.
*/
#pragma once
#include "Position.h"
#include <vector>

// Defines a Vertex struct, used for computations in Dijkstra's and Astar
struct graphVertex {
	// Constructor for Vertex struct
	graphVertex(int xPosition, int yPosition) : vertexPosition({ xPosition,yPosition }) {}

	// Position of a vertex within corresponding Grid
	Position vertexPosition;

	// Pointer to a vertex's parent
	graphVertex* parent = nullptr;

	// Flag indicating whether vertex is processed or not
	bool processedVertex = false;

	// Flag indicating whether vertex is wall or not
	bool isWall = false;

	// Heuristics determining various distances
	double vertexToEndDistance = INFINITY;
	double startToVertexDistance = INFINITY;
	double totalDistance = INFINITY; // Represents distance from start to end, used in Astar

	// Vector containing pointers to all neighboring vertices
	std::vector<graphVertex*> neighboringVertices;
};

class Graph {
private:
	// Vector containing all vertices within the graph/grid
	std::vector<graphVertex> vertices;

	// Member variables containing number of horizontal and vertical vertices/squares
	int xVertices;
	int yVertices;
public:
	// Constructor method for Graph object
	Graph(std::tuple<int, int>);

	// Accessor method for getting vertex at given position
	graphVertex & getVertex(const Position &);

	// Method for resetting graph
	void resetGraph();
};