#include "Circle.h"
#include <sstream>
#include <iomanip>
#include <iostream>

void Circle::calculateArea() {
	area = pi * radius * radius;
}

void Circle::calculatePerimeter() {
	perimeter = pi * radius * 2;
}


void Circle::calculatePoints() {
	//All points are recalculated and created as new Point objects
	points.clear();

	//Left top is already updated, other points are calculated relative to it
	points.push_back(leftTop);
	int leftTopX = leftTop.getXCoord();
	int leftTopY = leftTop.getYCoord();

	Point rightBottom(leftTopX + 2 * radius, leftTopY + 2 * radius);
	points.push_back(rightBottom);
}


std::string Circle::toString() const{

	std::ostringstream out;

	out << "Circle[r=" << radius << "]\nPoints[";

	for (Point currentPoint : points) {
		out << "(" << currentPoint.getXCoord() << "," <<
			currentPoint.getYCoord() << ")";
	}
	//float outputs are rounded to 1.d.p.
	out << std::fixed << std::setprecision(1) << "]\nArea=" << area
		<< " Perimeter=" << perimeter;

	return out.str();
}


void Circle::move(int newX, int newY) {
	if (checkTopLeft(newX, newY)) {
		leftTop = Point(newX, newY);
		calculatePoints();
	}
	
}


void Circle::scale(float scaleX, float scaleY) {

	int leftTopX = leftTop.getXCoord();
	int leftTopY = leftTop.getYCoord();

	//If scaleX != scaleY then input validation has failed. To ensure
	//this class does not become unstable if this happens, leftTopY 
	//is scaled using scaleX.
	if (scaleX != scaleY) {
		std::cout << "Error: input validation failed, attempt to scale "
			"circle by unequal factors. X scale factor will be used for "
			"Y direction." << std::endl;
	}

	//Scale directly affects diameter, so radius is calculated from it
	radius = abs((radius * 2 * scaleX) / 2);

	//If the scale is negative, the top left coordinate moves
	if (scaleX < 0) {
		leftTopX -= 2 * radius;
		leftTopY -= 2 * radius;
	}
	
	//Top left coorindate is set to 0,0 if it would be negative, otherwise normally updated
	if (!checkTopLeft(leftTopX, leftTopY, "Scale would move shape to negative coordinate. "
		"Top left point set to 0, 0, scale applied from there.")) {
		leftTop = Point(0, 0);
	}

	else {
		leftTop = Point(leftTopX, leftTopY);
	}

	calculatePoints();
	calculateArea();
	calculatePerimeter();

}


Circle::Circle(int topLeftX, int topLeftY, int Radius)
	: Shape(topLeftX, topLeftY) {

	//isCircular overwritten from default of false
	isCircular = true;

	//Radius should be checked by input validation, but absolute value
	//used to prevent object becoming unstable if input validation fails
	radius = abs(Radius);


	/*
	* Important - calling a virtual function in a constructor is often
	* a bad idea. Because derived classes have not been constructed
	* yet, if a derived class contains an overriden version of the
	* virtual function, it will not be called. This can result in
	* unexpected behaviour. However, it is unlikely that any derived
	* class of a circle would want to override functions to calculate
	* area, perimeter, or points - the caluclate function declarations
	* are marked final to enforce this. Therefore, this is an exception
	* to the general rule.
	*/
	calculateArea();
	calculatePerimeter();
	calculatePoints();
};