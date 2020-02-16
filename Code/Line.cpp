#include "Line.h"

// default constructor
Line::Line() : x1Num(NON_EXISTANT), x2Num(NON_EXISTANT), y1Num(NON_EXISTANT), 
				y2Num(NON_EXISTANT), strokeWidthNum(NON_EXISTANT), stroke(EMPTY_STRING)
{
}

// getter for each member
const double Line::getX1() const
{
	return x1Num;
}

const double Line::getX2() const
{
	return x2Num;
}

const double Line::getY1() const
{
	return y1Num;
}

const double Line::getY2() const
{
	return y2Num;
}

const double Line::getStrokeWidth() const
{
	return strokeWidthNum;
}

const std::string Line::getStroke() const
{
	return stroke;
}


// standard setter for each member
void Line::setAsNumX1(const double x1)
{
	this->x1Num = x1;
}

void Line::setAsNumX2(const double x2)
{
	this->x2Num = x2;
}

void Line::setAsNumY1(const double y1)
{
	this->y1Num = y1;
}

void Line::setAsNumY2(const double y2)
{
	this->y2Num = y2;
}

void Line::setAsNumStrokeWidth(const double strokeWidth)
{
	this->strokeWidthNum = strokeWidth;
}

void Line::setStroke(const std::string stroke)
{
	this->stroke = stroke;
}

const std::string Line::getType() const
{
	return "line";
}

// print function
// if x1, x2, y1, y2 or stroke haven't been changed, then this line does not exist
void Line::print() const
{
	if (x1Num == NON_EXISTANT || x2Num == NON_EXISTANT || y1Num == NON_EXISTANT || 
		y2Num == NON_EXISTANT || stroke == EMPTY_STRING)
	{
		std::cout << "no such line exists" << std::endl;
		return;
	}

	std::cout << getType() << " " << getX1() << " " << getY1() << " " << getX2() << " " << getY2() << " " << getStroke() << " ";

	if (strokeWidthNum != NON_EXISTANT)
	{
		std::cout << getStrokeWidth();
	}

	std::cout << std::endl;
}

// translates the line by adding horizontal to x1Num and x2Num and vertical to y1Num and y2Num
void Line::translate(const double horizontal, const double vertical)
{
	setAsNumX1(getX1() + horizontal);
	setAsNumX2(getX2() + horizontal);
	setAsNumY1(getY1() + vertical);
	setAsNumY2(getY2() + vertical);
}

// the destructor does not need to delete anything since we did not dynamically alocate any memory
Line::~Line()
{
}

// this function and the ones down below work the same way only that they set different members
// they recieve a line from a file as a parameter and then they extract the data for their concrete
// member (i.e. in this case x="...") and then converts the number inside the quotation marks to double using
// the function convertToDouble from the base class (which was inherited)
void Line::setX1(const std::string line)
{
	std::regex reg("x1(\\s)*=(\\s)*\"(\\s)*[\\d]+(\\s)*\"");
	std::string onlyX1 = getMatch(line, reg);

	if (onlyX1 != "")
	{
		x1Num = convertToDouble(onlyX1);
	}
}

void Line::setX2(const std::string line)
{
	std::regex reg("x2(\\s)*=(\\s)*\"(\\s)*[\\d]+(\\s)*\"");
	std::string onlyX2 = getMatch(line, reg);

	if (onlyX2 != "")
	{
		x2Num = convertToDouble(onlyX2);
	}
}

void Line::setY1(const std::string line)
{
	std::regex reg("y1(\\s)*=(\\s)*\"(\\s)*[\\d]+(\\s)*\"");
	std::string onlyY1 = getMatch(line, reg);

	if (onlyY1 != "")
	{
		y1Num = convertToDouble(onlyY1);
	}
}

void Line::setY2(const std::string line)
{
	std::regex reg("y2(\\s)*=(\\s)*\"(\\s)*[\\d]+(\\s)*\"");
	std::string onlyY2 = getMatch(line, reg);

	if (onlyY2 != "")
	{
		y2Num = convertToDouble(onlyY2);
	}
}

void Line::setStrokeWidth(const std::string line)
{
	std::regex reg("stroke-width(\\s)*=(\\s)*\"(\\s)*[\\d]+(\\s)*\"");
	std::string onlyStrokeWidth = getMatch(line, reg);

	if (onlyStrokeWidth != "")
	{
		strokeWidthNum = convertToDouble(onlyStrokeWidth);
	}
}

// in this case the difference between this function and the above ones is that it takes the string inside the
// quotation marks and sets it to stroke
void Line::setStrokeFromEntireLine(const std::string line)
{
	std::regex reg("stroke(\\s)*=(\\s)*\"(\\s)*[a-zA-Z]+(\\s)*\"");
	std::string onlyStroke = getMatch(line, reg);
	std::string color = "";

	for (int i = 0; i < onlyStroke.size(); i++)
	{
		if (onlyStroke[i] == '"')
		{
			for (int j = 0; onlyStroke[i + j + 1] != '"'; j++)
			{
				// ignores the whitespaces in the beginning if there are any
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

// this function calls each function above one by one each setting their corresponding member
void Line::setAllMembers(const std::string line)
{
	setX1(line);
	setX2(line);
	setY1(line);
	setY2(line);
	setStrokeWidth(line);
	setStrokeFromEntireLine(line);
}
