#pragma once
#include <vector>
#include <iostream>
#include <string>

/*
* Definition: Namespace to hold collection of related non-memeber functions:
* all relating to validating user input
* Usage: Currently used by driver code to validate user input. Note that other
* classes have input validation checks, but usually these are only signs that the 
* code resposnisible for input (driver.cpp in this case) has failed
*/
namespace inputValidation {


	/*
	* Description: checks if a user's index input to a vector is in range.
	* This is the default version with a general error message, it is overloaded below
	* Input: user index, vector(any type)
	* Output: true if valid index, false if not
	*/
	template<typename T> 
	bool checkIndex(int i, std::vector<T> v) {
		if (i <= v.size() && i > 0) {
			return true;
		}
		else {
			std::cout << "Invalid input: index does not exist.";
			return false;
		}
	}


	/*
	* Description: checks if a user's index input to a vector is in range.
	* This is the overloaded version to allow a custom error message to be passed
	* Input: user index, vector(any type), custom error message
	* Output: true if valid index, false if not
	*/
	template<typename T>
	bool checkIndex(int i, std::vector<T> v, std::string errorMessage) {
		if (i <= v.size() && i > 0) {
			return true;
		}
		else {
			std::cout << errorMessage;
			return false;
		}
	}


	/*
	* Description: checks if a user's topLeft coordinate input is valid (doesn't contain negative values).
	* Note a similar function also appears in the shape class as a precaution against this input validation not
	* being used.
	* Input: void
	* Output: true if valid coordinate points, false if not
	*/
	bool checkTopLeft(int topLeftX, int topLeftY);

	/*
	* Description: checks if a user's shape attributes are valid (doesn't contain negative values).
	* This is the default version for shapes with only 1 attribute (squares with edges, circles with radius)
	* which is overriden below.
	* Input: attribute
	* Output: true if valid attribute, false if not
	*/
	bool checkAttributes(int attribute);

	/*
	* Description: checks if a user's shape attributes are valid (doesn't contain negative values).
	* This is an overriden version for shapes with 2 attributes (rectangles with width and height)
	* which is overriden below.
	* Input: attribute
	* Output: true if valid attribute, false if not
	*/
	bool checkAttributes(int attribute, int attribute1);

	/*
	* Description: generates error message for for incorrectly formatted input when 
	* creating shape: makes driver code more readable with less repetition
	* Input: shape name, shape attributes (e.g. "edge length", "height and width", "radius")
	* Output: full error message specific for shape
	*/
	std::string getShapeFormatError(std::string shapeName, std::string shapeAttributes);


	/*
	* Description: generates error message for for incorrectly formatted input when
	* moving shape: makes driver code more readable with less repetition
	* Input: move operation (e.g. "move", "scale"), moveParameters (e.g. "new topLeft", "scale X and ScaleY")
	* Output: full error message specific for move operation
	*/
	std::string getMovableFormatError(std::string operation, std::string moveParams);

	/*
	* Description: allows input instructions to be output multiple times in driver without repetitive, long code
	* Input: void
	* Output: void
	*/
	void printInstructions();
}