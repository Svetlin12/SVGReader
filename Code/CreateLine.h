#pragma once
#include <iostream>
#include <string>
#include <regex>
#include <vector>

// we use these two in the constructor for a better readable code
#define NO_VALUE -1 
#define NO_STRING ""

// we use this class in order to create a circle
// we separated the implementation to creation and representation to make it more simple and easy to understand

class CreateLine
{
private:

	// stores x1 value
	double x1;

	// stores x2 value
	double x2;

	// stores y1 value
	double y1;

	// stores y2 value
	double y2;

	// stores stroke-width value
	double strokeWidth;

	// stores stroke string
	std::string stroke;

	// vector used to check the correctness of the color we have been given from the input
	std::vector<std::string> colorChecker = { "none", "aqua", "aquamarine", "azure", "beige", "black", "blue", "blueviolet", "brown", "chocolate", "crimson", "darkblue",
		"darkgray", "darkgreen", "darkgrey", "darkorange", "darkred", "darkviolet", "deeppink", "dimgray", "dimgrey", "firebrick", "forestgreen",
		"ghostwhite", "gold", "gray", "green", "greenyellow", "grey", "lightblue", "lightgreen", "lightblue", "lightgray", "lightgreen", "lightgrey",
		"lightpink", "lightyellow", "maroon", "olive", "orange", "pink", "purple", "red", "silver", "skyblue", "snow", "tomato", "turquoise", "violet",
		"wheat", "white", "yellow", "yellowgreen" };

	// stores the numbers from the input
	std::vector<std::string> nums;

	// stores the words from the input (excluding create and line)
	std::vector<std::string> words;


public:

	// checks whether words has a size of 0
	const bool isWordsCountZero();

	// checks the corectness of the numbers that have been given to us as input
	const bool checkIfBadInput(const std::string input);

	// default constructor
	CreateLine();

	// normal getter for each member
	const double getX1() const;
	const double getX2() const;
	const double getY1() const;
	const double getY2() const;
	const double getStrokeWidth() const;
	const std::string getStroke() const;

	// normal setter for each member
	void setX1(const double x1);
	void setX2(const double x2);
	void setY1(const double y1);
	void setY2(const double y2);
	void setStrokeWidth(const double strokeWidth);
	void setStroke(const std::string stroke);

	// pushes all the numbers from the input to the vector nums
	void setNums(std::string str, std::regex reg);

	// pushes all the words from the input to the vector words (excluding create and circle)
	void setWords(std::string str, std::regex reg);

	// checks whether there is a number for stroke-width
	const bool checkIfStrokeWidthExists(const std::string input);

	// checks whether the colors we get from the input have been correct
	const bool checkIfCorrectColor();

	// returns the size of the vector nums
	const int getNumsCount();

	// checks whether there are numbers that start with 0 (excluding 0)
	const bool checkForCorrectNumbers() const;

	// we use this function when we get 4 numbers at total; sets the members to their corresponding values
	void caseStrokeWidth(std::string& lineForFile);

	// we use this one when we get 3 numbers at total; sets the members to their corresponding values
	void caseNoStrokeWidth(std::string& lineForFile);
};