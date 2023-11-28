/*
* Header file for the Grid class, representing a grid of squares.
* Defines member attributes and methods.
*/
#pragma once
#include <SFML\Graphics.hpp>
#include "Position.h"

class Grid {
public:
	// Constructor method for Grid object
	Grid(int, int, sf::RenderWindow &);

	// Method for drawing grid to SFML window
	void drawGrid();

	// Method for drawing path to SFML window
	void drawPath();

	// Method for defining a wall within grid
	void setWall(sf::Vector2i);

	// Method for explicitly defining ending position
	void setEnd(sf::Vector2i);

	// Method for explicitly defining starting position
	void setStart(sf::Vector2i);

	// Method for coloring a processed square (for use with Dijkstra's or A*)
	void colorProcessedSquare(const Position &);

	// Method for coloring a processing square (for use with Dijkstra's or A*)
	void colorProcessingSquare(const Position &);

	// Method for loading tiles within computed path to path vector
	void loadPath(const Position &, const Position &);

	// Accessor method for walls vector
	std::vector<Position> getWallPositions() const;

	// Accessor method for number of squares horizontally and vertically, returned as an int 2-tuple
	std::tuple<int, int> getNumberOfSquares() const;

	// Accessor method for endPosition
	Position getEndPosition() const;

	// Accessor method for startPosition
	Position getStartPosition() const;

private:
	// Vector storing squares for grid
	std::vector<sf::RectangleShape> squares;

	// Vector storing positions of walls
	std::vector<Position> walls;

	// Vector containing SFML vertex representations of a computed path
	std::vector<sf::Vertex> pathVertices;

	// Window for grid to be drawn to
	sf::RenderWindow& window;

	// Variables defining resolution of SFML window
	int windowWidth;
	int windowHeight;

	// Variables defining number of tiles, horizontal and vertical
	int xTiles;
	int yTiles;							

	// Variables defining the source square and target square
	Position startPosition;
	Position endPosition;

	// Variables defining colors of squares in all possible states
	sf::Color freeColor = sf::Color::White;
	sf::Color wallColor = sf::Color::Black;
	sf::Color startColor = sf::Color::Green;
	sf::Color endColor = sf::Color::Red;
	sf::Color processedColor = sf::Color::Cyan;
	sf::Color processingColor = sf::Color::Blue;

	// Helper function for setEnd method
	void updateEnd(const Position &);

	// Helper function for setStart method
	void updateStart(const Position &);

	// Helper function for accessing square color at given position
	sf::Color getSquareColor(const Position &) const;

	// Helper function for mutating square color at given position with given color
	void setSquareColor(const Position &, const sf::Color &);

	// Helper function for determining if coordinates are within bounds of grid
	bool outofBounds(int x, int y);
};