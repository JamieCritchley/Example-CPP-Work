#include "Shape.h"
#include <iostream>

bool Shape::checkTopLeft(int topLeftX, int topLeftY) {
	if (topLeftX < 0 || topLeftY < 0) {
		std::cout << "Error: input validation failed, attempt to create shape with negative "
			"coordinates. Top Left coordinate set to 0,0." << std::endl;
		return false;
	}
	else {
		return true;
	}
}

bool Shape::checkTopLeft(int topLeftX, int topLeftY, std::string consoleMessage) {
	if (topLeftX < 0 || topLeftY < 0) {
		std::cout << consoleMessage << std::endl;
		return false;
	}
	else {
		return true;
	}
}

bool Shape::checkIfCircular() {
	return isCircular;
}
bool Shape::checkIfEquilateral() {
	return isEquilateral;
}


Shape::Shape(int topLeftX, int topLeftY)
	: leftTop(topLeftX, topLeftY) {
	
	//Placeholder values that subclass will overwrite
	area = 0;
	perimeter = 0;

	//Negative coordinate check - if this is used, input validation has failed
	if (!checkTopLeft(topLeftX, topLeftY)) {
		leftTop = Point(0, 0);
	}
	//Only currently known point
	points.push_back(leftTop);

	//Set to false by default, set to true when constructing circular object
	isCircular = false;

	//Set to false by default, set to true when constructing equilateral object
	isEquilateral = false;
}


std::ostream& operator<<(std::ostream& out, Shape* shape) {
	out << shape->toString();
	return out;
}
