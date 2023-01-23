#pragma once
#include "Shape.h"
#include "Movable.h"

/*
* Definition: Represents a movable rectangle on a graph, with 0,0 in 
* the top left
* Usage: Used by driver code to allow users to create and manipulate
* a rectangle. Can be referred to using base class pointers.
*/
class Rectangle : public Movable, public Shape {
private:
	int height;
	int width;


	/*
	* Description: updates area variable with current area, calculated
	* by: h*w (overriden)
	* Input: void
	* Output: void
	*/
	void calculateArea() final;


	/*
	* Description: updates perimeter variable with current perimeter,
	* calculated by: h*2 + w*2 (overriden)
	* Input: void
	* Output: void
	*/
	void calculatePerimeter() final;


	/*
	* Description: updates points vector with current points, the 4
	* corners, using height and width. leftTop variable should already 
	* have been updated as it is used to calculate other points. This 
	* class also pushes leftTop to points (overriden)
	* Input: void
	* Output: void
	*/
	void calculatePoints() final;

public:


	/*
	* Description: creates a string containing height and width,
	* position of all points, area and perimeter (overriden)
	* Input: void
	* Output: formatted shape information. Example:
	* Rectangle[h=50,w=200] 
	* Points[(100,100)(300,100)(300,150)(100,150)] 
	* Area=10000.0 Perimeter=500.0 
	*/
	std::string toString() const;


	/*
	* Description: Moves Rectangle to new position, and recalculates points
	* (overriden)
	* Input: coordinates of new top left point: x coordinate, y coordinate
	* Output: void
	*/
	void move(int newX, int newY);


	/*
	* Description: Scales Rectangle to new size, then recalculates 
	* points, area, perimeter, height and edge (overriden)
	* Input: scale factor in x direction, scale factor in y direction
	* E.g. scale(2,1) stretches the rectangle in the x direction by 2,
	* while the y direction would be unscaled
	* Output: void
	*/
	void scale(float scaleX, float scaleY);


	/*
	* Description: Constructor, sets width and height and coordinates 
	* for top left point. Coordinates are passed to the Shape class 
	* constructor.
	* Input: x coordinate, y coordinate, width, height.
	* Output: void (constructor)
	*/
	Rectangle(int topLeftX, int topLeftY, int Width, int Height);
};