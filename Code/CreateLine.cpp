#include "CreateLine.h"

// returns true if the size of the vector words is 0, false otherwise
const bool CreateLine::isWordsCountZero()
{
	return words.size() == 0;
}

// checks whether the numbers are correct
// we need to check only 4 numbers : x1, y1, x2 and y2 and then stop right after checking the last one
// in this case then we only need to push 4 numbers inside the vector inputNums and then break the first loop
// then go through the vector and start from 1 because inputNums[0] is the word line
// inside the loop we check whether the numbers are correct
// return true if the input is incorrect (if any number is incorrect), return false otherwise
const bool CreateLine::checkIfBadInput(const std::string input)
{
	std::vector<std::string> inputNums;
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == ' ')
		{
			// string to create and hold the current number and then push it inside the vector
			std::string instance = "";

			// counts the amount of iterations of the loop down below and then adds counter - 1 to i
			// because we don't need the outer loop to go through the actual number after we have checked them
			// with this one: it's just a waste of time
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

			// if counter is not 0
			if (!counter)
				i += counter - 1;
		}
		
		// when we have put 4 numbers and the word line inside the vector we should stop the loop from going further
		if (inputNums.size() == 5)
		{
			break;
		}
	}

	// go through the vector and check each string(number) inside
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

CreateLine::CreateLine() : x1(NO_VALUE), y1(NO_VALUE), x2(NO_VALUE), y2(NO_VALUE), strokeWidth(NO_VALUE), 
							stroke(NO_STRING)
{
}

// normal getters
const double CreateLine::getX1() const
{
	return x1;
}

const double CreateLine::getX2() const
{
	return x2;
}

const double CreateLine::getY1() const
{
	return y1;
}

const double CreateLine::getY2() const
{
	return y2;
}

const double CreateLine::getStrokeWidth() const
{
	return strokeWidth;
}

const std::string CreateLine::getStroke() const
{
	return stroke;
}

// normals setters
void CreateLine::setX1(const double x1)
{
	this->x1 = x1;
}

void CreateLine::setX2(const double x2)
{
	this->x2 = x2;
}

void CreateLine::setY1(const double y1)
{
	this->y1 = y1;
}

void CreateLine::setY2(const double y2)
{
	this->y2 = y2;
}

void CreateLine::setStrokeWidth(const double strokeWidth)
{
	this->strokeWidth = strokeWidth;
}

void CreateLine::setStroke(const std::string stroke)
{
	this->stroke = stroke;
}

// puts the numbers from the input inside the vector nums using a regular expression to find them
void CreateLine::setNums(std::string str, std::regex reg)
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

// puts the words from the input inside the vector words (excluding create and line) using a regular expression to
// find them
void CreateLine::setWords(std::string str, std::regex reg)
{
	std::sregex_iterator currentMatch(str.begin(), str.end(), reg);
	std::sregex_iterator lastMatch;

	while (currentMatch != lastMatch)
	{
		std::smatch match = *currentMatch;
		words.push_back(match.str());
		currentMatch++;
	}

	// go through the vector words and then remove the first two which are create and line
	for (int i = 0; i < words.size(); i++)
	{
		if (words[i] == "create" || words[i] == "line")
		{
			words.erase(words.begin() + i);
			i--;
		}
	}
}

// checks whether the last number is after the first word (which should be the only one) meaning that we have a number
// for stroke-width
const bool CreateLine::checkIfStrokeWidthExists(const std::string input)
{
	// finds the position of the last number in the input
	int findLastNumberPos = input.find(nums[nums.size() - 1]);

	// finds the position of the first word in the input
	int findWordPos = input.find(words[0]);

	if (findLastNumberPos > findWordPos)
	{
		// return true if a number for stroke-width exists
		return true;
	}

	// return false otherwise
	return false;
}

// checks whether the color is correct (we know that there is only one word (for stroke)) by going through the vector
// colorChecker
const bool CreateLine::checkIfCorrectColor()
{
	bool isItCorrect = false;
	for (int i = 0; i < colorChecker.size(); i++)
	{
		if (colorChecker[i] == words[0])
		{
			isItCorrect = true;
		}
	}
	if (!isItCorrect)
	{
		// return false if the color is incorrect
		return false;
	}

	// return true if the color is correct
	return true;
}

// returns the size of the vector nums
const int CreateLine::getNumsCount()
{
	return nums.size();
}

// checks if the numbers start with 0
const bool CreateLine::checkForCorrectNumbers() const
{
	for (int i = 0; i < nums.size(); i++)
	{
		// the size needs to be more than 1 because we don't want to include 0 in this check
		if (nums[i].size() > 1 && nums[i][0] == '0')
		{
			// return false if one of the numbers start with 0
			return false;
		}
	}

	// return true otherwise
	return true;
}

// when there is no number for stroke-width meaning that we have 4 numbers from the input
void CreateLine::caseStrokeWidth(std::string & lineForFile)
{
	// we use & since we want to change lineForFile and then give it to the caller
	// note: we are going to write the line for the file ourselves

	// incorrect input if there are at least 2 words
	if (words.size() > 1)
	{
		lineForFile = "";
		return;
	}

	// incorrect if the color is incorrect
	if (!checkIfCorrectColor())
	{
		lineForFile = "";
		return;
	}

	setX1(std::stoi(nums[0]));
	setY1(std::stoi(nums[1]));
	setX2(std::stoi(nums[2]));
	setY2(std::stoi(nums[3]));
	setStrokeWidth(std::stoi(nums[4]));
	setStroke(words[0]);

	lineForFile += "<line x1=\"";
	lineForFile += nums[0];
	lineForFile += "\" y1=\"";
	lineForFile += nums[1];
	lineForFile += "\" x2=\"";
	lineForFile += nums[2];
	lineForFile += "\" y2=\"";
	lineForFile += nums[3];
	lineForFile += "\" stroke=\"";
	lineForFile += stroke;
	lineForFile += "\" stroke-width=\"";
	lineForFile += nums[4];
	lineForFile += "\" />";
}

// when we have a number for stroke-width (5 numbers from the input)
void CreateLine::caseNoStrokeWidth(std::string & lineForFile)
{
	// incorrect if there are at least 2 numbers
	if (words.size() > 1)
	{
		lineForFile = "";
		return;
	}

	// incorrect if the color is incorrect
	if (!checkIfCorrectColor())
	{
		lineForFile = "";
		return;
	}

	setX1(std::stoi(nums[0]));
	setY1(std::stoi(nums[1]));
	setX2(std::stoi(nums[2]));
	setY2(std::stoi(nums[3]));
	setStroke(words[0]);

	lineForFile += "<line x1=\"";
	lineForFile += nums[0];
	lineForFile += "\" y1=\"";
	lineForFile += nums[1];
	lineForFile += "\" x2=\"";
	lineForFile += nums[2];
	lineForFile += "\" y2=\"";
	lineForFile += nums[3];
	lineForFile += "\" stroke=\"";
	lineForFile += stroke;
	lineForFile += "\" />";
}
