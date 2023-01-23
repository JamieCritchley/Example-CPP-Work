#pragma once
#include "Shape.h"
#include "Movable.h"

/*
* Definition: Represents a movable square on a graph, with 0,0 in the 
* top left
* Usage: Used by driver code to allow users to create and manipulate
* a square. Can be referred to using base class pointers.
*/
class Square : public Movable, public Shape {
private:
	int edge;

	/*
	* Description: updates area variable with current area, calculated
	* by: edge^2 (overriden)
	* Input: void
	* Output: void
	*/
	void calculateArea() final;


	/*
	* Description: updates perimeter variable with current perimeter,
	* calculated by: edge * 4 (overriden)
	* Input: void
	* Output: void
	*/
	void calculatePerimeter() final;


	/*
	* Description: updates points vector with current points, the 4
	* corners, using edge length. leftTop variable should already 
	* have been updated as it is used to calculate other points. This 
	* class also pushes leftTop to points (overriden)
	* Input: void
	* Output: void
	*/
	void calculatePoints() final;

public:


	/*
	* Description: creates a string containing edge length, position of
	* all points, area and perimeter (overriden)
	* Input: void
	* Output: formatted shape information. Example:
	* Square[e=30] 
	* Points[(200,250)(230,250)(230,280)(200,280)] 
    * Area=900.0 Perimeter=120.0 
	*/
	std::string toString() const;


	/*
	* Description: Moves Square to new position, and recalculates points
	* (overriden)
	* Input: coordinates of new top left point: x coordinate, y coordinate
	* Output: void
	*/
	void move(int newX, int newY);


	/*
	* Description: Scales Square to new size, then recalculates points,
	* area, perimeter and edge length (overriden)
	* Input: scale factor in x direction, scale factor in y direction
	* Important - input must be validated so that scaleX = scaleY,
	* as squares must be stretched by equal factors in both directions
	* E.g. scale(2,2) stretches the square by a factor of 2.
	* scale(2,1) would be an invalid input.
	* Output: void
	*/
	void scale(float scaleX, float scaleY);


	/*
	* Description: Constructor, sets edge length and coordinates for top 
	* left point. Coordinates are passed to the Shape class 
	* constructor.
	* Input: x coordinate, y coordinate, edge length.
	* Output: void (constructor)
	*/
	Square(int topLeftX, int topRightX, int Edge);
};