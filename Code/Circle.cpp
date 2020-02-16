#include "Circle.h"

// the default constructor sets each member a value that we can recognize later on if the member hasn't been changed
Circle::Circle() : cxNum(NON_EXISTANT), cyNum(NON_EXISTANT), rNum(NON_EXISTANT), 
					strokeWidthNum(NON_EXISTANT), fill(EMPTY_STRING), stroke(EMPTY_STRING)
{
}

// getter for each member
const double Circle::getCX() const
{
	return cxNum;
}

const double Circle::getCY() const
{
	return cyNum;
}

const double Circle::getR() const
{
	return rNum;
}

const double Circle::getStrokeWidth() const
{
	return strokeWidthNum;
}

const std::string Circle::getFill() const
{
	return fill;
}

const std::string Circle::getStroke() const
{
	return stroke;
}

// setter for each member
void Circle::setAsNumCX(const double cx)
{
	this->cxNum = cx;
}

void Circle::setAsNumCY(const double cy)
{
	this->cyNum = cy;
}

void Circle::setAsNumR(const double r)
{
	this->rNum = r;
}

void Circle::setAsNumStrokeWidth(const double strokeWidth)
{
	this->strokeWidthNum = strokeWidth;
}

void Circle::setFill(const std::string fill)
{
	this->fill = fill;
}

void Circle::setStroke(const std::string stroke)
{
	this->stroke = stroke;
}

const std::string Circle::getType() const
{
	return "circle";
}

// prints the data for the circle to the console
// if cxNum, cyNum or rNum haven't been changed then the circle does not exist
void Circle::print() const
{
	if (cxNum == NON_EXISTANT || cyNum == NON_EXISTANT || rNum == NON_EXISTANT)
	{
		std::cout << "non-existant circle" << std::endl;
		return;
	}

	std::cout << getType() << " " << getCX() << " " << getCY() << " " << getR() << " ";

	if (fill != EMPTY_STRING)
	{
		std::cout << getFill() << " ";
	}

	if (stroke != EMPTY_STRING)
	{
		std::cout << getStroke() << " ";
	}

	if (strokeWidthNum != NON_EXISTANT)
	{
		std::cout << getStrokeWidth();
	}

	std::cout << std::endl;
}

// translates the circle by adding horizontal to cxNum and vertical to cyNum
void Circle::translate(const double horizontal, const double vertical)
{
	setAsNumCX(getCX() + horizontal);
	setAsNumCY(getCY() + vertical);
}

// the destructor does not need to delete anything since we haven't dynamically allocated any memory
Circle::~Circle()
{
}

// sets x being given a line from a file: first it finds where the x="..." is and then it extracts from that string
// the number and sets it to the member xNum
// note: the other setters down below work the same way except for the setters of fill and stroke
void Circle::setCX(const std::string cx)
{
	std::regex reg("cx(\\s)*=(\\s)*\"(\\s)*[\\d]+(\\s)*\"");
	std::string onlyCX = getMatch(cx, reg);

	if (onlyCX != "")
	{
		cxNum = convertToDouble(onlyCX);
	}
}

void Circle::setCY(const std::string cy)
{
	std::regex reg("cy(\\s)*=(\\s)*\"(\\s)*[\\d]+(\\s)*\"");
	std::string onlyCY = getMatch(cy, reg);

	if (onlyCY != "")
	{
		cyNum = convertToDouble(onlyCY);
	}
}

void Circle::setR(const std::string r)
{
	std::regex reg("r(\\s)*=(\\s)*\"(\\s)*[\\d]+(\\s)*\"");
	std::string onlyR = getMatch(r, reg);

	if (onlyR != "")
	{
		rNum = convertToDouble(onlyR);
	}
}

void Circle::setStrokeWidthNum(const std::string strokeWidth)
{
	std::regex reg("stroke-width(\\s)*=(\\s)*\"(\\s)*[\\d]+(\\s)*\"");
	std::string onlyStrokeWidth = getMatch(strokeWidth, reg);

	if (onlyStrokeWidth != "")
	{
		strokeWidthNum = convertToDouble(onlyStrokeWidth);
	}
}

void Circle::setFillFromEntireLine(const std::string line)
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
				// ignores the white spaces at the beginning if there are any
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
		// removes the white spaces at the end of the string in order for us to get the correct string
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

void Circle::setStrokeFromEntireLine(const std::string stroke)
{
	std::regex reg("stroke(\\s)*=(\\s)*\"(\\s)*[a-zA-Z]+(\\s)*\"");
	std::string onlyStroke = getMatch(stroke, reg);
	std::string color = "";

	for (int i = 0; i < onlyStroke.size(); i++)
	{
		if (onlyStroke[i] == '"')
		{
			for (int j = 0; onlyStroke[i + j + 1] != '"'; j++)
			{
				// ignores the whitespaces at the beginning if there are any
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

// this program saves me some time and tedious lines of code to write. It calls the functions above and sets
// each member from the line given
void Circle::setAllMembers(const std::string line)
{
	setCX(line);
	setCY(line);
	setR(line);
	setStrokeWidthNum(line);
	setFillFromEntireLine(line);
	setStrokeFromEntireLine(line);
}
