#include "CreateCircle.h"

// returns true if the size of the vector words is 0 and false otherwise
const bool CreateCircle::isWordsCountZero() const
{
	return words.size() == 0;
}

// checks whether the numbers are correct meaning that there are not inputs of the sort "create circle
// 20 20 here yellow" in order to assure ourselves that the program will not break
const bool CreateCircle::checkForBadInput(const std::string input)
{
	// this is where we will store the numbers
	std::vector<std::string> inputNums;

	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == ' ')
		{
			std::string instance = "";

			// counts the iterations of the loop and then is used to add to i in order to skip the 
			// amount of input characters we passed through in the loop down below
			// we add counter - 1 to i because i will increase immediately after the next iteration begins
			// meaning that if we added counter the loop will skip one character which is vital for the
			// program
			int counter = 0;
			for (int j = 1; input[i + j] != ' '; j++)
			{
				instance.push_back(input[i + j]);
				counter++;
			}

			if (instance != "")
			{
				inputNums.push_back(instance);
			}

			i += counter - 1;
		}
		
		// leave the loop when the vector has that many items inside
		if (inputNums.size() == 4)
		{
			break;
		}
	}

	// go through the vector starting from 1 since inputNums[0] is circle which we do not need to check
	for (int i = 1; i < inputNums.size(); i++)
	{
		for (int j = 0; j < inputNums[i].size(); j++)
		{
			if (inputNums[i][j] < '0' || inputNums[i][j] > '9')
			{
				return true;
			}
		}
	}

	return false;
}

CreateCircle::CreateCircle() : cx(NO_VALUE), cy(NO_VALUE), r(NO_VALUE), strokeWidth(NO_VALUE),
								stroke(NO_STRING), fill(NO_STRING)
{
}

// normal setters
void CreateCircle::setCX(const double cx)
{
	this->cx = cx;
}

void CreateCircle::setCY(const double cy)
{
	this->cy = cy;
}

void CreateCircle::setR(const double r)
{
	this->r = r;
}

void CreateCircle::setStrokeWidth(const double strokeWidth)
{
	this->strokeWidth = strokeWidth;
}

void CreateCircle::setFill(const std::string fill)
{
	this->fill = fill;
}

void CreateCircle::setStroke(const std::string stroke)
{
	this->stroke = stroke;
}

// normal getters
const double CreateCircle::getCX() const
{
	return cx;
}

const double CreateCircle::getCY() const
{
	return cy;
}

const double CreateCircle::getR() const
{
	return r;
}

const double CreateCircle::getStrokeWidth() const
{
	return strokeWidth;
}

const std::string CreateCircle::getFill() const
{
	return fill;
}

const std::string CreateCircle::getStroke() const
{
	return stroke;
}

// puts all the numbers from the input inside the vector nums using a regular expression in order to find them
void CreateCircle::setNums(std::string str, std::regex reg)
{
	std::sregex_iterator currentMatch(str.begin(), str.end(), reg);
	std::sregex_iterator lastMatch;

	while (currentMatch != lastMatch)
	{
		std::smatch match = *currentMatch;
		nums.push_back(match.str());
		currentMatch++;
	}
}

// puts all the words from the input inside the vector words (excluding create and circle) using a
// regular expression in order to find them
void CreateCircle::setWords(std::string str, std::regex reg)
{
	std::sregex_iterator currentMatch(str.begin(), str.end(), reg);
	std::sregex_iterator lastMatch;

	while (currentMatch != lastMatch)
	{
		std::smatch match = *currentMatch;
		words.push_back(match.str());
		currentMatch++;
	}

	// go through the vector and remove the items which values are create and circle
	for (int i = 0; i < words.size(); i++)
	{
		if (words[i] == "create" || words[i] == "circle")
		{
			words.erase(words.begin() + i);
			i--;
		}
	}
}

// checks whether the last number is after the last word meaning that this is a number for stroke-width
const bool CreateCircle::checkIfStrokeWidthExists(const std::string input)
{
	if (input.find(nums[nums.size() - 1]) > input.find(words[words.size() - 1]))
	{
		return true;
	}
	return false;
}

// checks whether the colors we have been given from the console are correct by going thorough the 
// vector words and comparing each words element with each element from the vector colorChecker
const bool CreateCircle::checkIfCorrectColor()
{
	for (int j = 0; j < words.size(); j++)
	{
		bool isItCorrect = false;
		for (int i = 0; i < colorChecker.size(); i++)
		{
			if (colorChecker[i] == words[j])
			{
				isItCorrect = true;
			}
		}

		if (!isItCorrect)
		{
			return false;
		}
	}
	return true;
}

// returns the size of the vector nums
const int CreateCircle::getNumsCount()
{
	return nums.size();
}

// checks whether the numbers start with 0 or not (excluding 0)
const bool CreateCircle::checkForCorrectNumbers() const
{
	for (int i = 0; i < nums.size(); i++)
	{
		if (nums[i].size() > 1 && nums[i][0] == '0')
		{
			return false;
		}
	}
	return true;
}

// returns if words contains one element(word)
const bool CreateCircle::case1Word()
{
	return words.size() == 1;
}

// returns if words contains two elements(words)
const bool CreateCircle::case2Words()
{
	return words.size() == 2;
}

// this is the case we have when we don't have a number for stroke-width
// we set cx, cy and r, fill or stroke, or both
// note: we will write the line for file ourselves and then give it to the caller that's why we use &
void CreateCircle::caseNums3(std::string & lineForFile)
{
	// incorrect input if the colors aren't right
	if (!checkIfCorrectColor())
	{
		lineForFile = "";
		return;
	}

	// incorrect input if the size of the vector words is more than two
	// there are only two strings as members so there should not be more words than 2
	if (words.size() > 2)
	{
		lineForFile = "";
		return;
	}

	setCX(std::stoi(nums[0]));
	setCY(std::stoi(nums[1]));
	setR(std::stoi(nums[2]));

	if (case1Word())
	{
		fill = words[0];
		lineForFile += "<circle cx=\"";
		lineForFile += nums[0];
		lineForFile += "\" cy=\"";
		lineForFile += nums[1];
		lineForFile += "\" r=\"";
		lineForFile += nums[2];
		lineForFile += "\" fill=\"";
		lineForFile += fill;
	}
	else if (case2Words())
	{
		fill = words[0];
		stroke = words[1];
		lineForFile += "<circle cx=\"";
		lineForFile += nums[0];
		lineForFile += "\" cy=\"";
		lineForFile += nums[1];
		lineForFile += "\" r=\"";
		lineForFile += nums[2];
		lineForFile += "\" fill=\"";
		lineForFile += fill;
		lineForFile += "\" stroke=\"";
		lineForFile += stroke;
	}

	lineForFile += "\" />";
}

// this is the case we use when we have a number for stroke-width
// this function uses the same principles as the above one
void CreateCircle::caseNums4(std::string & lineForFile)
{
	if (!checkIfCorrectColor())
	{
		lineForFile = "";
		return;
	}

	if (words.size() > 2)
	{
		lineForFile = "";
		return;
	}

	setCX(std::stoi(nums[0]));
	setCY(std::stoi(nums[1]));
	setR(std::stoi(nums[2]));
	setStrokeWidth(std::stoi(nums[3]));

	if (case1Word())
	{
		fill = words[0];
		lineForFile += "<circle cx=\"";
		lineForFile += nums[0];
		lineForFile += "\" cy=\"";
		lineForFile += nums[1];
		lineForFile += "\" r=\"";
		lineForFile += nums[2];
		lineForFile += "\" fill=\"";
		lineForFile += fill;
	}
	else if (case2Words())
	{
		fill = words[0];
		stroke = words[1];
		lineForFile += "<circle cx=\"";
		lineForFile += nums[0];
		lineForFile += "\" cy=\"";
		lineForFile += nums[1];
		lineForFile += "\" r=\"";
		lineForFile += nums[2];
		lineForFile += "\" fill=\"";
		lineForFile += fill;
		lineForFile += "\" stroke=\"";
		lineForFile += stroke;
	}
	
	lineForFile += "\" stroke-width=\"";
	lineForFile += nums[3];
	lineForFile += "\" />";
}
