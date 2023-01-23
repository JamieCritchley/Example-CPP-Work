#include "Square.h"
#include <sstream>
#include <iostream>
#include <iomanip>

void Square::calculateArea(){
	area = edge * edge;
}


void Square::calculatePerimeter() {
	perimeter = edge * 4;
}


void Square::calculatePoints() {
	//All points are recalculated and created as new Point objects
	points.clear();

	//Left top is already updated, other points are calculated relative to it
	points.push_back(leftTop);
	int leftTopX = leftTop.getXCoord();
	int leftTopY = leftTop.getYCoord();

	Point rightTop(leftTopX + edge, leftTopY);
	points.push_back(rightTop);

	Point rightBottom(leftTopX + edge, leftTopY + edge);
	points.push_back(rightBottom);

	Point leftBottom(leftTopX, leftTopY + edge);
	points.push_back(leftBottom);
	
}


std::string Square::toString() const{

	std::ostringstream out;

	out << "Square[e=" << edge << "]\nPoints[";

	for (Point currentPoint : points) {
		out << "(" << currentPoint.getXCoord() << "," <<
			currentPoint.getYCoord() << ")";
	}
	//float outputs are rounded to 1.d.p.
	out << std::fixed << std::setprecision(1) << "]\nArea=" << area 
		<< " Perimeter=" << perimeter;

	return out.str();
}


void Square::move(int newX, int newY) {
	if (checkTopLeft(newX, newY)) {
		leftTop = Point(newX, newY);
		calculatePoints();
	}
	
}


void Square::scale(float scaleX, float scaleY) {

	int leftTopX = leftTop.getXCoord();
	int leftTopY = leftTop.getYCoord();

	//If scaleX != scaleY then input validation has failed. To ensure
	//this class does not become unstable if this happens, leftTopY 
	//is scaled using scaleX.
	if (scaleX != scaleY) {
		std::cout << "Error: input validation failed, attempt to scale "
			"square by unequal factors. X scale factor will be used for "
			"Y direction." << std::endl;
	}

	edge = abs(edge * scaleX);

	//If the scale is negative, the top left coordinate moves
	if (scaleX < 0) {
		leftTopX -= edge;
		leftTopY -= edge;
	}

	//Top left coorindate is set to 0,0 if it would be negative, otherwise normally updated
	if (!checkTopLeft(leftTopX, leftTopY, "Scale would move shape to negative coordinate. "
		"Top left point set to 0,0 instead.")) {
		leftTop = Point(0, 0);
	}

	else {
		leftTop = Point(leftTopX, leftTopY);
	}

	calculatePoints();
	calculateArea();
	calculatePerimeter();
}


Square::Square(int topLeftX, int topLeftY, int Edge)
	: Shape(topLeftX, topLeftY) //topLeft is initialised in Shape
{

	//isEquilateral overwritten from default of false
	isEquilateral = true;

	//Edge length should be checked by input validation, but absolute value
	//used to prevent object becoming unstable if input validation fails
	edge = abs(Edge);


	/*
	* Important - calling a virtual function in a constructor is often
	* a bad idea. Because derived classes have not been constructed 
	* yet, if a derived class contains an overriden version of the 
	* virtual function, it will not be called. This can result in 
	* unexpected behaviour. However, it is unlikely that any derived 
	* class of a square would want to override functions to calculate 
	* area, perimeter, or points - the caluclate function declarations 
	* are marked final to enforce this. Therefore, this is an exception 
	* to the general rule. 
	*/
	calculateArea();
	calculatePerimeter();
	calculatePoints();
}