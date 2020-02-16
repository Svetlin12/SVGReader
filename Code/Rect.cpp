#include "Rect.h"

// the default constructor sets each member an initial value that will be in help when we determine whether or not
// the member has been changed or not
Rect::Rect() : xNum(NON_EXISTANT), yNum(NON_EXISTANT), heightNum(NON_EXISTANT), 
				widthNum(NON_EXISTANT), strokeWidth(NON_EXISTANT), fill(EMPTY_STRING), stroke(EMPTY_STRING)
{
}

// pretty simple setters down below
void Rect::setAsNumX(const double x)
{
	xNum = x;
}

void Rect::setAsNumY(const double y)
{
	yNum = y;
}

void Rect::setAsNumHeight(const double height)
{
	heightNum = height;
}

void Rect::setAsNumWidth(const double width)
{
	widthNum = width;
}

void Rect::setAsNumStrokeWidth(const double strokeWidth)
{
	this->strokeWidth = strokeWidth;
}

void Rect::setFill(const std::string fill)
{
	this->fill = fill;
}

void Rect::setStroke(const std::string stroke)
{
	this->stroke = stroke;
}


// getters
const double Rect::getX() const
{
	return xNum;
}

const double Rect::getY() const
{
	return yNum;
}

const double Rect::getHeight() const
{
	return heightNum;
}

const double Rect::getWidth() const
{
	return widthNum;
}

const double Rect::getStrokeWidth() const
{
	return strokeWidth;
}

const std::string Rect::getFill() const
{
	return fill;
}

const std::string Rect::getStroke() const
{
	return stroke;
}

const std::string Rect::getType() const
{
	return "rectangle";
}


// the print function which prints the info based on which member has a value that is different than 
// NON_EXISTANT and EMPTY_STRING
void Rect::print() const
{
	std::cout << getType() << " ";
	if (getX() != NON_EXISTANT)
	{
		std::cout << getX() << " ";
	}
	
	if (getY() != NON_EXISTANT)
	{
		std::cout << getY() << " ";
	}

	if (getHeight() != NON_EXISTANT)
	{
		std::cout << getHeight() << " ";
	}

	if (getWidth() != NON_EXISTANT)
	{
		std::cout << getWidth() << " ";
	}

	if (getFill() != EMPTY_STRING)
	{
		std::cout << getFill() << " ";
	}

	if (getStroke() != EMPTY_STRING)
	{
		std::cout << getStroke() << " ";
	}

	if (getStrokeWidth() != NON_EXISTANT)
	{
		std::cout << getStrokeWidth();
	}
	std::cout << std::endl;
}

// translates the figure by adding horizontal to the member xNum and vertical to the member yNum
void Rect::translate(const double horizontal, const double vertical)
{
	setAsNumX(getX() + horizontal);
	setAsNumY(getY() + vertical);
}

// the destructor has nothing to delete (we have no dynamically allocated memory)
Rect::~Rect()
{
}

// sets x being given a line from a file: first it finds where the x="..." is and then it extracts from that string
// the number and sets it to the member xNum
void Rect::setX(const std::string line)
{
	std::regex reg("x(\\s)*=(\\s)*\"(\\s)*[\\d]+(\\s)*\"");
	std::string onlyX = getMatch(line, reg);
	
	if (onlyX != "")
	{
		xNum = convertToDouble(onlyX);
	}
}

// the same is applied here and the below functions, only now it is for the member yNum
void Rect::setY(const std::string line)
{
	std::regex reg("y(\\s)*=(\\s)*\"(\\s)*[\\d]+(\\s)*\"");
	std::string onlyY = getMatch(line, reg);

	if (onlyY != "")
	{
		yNum = convertToDouble(onlyY);
	}
}

// read explanation for setX() - this function does the same only that it sets heightNum
void Rect::setHeight(const std::string line)
{
	std::regex reg("height(\\s)*=(\\s)*\"(\\s)*[\\d]+(\\s)*\"");
	std::string onlyHeight = getMatch(line, reg);

	if (onlyHeight != "")
	{
		heightNum = convertToDouble(onlyHeight);
	}
}

// read the explanation for setX()
void Rect::setWidth(const std::string line)
{
	std::regex reg("width(\\s)*=(\\s)*\"(\\s)*[\\d]+(\\s)*\"");
	std::string onlyWidth = getMatch(line, reg);

	if (onlyWidth != "")
	{
		widthNum = convertToDouble(onlyWidth);
	}
}

// read the explanation for setX()
void Rect::setStrokeWidth(const std::string line)
{
	std::regex reg("stroke-width(\\s)*=(\\s)*\"(\\s)*[\\d]+(\\s)*\"");
	std::string onlyStrokeWidth = getMatch(line, reg);

	if (onlyStrokeWidth != "")
	{
		this->strokeWidth = convertToDouble(onlyStrokeWidth);
	}
}

// read the explanation for setX()
void Rect::setFillFromEntireLine(const std::string line)
{
	std::regex reg("fill(\\s)*=(\\s)*\"(\\s)*[a-zA-z]+(\\s)*\"");
	std::string onlyFill = getMatch(line, reg);
	std::string color = "";

	for (int i = 0; i < onlyFill.size(); i++)
	{
		if (onlyFill[i] == '"')
		{
			for (int j = 0; onlyFill[i + j + 1] != '"'; j++)
			{
				// if there are any inputs of the sort "    green" the program will ignore the whitespaces
				if (onlyFill[i + j + 1] == ' ' && color.size() == 0)
				{
					continue;
				}

				color += onlyFill[i + j + 1];
			}
			break;
		}
	}

	if (color != "")
	{
		// removes the whitespaces at the end of the string in order for us to get the correct string
		if (color[color.size() - 1] == ' ')
		{
			for (int i = color.size() - 1; color[i] != ' '; i--)
			{
				color.erase(color.begin() + i);
			}
		}
	}
	
	// checks whether the color we have been given from the file is correct or not
	for (int i = 0; i < colorChecker.size(); i++)
	{
		if (colorChecker[i] == color)
		{
			this->fill = color;
			return;
		}
	}
}

// read the explanation for setX()
void Rect::setStrokeFromEntireLine(const std::string line)
{
	std::regex reg("stroke(\\s)*=(\\s)*\"(\\s)*[\\w]+(\\s)*\"");
	std::string onlyStroke = getMatch(line , reg);
	std::string color = "";

	for (int i = 0; i < onlyStroke.size(); i++)
	{
		if (onlyStroke[i] == '"')
		{
			for (int j = 0; onlyStroke[i + j + 1] != '"'; j++)
			{
				if (onlyStroke[i + j + 1] == ' ' && color.size() == 0)
				{
					continue;
				}

				color += onlyStroke[i + j + 1];
			}
			break;
		}
	}

	if (color != "")
	{
		// removes the whitespaces at the end of the string in order for us to get the correct string
		if (color[color.size() - 1] == ' ')
		{
			for (int i = color.size() - 1; color[i] != ' '; i--)
			{
				color.erase(color.begin() + i);
			}
		}
	}

	// checks whether the color we have been given from the file is correct or not
	for (int i = 0; i < colorChecker.size(); i++)
	{
		if (colorChecker[i] == color)
		{
			this->stroke = color;
			return;
		}
	}
}

// this function calls the above functions which on the other hand set each member being given the other line
// I made this function because it saves some lines of code that are tedious to write and really an eye sore
void Rect::setAllMembers(const std::string line)
{
	setX(line);
	setY(line);
	setHeight(line);
	setWidth(line);
	setStrokeWidth(line);
	setFillFromEntireLine(line);
	setStrokeFromEntireLine(line);
}
