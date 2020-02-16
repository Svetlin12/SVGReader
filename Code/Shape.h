#pragma once
#include <iostream>
#include <regex>
#include <string>

// the classes that derive from this one are used to store the information from the file about the figures 
// and represent them as well. Also, they are used when the user creates a new figure, although with the help of 
// three other classes (CreateCircle, CreateRectangle and CreateLine)

// these values are used in the constructor of the derived
// classes and the print function. They help determine whether or not
// a member from the derived class has been changed or not
#define NON_EXISTANT -1
#define EMPTY_STRING ""

// abstract class which defines a shape. It is used as the base class for Rect, Circle and Line as they share 
// some functions
class Shape
{
public:

	// a vector that contains a bunch of the colors that svg supports (I didn't add all but support for all colors
	// could be added easily - just add them here). This vector will be in use when we want to check whether we have
	// been given a correct color
	std::vector<std::string> colorChecker = { "none", "aqua", "aquamarine", "azure", "beige", "black", "blue", "blueviolet", "brown", "chocolate", "crimson", "darkblue",
		"darkgray", "darkgreen", "darkgrey", "darkorange", "darkred", "darkviolet", "deeppink", "dimgray", "dimgrey", "firebrick", "forestgreen",
		"ghostwhite", "gold", "gray", "green", "greenyellow", "grey", "lightblue", "lightgreen", "lightblue", "lightgray", "lightgreen", "lightgrey",
		"lightpink", "lightyellow", "maroon", "olive", "orange", "pink", "purple", "red", "silver", "skyblue", "snow", "tomato", "turquoise", "violet",
		"wheat", "white", "yellow", "yellowgreen" };

	const std::string getMatch(std::string str, std::regex reg);
	const double convertToDouble(const std::string str);

	// inheritance is used so this is an essential
	virtual ~Shape();

	// translates the figures with the given values of horizontal and vertical which both can be negative values
	virtual void translate(const double horizontal, const double vertical) = 0;

	// determines which type of figure the Shape* (later on we will use it) is
	virtual const std::string getType() const = 0;

	// prints the information to the console
	virtual void print() const = 0;

	// sets the values of the figures based on the infomation given from the file
	virtual void setAllMembers(const std::string line) = 0;
};