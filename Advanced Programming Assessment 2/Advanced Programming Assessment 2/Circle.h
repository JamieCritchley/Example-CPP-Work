#pragma once
#pragma once
#include "Shape.h"
#include "Movable.h"

/*
* Definition: Represents a movable circle on a graph, with 0,0 in the
* top left. The coordinates are the top left and bottom right points 
* of a square made up of 4 tangents.
* Usage: Used by driver code to allow users to create and manipulate
* a circle. Can be referred to using base class pointers.
*/
class Circle : public Movable, public Shape {
private:
	int radius;

	//pi is also defined in <numbers>, but this is an unnecessary include
	const double pi = 4 * atan(1);

	/*
	* Description: updates area variable with current area, calculated
	* by: pi * r^2 (overriden)
	* Input: void
	* Output: void
	*/
	void calculateArea() final;


	/*
	* Description: updates perimeter variable with current perimeter,
	* calculated by: pi * r * 2 (overriden)
	* Input: void
	* Output: void
	*/
	void calculatePerimeter() final;


	/*
	* Description: updates points vector with current points, the top
	* left and bottom right corners - see class declation comments.
	* Left top variable should already have been updated as it is used 
	* to calculate other points. This class also pushes leftTop to points
	* (overriden).
	* Input: void
	* Output: void
	*/
	void calculatePoints() final;

public:


	/*
	* Description: creates a string containing radius, position of all 
	* points, area and perimeter (overriden)
	* Input: void
	* Output: formatted shape information. Example:
	* Circle[r=50] 
	* Points[(150,280)(250,380)] 
	* Area=7854.0 Perimeter=314.2
	*/
	std::string toString() const;


	/*
	* Description: Moves Circle to new position, and recalculates points
	* (overriden)
	* Input: coordinates of new top left point: x coordinate, y coordinate
	* Output: void
	*/
	void move(int newX, int newY);


	/*
	* Description: Scales Circle to new size, then recalculates points,
	* area, perimeter and radius (overriden)
	* Input: scale factor in x direction, scale factor in y direction
	* Important - input must be validated so that scaleX = scaleY,
	* as circles must be stretched by equal factors in both directions
	* E.g. scale(2,2) stretches the circle by a factor of 2.
	* scale(2,1) would be an invalid input.
	* Output: void
	*/
	void scale(float scaleX, float scaleY);


	/*
	* Description: Constructor, sets radius and coordinates for top 
	* left point. Coordinates are passed to the Shape class constructor.
	* Input: x coordinate, y coordinate, width, height.
	* Output: void (constructor)
	*/
	Circle(int topLeftX, int topLeftY, int Radius);
};