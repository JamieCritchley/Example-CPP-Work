#pragma once
#include "Point.h"
#include <vector>
#include <string>
#include <ostream>

/*
* Definition: Abstract class to represent a Shape on a graph, 
  with 0,0 in the top left
* Usage: Inheritted by shapes. Methods relating to calculations and 
* output are pure virtual. Can be used as a polymorphic base class. 
*/
class Shape {

//Note: private virtual functions can still be overriden. As these are helper 
//functions, they can stay private
private:


	/*
	* Description: updates area variable with current area (pure virtual)
	* Input: void
	* Output: void
	*/
	virtual void calculateArea() = 0;


	/*
	* Description: upodates perimeter variable with current perimeter
	* (pure virtual)
	* Input: void
	* Output: void
	*/
	virtual void calculatePerimeter() = 0;


	/*
	* Description: updates points vector with current points (pure
	* virtual)
	* Input: void
	* Output: void
	*/
	virtual void calculatePoints() = 0;


protected:

	float area;
	float perimeter;
	bool isCircular;
	bool isEquilateral;

	//Represents the coordinate in the top left
	Point leftTop;


	/*
	* Represents all the vertices that make up the shape.
	* For circular objects, this is the top left and bottom right 
	* corner of a square or rectangle made up of 4 tangents.
	*/
	std::vector<Point> points;


	/*
	* Description: checks if a new topLeft coordinate is valid
	* Default implementation for defending against broken input
	* validation
	* Input: top left coordinates
	* Output: true if valid coordinate points, false if not
	*/
	bool checkTopLeft(int topLeftX, int topLeftY);

	/*
	* Description: checks if a new topLeft coordinate is valid
	* Overriden to allow a custom message to output. Used when complex 
	* manipulations affect topLeft, not allowing it to be validated
	* on recieving input
	* Input: top left coordinates, custom message
	* Output: true if valid coordinate points, false if not
	*/
	bool checkTopLeft(int topLeftX, int topLeftY, std::string consoleMessage);


	/*
	* Copy/move constructors/assignemnet operators are
	* protected to prevent accidental slicing using base class
	* pointers. They are protected instead of deleted as this class
	* contains data which may need to be copied/moved by its subclass.
	* This is specified in the C++ Core Guidlines in section 
	* "C.67: A polymorphic class should surpress public copy/move".
	*/
	Shape(const Shape&) = default;
	Shape& operator= (const Shape&) = default;
	Shape(Shape&&) = default;
	Shape& operator= (Shape&&) = default;


	/*
	* Note: The constructor is protected as abstract classes should 
	* only be  instantiated by subclasses. This is in accordance with 
	* the Microsoft .NET documentation: "CA1012: Abstract types 
	* should not have public constructors"
	* 
	* Description: Constructor, sets coordinates for top left point.
	* These are set in the constructor of the subclass using the
	* initialiser list. Overwrites topLeft to 0,0if negative starting 
	* coordinates are given - this should be handled with input validation 
	* before class use however
	* Input: x coordinate, y coordinate.
	* Output: void (constructor)
	*/
	Shape(int topLeftX, int topLeftY);

public:


	/*
	* Description: creates a string containing shape type, position of
	* all points, area and perimeter (pure virtual)
	* Input: void
	* Output: formatted shape information
	*/
	virtual std::string toString() const = 0;



	/*
	* Description: Default virtual Destructor, necessary to use base 
	* class pointers
	* Input: void (destructor)
	* Output: void (destructor)
	*/
	virtual ~Shape() = default;

	/*
	* Description: Basic getter for isCircular
	* Input: void
	* Output: true if circular, false if not
	*/
	bool checkIfCircular();

	/*
	* Description: Basic getter for isEquilateral
	* Input: void
	* Output: true if equilateral, false if not
	*/
	bool checkIfEquilateral();
};

/*
* Solution insipred by https://learn.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=msvc-170
* Understanding of difference to regular binary overload shown in function comment
* 
* Description: Overloading left shift operator to call toString on a shape
* class. As the left most operand is not Shape, it cannot be defined as a member
* function. It is unneccesary to define a friend function, as toString is 
* public already.
* Input: ostream (cout), shape
* Output: reference to original ostream operator
*/
std::ostream& operator<<(std::ostream& out, Shape* shape);