#include "Rectangle.h"
#include <sstream>
#include <iomanip>

void Rectangle::calculateArea() {
	area = height * width;
}


void Rectangle::calculatePerimeter() {
	perimeter = 2 * height + 2 * width;
}


void Rectangle::calculatePoints() {
	//All points are recalculated and created as new Point objects
	points.clear();

	//Left top is already updated, other points are calculated relative to it
	points.push_back(leftTop);
	int leftTopX = leftTop.getXCoord();
	int leftTopY = leftTop.getYCoord();

	Point rightTop(leftTopX + width, leftTopY);
	points.push_back(rightTop);

	Point rightBottom(leftTopX + width, leftTopY + height);
	points.push_back(rightBottom);

	Point leftBottom(leftTopX, leftTopY + height);
	points.push_back(leftBottom);
}


std::string Rectangle::toString() const {
	std::ostringstream out;

	out << "Rectangle[h=" << height << ",w=" << width << "]\nPoints[";

	for (Point currentPoint : points) {
		out << "(" << currentPoint.getXCoord() << "," <<
			currentPoint.getYCoord() << ")";
	}

	//float outputs are rounded to 1.d.p.
	out << std::fixed << std::setprecision(1) << "]\nArea=" << area
		<< " Perimeter=" << perimeter;

	return out.str();
}


void Rectangle::move(int newX, int newY) {
	if (checkTopLeft(newX, newY)) {
		leftTop = Point(newX, newY);
		calculatePoints();
	}
}


void Rectangle::scale(float scaleX, float scaleY) {

	int leftTopX = leftTop.getXCoord();
	int leftTopY = leftTop.getYCoord();

	width = abs(width * scaleX);
	height = abs(height * scaleY);

	//If scaleX is negative, the top left coordinate moves in the X direction
	if (scaleX < 0) {
		leftTopX -= width;
	}
	//If scaleY is negative, the top left coordinate moves in the Y direction
	if (scaleY < 0) {
		leftTopY -= height;
	}

	//Top left coorindate is set to 0,0 if it would be negative, otherwise normally updated
	if (!checkTopLeft(leftTopX, leftTopY, "Scale would move shape to negative coordinate. "
		"Top left point set to 0, 0 instead.")) {
		leftTop = Point(0, 0);
	}

	else {
		leftTop = Point(leftTopX, leftTopY);
	}

	calculatePoints();
	calculateArea();
	calculatePerimeter();
}


Rectangle::Rectangle(int topLeftX, int topLeftY, int Height, int Width)
	: Shape(topLeftX, topLeftY) //topLeft is initialised in Shape
{
	//Height and width should be checked by input validation, but absolute value
	//used to prevent object becoming unstable if input validation fails
	height = abs(Height);
	width = abs(Width);


	/*
	* Important - calling a virtual function in a constructor is often
	* a bad idea. Because derived classes have not been constructed
	* yet, if a derived class contains an overriden version of the
	* virtual function, it will not be called. This can result in
	* unexpected behaviour. However, it is unlikely that any derived
	* class of a rectangle would want to override functions to calculate
	* area, perimeter, or points - the caluclate function declarations
	* are marked final to enforce this. Therefore, this is an exception
	* to the general rule.
	*/
	calculateArea();
	calculatePerimeter();
	calculatePoints();
}