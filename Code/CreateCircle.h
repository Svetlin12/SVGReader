#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <regex>

// we use those in the default constructor in order to make the code easier to understand
#define NO_VALUE -1
#define NO_STRING ""

// we use this class to create a circle when the command create circle is given from the console
// separating creation and representation makes the code better to understand and read

class CreateCircle
{
private:

	// stores the cx value
	double cx;

	// stores the cy value
	double cy;

	// stores the r value
	double r;

	// stores the stroke-width value
	double strokeWidth;

	// stores the fill string
	std::string fill;

	// stores the stroke string
	std::string stroke;

	// a vector used to check the corectness of the color(colors) we get from the input
	std::vector<std::string> colorChecker = { "none", "aqua", "aquamarine", "azure", "beige", "black", "blue", "blueviolet", "brown", "chocolate", "crimson", "darkblue",
		"darkgray", "darkgreen", "darkgrey", "darkorange", "darkred", "darkviolet", "deeppink", "dimgray", "dimgrey", "firebrick", "forestgreen",
		"ghostwhite", "gold", "gray", "green", "greenyellow", "grey", "lightblue", "lightgreen", "lightblue", "lightgray", "lightgreen", "lightgrey",
		"lightpink", "lightyellow", "maroon", "olive", "orange", "pink", "purple", "red", "silver", "skyblue", "snow", "tomato", "turquoise", "violet",
		"wheat", "white", "yellow", "yellowgreen" };

	// stores the numbers from the input
	std::vector<std::string> nums;

	// stores the words from the input (excluding create and circle)
	std::vector<std::string> words;

public:

	// checks whether the size of words is 0
	const bool isWordsCountZero() const;

	// checks the corectness of the numbers that have been given to us as input
	const bool checkForBadInput(const std::string input);

	// default constructor
	CreateCircle();

	// normal setters
	void setCX(const double cx);
	void setCY(const double cy);
	void setR(const double r);
	void setStrokeWidth(const double strokeWidth);
	void setFill(const std::string fill);
	void setStroke(const std::string stroke);

	// normal getters
	const double getCX() const;
	const double getCY() const;
	const double getR() const;
	const double getStrokeWidth() const;
	const std::string getFill() const;
	const std::string getStroke() const;

	// puts the numbers from the input inside the vector nums
	void setNums(std::string str, std::regex reg);

	// puts the words from the input inside the vector words
	void setWords(std::string str, std::regex reg);

	// checks whether there is a number for stroke-width
	const bool checkIfStrokeWidthExists(const std::string input);

	// checks whether the color/colors are correct
	const bool checkIfCorrectColor();

	// returns the size of the vector nums
	const int getNumsCount();

	// checks whether the numbers in nums start with 0 or not
	const bool checkForCorrectNumbers() const;
	
	// checks if the size of words is 1
	const bool case1Word();

	// checks if the size of words is 2
	const bool case2Words();

	// when we have 3 numbers; sets the members to their corresponding values
	void caseNums3(std::string& lineForFile);

	// when we have 4 numbers; sets the members to their corresponding values
	void caseNums4(std::string& lineForFile);
};