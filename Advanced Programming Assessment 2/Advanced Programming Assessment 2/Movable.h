#pragma once

/*
* Description: Interface for classes that can be moved and scaled on a graph
* Usage: Currently used for shapes to move and scale on a graph.
* Can be used as a polymorphic base class
*/
class Movable {
protected:

	/*
	* Copy/move constructors/assignemnet operators are
	* deleted to prevent accidental slicing using base class
	* pointers. They are deleted instead of protected as this class
	* contains no data for a subclass to copy/move. This is specified 
	* in the C++ Core Guidlines in section  "C.67: A polymorphic 
	* class should surpress public copy/move".
	*/
	Movable(const Movable&) = delete;
	Movable& operator=(const Movable&) = delete;
	Movable(Movable&&) = delete;
	Movable& operator=(Movable&&) = delete;


	/*
	* Note: The constructor is protected as abstract classes should only be
	* instantiated by subclasses. This is in accordance with the
	* Microsoft .NET documentation: "CA1012: Abstract types should
	* not have public constructors"
	*/
	Movable() = default;
	

public:


	/*
	* Description: Moves shape to new position on a graph (pure virtual)
	* Input: coordinates of new top left point:
	* x coordinate, y coordinate
	* Output: void
	*/
	virtual void move(int newX, int newY) = 0;


	/*
	* Description: Scales shape to new size (pure virtual)
	* Input: scale factor in x direction, scale factor in y direction
	* E.g. scale(2,1) stretches in the x direction by factor of 2,
	* while y is not scaled
	* Output: void
	*/
	virtual void scale(float scaleX, float scaleY) = 0;


	/*
	* Description: Default virtual destructor, necessary to use base 
	* class pointers
	* Input: void (destructor)
	* Output: void (destructor)
	*/
	virtual ~Movable() = default;

};