#include "inputValidation.h"

namespace inputValidation {

	bool checkTopLeft(int topLeftX, int topLeftY) {
		if (topLeftX < 0 || topLeftY < 0) {
			std::cout << "Invalid top left coordinate: graph starts at 0,0, shape cannot contain negative values.";
			return false;
		}
		else {
			return true;
		}
	}

	bool checkAttributes(int attribute) {
		if (attribute <= 0) {
			std::cout << "Invalid shape attribute: attribute must be positive integers.";
			return false;
		}
		else {
			return true;
		}
	}

	bool checkAttributes(int attribute, int attribute1) {
		if (attribute <= 0 || attribute1 <= 0) {
			std::cout << "Invalid shape attributes: attributes must be positive integers.";
			return false;
		}
		else {
			return true;
		}
	}

	std::string getShapeFormatError(std::string shapeName, std::string shapeAttributes) {
		std::string errorMessage = "Incorrect input format: " + shapeName + "s require an X and Y "
			"coordinate for the top left point, followed by a\n" + shapeAttributes + ".\nThese "
			"specifications should be seperated with a single space.";
		return errorMessage;
	}

	std::string getMovableFormatError(std::string operation, std::string moveParams) {
		std::string errorMessage = "Incorrect input format: " + operation + " operation requires an "
			"index of the shape to be operated on, followed by a\n" + moveParams + ".\nThese specifications should "
			"be seperated with a single space.";
		return errorMessage;
	}

	void printInstructions() {
		std::cout << "There are 2 main operations, creating and manipulating shapes, as well as auxilliary operations.\n"
			"Auxilliary operations (only 1 input): type 'exit' to terminate the program, type 'display' to show all shapes\n"
			"currently in memory and type 'clear' to delete all shapes.\n\n"
			"Creating shapes (multiple inputs separated by spaces): type 'addR','addS' and 'addC' to create rectangles,\nsquares "
			"and circles.\nThe next two inputs for all of these are the X and Y coordinate of the top left corner.\nFinally, the shape "
			"specific details: edge length for square, radius for circle, and height and width for rectangle.\nCircle is represented by a "
			"square of 4 tangents of the circle: use this to create a relevant top left point.\n\n"
			"Manipulating shapes (multiple inputs separated by spaces): type 'move' to move a shape to a new position,\nfollowed by the shape "
			"index, then the new top left X and Y coordinates.\nType 'scale' to scale an object up or down, followed by the shape index then the "
			"factor of X and Y to scale the shape by.\nShapes can be scaled in a negative direction too.\nScale for equilateral and circular "
			"objects must have equal X and Y factors.\n\n"
			"Rules of shapes: The graph for all shapes starts at 0,0 in the top left and goes no lower.\nA shape cannot be created or moved "
			"to a negative top left coordinate.\nIf a negative scale operation would place the shape lower than 0,0, the top left coordinate "
			"is forced\nto 0,0 (the scale is still applied from there).\n" << std::endl;
	}

}
