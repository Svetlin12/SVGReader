#pragma once
#include <cmath>
#include "Shape.h"
#include "Rect.h"
#include "Circle.h"
#include "Line.h"
#include "Reader.h"
#include "CreateRectangle.h"
#include "CreateCircle.h"
#include "CreateLine.h"

// this is the class which will be the interface for our program - it has the functions that are needed:
// print, create, erase, translate, within, open, close, save and saveas
// note: this class directly uses the Parser class that's why we have open, close, save and saveas
// functions - we don't want to make the code to be difficult to read

class ConsoleInterface
{
private:

	// we implemented Singleton here because this class will be used at most once, so there is no need
	// for it to have multiple instances
	static ConsoleInterface* instance;

	// inputFromFile stores the lines of the file that contain the information for the figures
	// whereas figures stores the same info but now they are represented by either Rect, Line or Circle class
	// input's size should be the same as the figures' size (meaning that for every element in input there is a
	// corresponding one in figures
	std::vector<std::string> inputFromFile;
	std::vector<Shape*> figures;

	// assigns the vector with the information for the figures from Parser to inputFromFiles by using the
	// command getMatches() from Parser
	void getInputFromFile();

	// uses the information we have just obtained from the function above to create the figures it represents
	void getFigures();

	// determines which figure has been pointed out in each line from the file
	const std::string getTypeFromInput(const std::string input);

	// by using a regular expression to find some pattern in a string, this function returns the first match
	// the regular expression reg finds in the string str
	const std::string getMatch(std::string str, std::regex reg);

	// this function recieves a vector as one of its parameters and pushes all the matches the regular expression reg finds in
	// the string str... we will use this function to find some numbers from the input and push them inside the 
	// vector
	void getNumbersToVector(std::vector<std::string>& vector, std::string str, std::regex reg);

	// extracts a number from a string (or the first number from the string) using the function getMatch()
	// and then it converts the string to a double and returns it
	const double getNumberFromString(std::string str);

	// this function takes a shape as its parameter and makes a line for a file out of its data
	// we use this function in translate when we need to update the file lines when we have shifted the figure
	const std::string makeLineForFile(Shape* shape);

	// checks the corectness of the input in translate function
	const bool checkTranslateInput(const std::string input);

	// compares two strings by going through the smaller one (which is string2) and comparing each element to 
	// the corresponding element of string1
	// we use this function in translate to check the input (we are checking vertical = ... and horizontal = ... 
	// in particular)
	const bool compareTwoStrings(const std::string string1, const std::string string2);

	// extracts vertical = ... from the input (translate (number) vertical = ... horizontal = ...)
	// and returns it as a string
	const std::string getVerticalFromInput(const std::string input);

	// this function works the same as the above one only now it extracts horizontal = ...
	const std::string getHorizontalFromInput(const std::string input);

	// checks the corectness of the input given to the within function
	const bool checkWithinInput(const std::string input);

	// Singleton implementation - we are preventing the compiler from creating them behind the scenes
	// so that our Singleton will be complete
	ConsoleInterface();
	~ConsoleInterface();
	ConsoleInterface(const ConsoleInterface& c);
	ConsoleInterface& operator= (const ConsoleInterface& c);

	// counts the number of words and numbers in an input 
	// that way we can determine whether we have been given either too few or too many words and numbers
	const int countNumberOfWordsAndNums(const std::string input);

public:

	// Singleton implementation
	static ConsoleInterface* getInstance();
	static void releaseInstance();

	// prints all the data for the figures to the console as a list
	void print() const;

	// creates a figure
	void create(const std::string input);

	// removes a figure from the list
	void erase(const int numToErase);

	// translates either one figure or all figures
	void translate(const std::string input);

	// determines which figures are inside a concrete one
	void within(const std::string input);

	// opens a file
	const bool open(const std::string fileName);

	// closes a file
	void close();

	// saves the new information to the current file
	void save();

	// saves the new information to another file
	void saveAs(const std::string fileName);

};