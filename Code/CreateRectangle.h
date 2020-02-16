#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <regex>

// we use those in the constructor for better understanding of the code
#define INITIAL_VALUE -1
#define INITIAL_STRING ""

// This class is used to help out in the creation of a rectangle when the user uses the command create
// Because the implementation is long I chose to separate this class and Rect class to make it more 
// simple. After all, this class is for creating from input, the other one is used to represent the information
// from the input.

class CreateRectangle
{
private:

	// variable for x
	double x;

	// variable for y
	double y;

	// variable for height
	double height;

	// variable for width
	double width;

	// variable stroke-width
	double strokeWidth;

	// variable for fill
	std::string fill;

	// variable for stroke
	std::string stroke;

	// vector to store the numbers from the input
	std::vector<std::string> nums;

	// vector to store the words from the input
	std::vector<std::string> words;

	// vector used to check if the colors given from the input are correct
	std::vector<std::string> colorChecker = { "none", "aqua", "aquamarine", "azure", "beige", "black", "blue", "blueviolet", "brown", "chocolate", "crimson", "darkblue",
		"darkgray", "darkgreen", "darkgrey", "darkorange", "darkred", "darkviolet", "deeppink", "dimgray", "dimgrey", "firebrick", "forestgreen",
		"ghostwhite", "gold", "gray", "green", "greenyellow", "grey", "lightblue", "lightgreen", "lightblue", "lightgray", "lightgreen", "lightgrey",
		"lightpink", "lightyellow", "maroon", "olive", "orange", "pink", "purple", "red", "silver", "skyblue", "snow", "tomato", "turquoise", "violet",
		"wheat", "white", "yellow", "yellowgreen" };

public:

	// checks whether the number of words is 0 (other than create and rectangle that is)
	const bool isWordsSizeZero() const;

	// checks whether we have been given some intentionally or unintentionally wrong information
	// in which case the program should not break
	const bool checkForBadInput(const std::string input, const int Case);

	// default constructor
	CreateRectangle();

	// pushes the numbers from the input into the vector num
	void setNums(std::string str, std::regex reg);

	// pushes the words from the input into the vector words (other than create and rectangle)
	void setWords(std::string str, std::regex reg);

	// checks whether there is a number to set to stroke width
	const bool checkIfStrokeWidthExists(const std::string str);

	// checks whether we have been given a correct color from the input using the vector above (colorChecker)
	const bool checkIfCorrectColor();

	// gets the number of numbers (the size of nums)
	const int getNumsCount();

	// checks whether the numbers don't start with 0
	const bool checkForCorrectNumbers() const;

	// the two functions below determine whether we have 1 or 2 words (apart from create and rectangle)
	const bool case1Char();
	const bool case2Chars();

	// the four functions below determine whether we have 2 or 5 numbers; they also set the members
	// to their corresponding values
	void caseNums2(std::string& lineForFile);
	void caseNums3(std::string& lineForFile);
	void caseNums4(std::string& lineForFile);
	void caseNums5(std::string& lineForFile);

	// setter for each member
	void setX(const double x);
	void setY(const double y);
	void setHeight(const double height);
	void setWidth(const double width);
	void setStrokeWidth(const double strokeWidth);
	void setFill(const std::string fill);
	void setStroke(const std::string stroke);

	// getter for each member
	const double getX() const;
	const double getY() const;
	const double getHeight() const;
	const double getWidth() const;
	const double getStrokeWidth() const;
	const std::string getFill() const;
	const std::string getStroke() const;
};