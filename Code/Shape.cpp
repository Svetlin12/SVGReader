#include "Shape.h"

// what this basically does is that it takes a string, for example x = "20" and then converts the string 20 to a double
const double Shape::convertToDouble(const std::string str)
{
	std::string number;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '"')
		{
			for (int j = 0; str[i + j + 1] != '"'; j++)
			{
				// checks if the user has given us some spaces so that our program will bug out
				if (str[i + j + 1] == ' ')
				{
					continue;
				}

				number.push_back(str[i + j + 1]);
			}
			break;
		}
	}
	return (double)std::stoi(number);
}

Shape::~Shape()
{
}

// this function returns the first match it found between the string str and the regular expression reg
// if not return "" - so that the caller knows what happened
const std::string Shape::getMatch(std::string str, std::regex reg)
{
	std::sregex_iterator match(str.begin(), str.end(), reg);
	std::sregex_iterator end;

	if (match != end)
	{
		std::smatch matchedString = *match;
		std::string stringToGet = matchedString.str();
		return stringToGet;
	}
	else
	{
		return "";
	}
}
