/* ------------------------------------------------------
CMP2801M: Advanced Programming
Base driver code for assignment, written in Fall 2019

Base driver code written by Ayse Kucukyilmaz. The assignment
required the driver code to be developed on. To view the
original driver code, see the "Driver Original" file.
------------------------------------------------------ */
/*
* COMMENTING STYLE:
* 
* Classes and Namespaces have a comment before the declaration with the following format:
* Declaration: Contains information relevant to what a class represents. For namespaces, 
* explains the contents of the namespace and the reason for grouping of these things
* Usage: Explains the expected and currently known usage of the class/the contents of the
* namespace
* 
* Functions always have a comment before the declaration with the following format:
* Description: Contains information relevant to how function works and how to use it
* Input: Inputs in plain english
* Output: Outputs in plain english
*
* Inside the function definition, any complex/unclear lines of code are commented. Implementation
* that is self explanatory is not given a comment.
* 
* The driver code follows the function definition format of clarifying complex/unclear lines, while
* adding comments to explain structure of code (as main is a free function so has no class comment)
*/
#include "Shape.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Square.h"
#include "Movable.h"
#include "inputValidation.h"

#include <iostream>
#include <string>

using namespace std;

int main()
{
	string userCommand;
	vector <Shape*> shapes;     // holds shapes
	vector <string> parameters; // holds parameters

	//Error messages for invalid input format: defined outside loop and using functions to make code more readable
	const string RECTANGLE_FORMAT_ERROR = inputValidation::getShapeFormatError("Rectangle", "height and a width");
	const string SQUARE_FORMAT_ERROR = inputValidation::getShapeFormatError("Square", "edge length");
	const string CIRCLE_FORMAT_ERROR = inputValidation::getShapeFormatError("Circle", "radius");
	const string MOVE_FORMAT_ERROR = inputValidation::getMovableFormatError("Move", "new x and y coordinate for "
		"the top left point");
	const string SCALE_FORMAT_ERROR = inputValidation::getMovableFormatError("Scale", "scale factor for X and then for Y "
		"(equilateral and circular shapes only use X: in this case Y input must match X input)");

	//Prints instructions before first input
	inputValidation::printInstructions();

	while (userCommand.compare("exit") != 0)
	{
		cout << "Type 'repeat' to repeat input instructions" << endl;
		cout << "Enter the command: ";

		getline(cin, userCommand);

		char* cstr = new char[userCommand.length() + 1];

		strcpy_s(cstr, userCommand.length() + 1, userCommand.c_str());

		//Tokenizing string to populate parameter vector
		/*
		* Main source inspiring code: 
		* https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/strtok-s-strtok-s-l-wcstok-s-wcstok-s-l-mbstok-s-mbstok-s-l?view=msvc-170
		* Explanation to prove understanding:
		* strtok_s takes 3 parameters: 1st is the string to be tokenized (NULL after first call, 
		* inidicater to read from 3rd argument instead), 2nd is the delimitter and 3rd is  a pointer 
		* used internally by strok_s to store the start of the next token for future calls.
		* When a delimitter is found, it is replaced with  a null character in the original string, 
		* and the start of the token is returned as a pointer (to the original string). 
		* If an already existing null character is found, a pointer to the token is also returned: 
		* this results in the last token being correctly handled, as well as null pointer returns 
		* to fully tokenized strings.
		*/

		char* token = NULL;
		char* nextToken = NULL;

		//Handles first token (requires different function call)
		token = strtok_s(cstr, " ", &nextToken);

		//Loops until strtok_s returns null 
		while (token != NULL) {
			//Token has to be pushed first to avoid attempting to push null pointer
			parameters.push_back(token);
			token = strtok_s(NULL, " ", &nextToken);

		}

		//Check for null input has to be done here to avoid call to a nonexistent parameters[0]
		if (!inputValidation::checkIndex(1,parameters, "Invalid input: null input.")) {

			//Postproccessing has to be done before continue as it is skipped otherwise
			//(except for parameter.clear() - its already empty)
			std::cout << endl << endl;
			//Deallocate memory
			delete[] cstr;
			continue;
		}
		// as a result of the process, parameters[0] holds the command
		string command = parameters[0];



		/*
		* Summary of input validation: functions handle checks for enough inputs, valid shape indexes, non-negative
		* coordinates and positive shape attributes. Checks for numerical inputs which are smalle enough to store are 
		* handled individually using try/catch blocks: functions are not used here due to the error naturally being 
		* thrown. A function would require an additional if statement every time it was used. Finally, the check for 
		* equal scale factors for scaling circles and squares is simply written once due to it being unique to that operation.
		*/

		//Create a circle
		if (command.compare("addR") == 0) {

			// Checks if the user entered all the required arguments, reminds user of format if not
			if (inputValidation::checkIndex(5, parameters, RECTANGLE_FORMAT_ERROR)) {
		 				
				try {
					//assigns parameters based on context
					int x = stoi(parameters[1]); 
					int y = stoi(parameters[2]);
					int h = stoi(parameters[3]);
					int w = stoi(parameters[4]);

					//Check if coordinates, height and width are valid (positive) can only happen after coordinates are converted to ints
					if (inputValidation::checkTopLeft(x, y) && inputValidation::checkAttributes(h, w)) {

						Rectangle* r = new Rectangle(x, y, h, w);
						shapes.push_back(r);
						
						//"<<" operator overloaded to call toString function
						//Outputs derived class functionality as function is virtual
						cout << r;
					}

				}
				//Error thrown if user inputs non-int arguments
				catch (const invalid_argument&) {
					cout << "Invalid input: coordinates, height and width must be numbers.";
				}

				//Error thrown if a number input is too large
				catch (const out_of_range&) {
					cout << "Invalid input: numbers too large to store. Please enter values with less digits.";
				}
			}
		}



		//Create a square
		else if (command.compare("addS") == 0) {

			// Checks if the user entered all the required arguments, reminds user of format if not
			if (inputValidation::checkIndex(4, parameters, SQUARE_FORMAT_ERROR)) {

				try {
					//assigns parameters based on context
					int x = stoi(parameters[1]);
					int y = stoi(parameters[2]);
					int e = stoi(parameters[3]);


					//Check if coordinates and edge length are valid (positive) can only happen after coordinates are converted to ints
					if (inputValidation::checkTopLeft(x, y) && inputValidation::checkAttributes(e)) {
						Square* s = new Square(x, y, e);
						shapes.push_back(s);

						//"<<" operator overloaded to call toString function
						//Outputs derived class functionality as function is virtual
						cout << s;
					}
				}
				//Error thrown if user inputs non-int arguments
				catch (const invalid_argument&) {
					cout << "Invalid input: coordinates and edge length must be numbers.";
				}
				//Error thrown if number input is too large
				catch (const out_of_range&) {
					cout << "Invalid input: numbers too large to store. Please enter values with less digits.";
				}
			}
		}



		//Create a circle
		if (command.compare("addC") == 0) {

			// Checks if the user entered all the required arguments, reminds user of format if not
			if (inputValidation::checkIndex(4, parameters, CIRCLE_FORMAT_ERROR)) {

				try {
					//assigns parameters based on context
					int x = stoi(parameters[1]);
					int y = stoi(parameters[2]);
					int r = stoi(parameters[3]);


					//Check if coordinates and radius are valid (positive) can only happen after coordinates are converted to ints
					if (inputValidation::checkTopLeft(x, y) && inputValidation::checkAttributes(r)) {
						Circle* c = new Circle(x, y, r);
						shapes.push_back(c);

						//"<<" operator overloaded to call toString function
						//Outputs derived class functionality as function is virtual
						cout << c;
					}
				}
				//Error thrown if user inputs non-int arguments
				catch (const invalid_argument&) {
					cout << "Invalid input: coordinates and radius must be numbers.";
				}
				//Error thrown if number input is too large
				catch (const out_of_range&) {
					cout << "Invalid input: numbers too large to store. Please enter values with less digits.";
				}
			}
		}


		//Scale a shape
		else if (command.compare("scale") == 0) {
			
			// Checks if the user entered all the required arguments, reminds user of format if not
			if (inputValidation::checkIndex(4, parameters, SCALE_FORMAT_ERROR)) {
				try {
					//assigns parameters based on context
					int shapeNo = stoi(parameters[1]);
					float scaleX = stof(parameters[2]);
					float scaleY = stof(parameters[3]);


					//general index check used to check if shape index exists
					if (inputValidation::checkIndex(shapeNo, shapes)) {

						//Now that the shape index is validated, checks can be made for isotropic scaling for circles and square
						Shape* targetShape = shapes[shapeNo - 1];

						//If the shape is equilateral or circular, the scale factors must be equal for scaling to occur
						if (targetShape->checkIfCircular() == false && targetShape->checkIfEquilateral() == false || scaleX == scaleY) {
							

							//Dynamic cast is needed to force a downcasting again
							//This allows use of polymorphic functionality
							Movable* m = dynamic_cast<Movable*>(shapes[shapeNo - 1]);
							m->scale(scaleX, scaleY);

							//"<<" operator overloaded to call toString function
							//Outputs derived class functionality as function is virtual
							cout << shapes[shapeNo - 1];
						}
						else {
							cout << "Invalid input: Equilateral and circular objects must be scaled by equal X and Y scale factors.";
						}
						
					}

				}
				//Error thrown if user inputs non-int arguments
				catch (const invalid_argument&) {
					cout << "Invalid input: scale factors and shape index must be numbers.";
				}
				//Error thrown if number input is too large
				catch (const out_of_range&) {
					cout << "Invalid input: numbers too large to store. Please enter values with less digits.";
				}
			}
		}


		//Move a shape
		else if (command.compare("move") == 0) {

			// Checks if the user entered all the required arguments, reminds user of format if not
			if (inputValidation::checkIndex(4, parameters, MOVE_FORMAT_ERROR)) {
				try {
					// move object at index 
					int shapeNo = stoi(parameters[1]); // read from parameters
					int x = stoi(parameters[2]);
					int y = stoi(parameters[3]);

					//general index check used to check if shape index exists
					//same if statement used to check for valid move coordinates too
					if (inputValidation::checkIndex(shapeNo, shapes) && inputValidation::checkTopLeft(x,y)) {

						//Dynamic cast is needed to force a downcasting again
						//This allows use of polymorphic functionality
						Movable* m = dynamic_cast<Movable*>(shapes[shapeNo - 1]);
						m->move(x, y);

						//"<<" operator overloaded to call toString function
						//Outputs derived class functionality as function is virtual
						cout << shapes[shapeNo - 1];
					}

				}
				//Error thrown if user inputs non-int arguments
				catch (const invalid_argument&) {
					cout << "Invalid input, coordinates and shape index must be numbers.";
				}
				//Error thrown if number input is too large
				catch (const out_of_range&) {
					cout << "Invalid input: numbers too large to store. Please enter values with less digits.";
				}
			}
		}

		//Display all shapes currently stored
		else if (command.compare("display") == 0) {

			cout << "Here is a list of all created shapes:\n";
			//loops though shape vector and displays each value
			for (Shape* s : shapes) {
				cout << s << "\n\n";
			}
		}

		//Delete all shapes from memory
		else if (command.compare("clear") == 0) {
			cout << "Shapes cleared";

			//deallocates memory for every element
			for (Shape* shape : shapes) {
				delete shape;
			}
			//clears vector to remove elements
			shapes.clear();
		}

		//Allows the user to repeat the instructions 
		else if (command.compare("repeat") == 0) {
		cout << "\n\n";
			inputValidation::printInstructions();
		}
		
		//Clear parameters for next input
		parameters.clear();
		
		//Deallocate memory
		delete[] cstr;
		cout << endl << endl;
	}

	//deallocates memory for every element when program terminates
	for (Shape* shape : shapes) {
		delete shape;
	}

	cout << "Press any key to continue...";
	(void)std::getchar();//c style conversion to void to prevent compiler warning of ignored return value

	return 0;
}