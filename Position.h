/*
* Defines a Position struct.
* Used for defining and comparing (x, y) pairs.
*/
#pragma once
struct Position {
	int xPosition;
	int yPosition;
	
	// Returns true if positions are the same.
	bool operator==(const Position& aPosition) const {
		return xPosition == aPosition.xPosition && yPosition == aPosition.yPosition;
	}
};