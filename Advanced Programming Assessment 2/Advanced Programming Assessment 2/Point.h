#pragma once

/*
* Definition: Represents a coordinate
* Usage: Used by shapes to represent their vertices. If different
* coordinates are wanted, create a new Point
*/
class Point {
private:
	int x;
	int y;

public:
	/*
	* Description: Constructor, sets coordinates
	* Input: x coordinate, y coordinate
	* Output: void (constructor)
	*/
	Point(int X, int Y);
	
	/*
	* Description: Getter for X coordinate
	* Input: void
	* Output: X coordinate 
	*/
	int getXCoord();

	/*
	* Description: Getter for Y coordinate
	* Input: void
	* Output: Y coordinate
	*/
	int getYCoord();
};