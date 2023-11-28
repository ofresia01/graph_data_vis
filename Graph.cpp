/*
* Implementation file for the Graph class, representation of the grid for use with Dijkstra's or Astar.
* Implementation of all methods.
*/
#include "Graph.h"
#include <tuple>
#include <iostream>

// Constructor method for Graph object
Graph::Graph(std::tuple<int, int> numSquares) {
	// Assign values of 2-tuple numSquares to corresponding x and yVertices variables
	this->xVertices = std::get<0>(numSquares);
	this->yVertices = std::get<1>(numSquares);

	// Given number of horizontal and vertical vertices, add vertices to vertices vector
	for (int i = 0; i < xVertices; i++) {
		for (int j = 0; j < yVertices; j++) {
			vertices.emplace_back(i, j);
		}
	}

	// Check for neighbors and add them to neighboringVertices vector
	for (int x = 0; x < xVertices; x++) {
		for (int y = 0; y < yVertices; y++) {

			if (y > 0)
				vertices[x * xVertices + y].neighboringVertices.emplace_back(&vertices[x * xVertices + (y - 1)]);
			if (y < xVertices - 1)
				vertices[x * xVertices + y].neighboringVertices.emplace_back(&vertices[x * xVertices + (y + 1)]);
			if (x > 0)
				vertices[x * xVertices + y].neighboringVertices.emplace_back(&vertices[(x - 1) * xVertices + y]);
			if (x < xVertices - 1)
				vertices[x * xVertices + y].neighboringVertices.emplace_back(&vertices[(x + 1) * xVertices + y]);


			if (y > 0 && x > 0)
				vertices[x * xVertices + y].neighboringVertices.emplace_back(&vertices[(x - 1) * xVertices + (y - 1)]);
			if (y < xVertices - 1 && x > 0)
				vertices[x * xVertices + y].neighboringVertices.emplace_back(&vertices[(x - 1) * xVertices + (y + 1)]);
			if (y > 0 && x < xVertices - 1)
				vertices[x * xVertices + y].neighboringVertices.emplace_back(&vertices[(x + 1) * xVertices + (y - 1)]);
			if (y < xVertices - 1 && x < xVertices - 1)
				vertices[x * xVertices + y].neighboringVertices.emplace_back(&vertices[(x + 1) * xVertices + (y + 1)]);
		}
	}
}

// Accessor method for getting vertex at given position
graphVertex & Graph::getVertex(const Position& aPosition) {
	return vertices[aPosition.xPosition * xVertices + aPosition.yPosition];
}