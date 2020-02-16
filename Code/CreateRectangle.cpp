#include "CreateRectangle.h"

// determines whether the word count (apart from create and rectangle) is 0 therefore it is a bad input
const bool CreateRectangle::isWordsSizeZero() const
{
	return words.size() == 0;
}

// checks whether the numbers we are given are correct
// the way this function works is that first it stores all the numbers inside a vector
// it stops when the vector has stored exactly Case + 1 numbers (because it gets the word rectangle as its first member)
// we use case to determine how many numbers we should store inside inputNums
// then through a for loop we go through the vector and check whether they are actual numbers (without inputNums[0]
// which is the word rectangle)
const bool CreateRectangle::checkForBadInput(const std::string input, const int Case)
{
	std::vector<std::string> inputNums;
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == ' ')
		{
			std::string instance = "";

			// counts the iterations of the loop
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

			// adds counter - 1 to i because there is no need for i to go through the size of instance 
			// counter - 1 because if we increase with counter i will become i + 1 the next iteration and it will 
			// scip one character which could be vital for the correct behaviour of the function
			if (counter != 0)
				i += counter - 1;
		}

		// stop when we have reached a certain amount of numbers
		if (inputNums.size() == Case + 1)
		{
			// break the loop
			break;
		}
	}

	// go through the vector
	// starts from 1 because inputNums[0] is the word rectangle
	for (int i = 1; i < inputNums.size(); i++)
	{
		for (int j = 0; j < inputNums[i].size(); j++)
		{
			// if the character is not a number return true meaning that there is a bad input
			if (inputNums[i][j] < '0' || inputNums[i][j] > '9')
			{
				return true;
			}
		}
	}

	// return false otherwise
	return false;
}

CreateRectangle::CreateRectangle() : x(INITIAL_VALUE), y(INITIAL_VALUE), height(INITIAL_VALUE), 
					width(INITIAL_VALUE), fill(INITIAL_STRING), stroke(INITIAL_STRING), strokeWidth(INITIAL_VALUE)
{
}

// using a regular expression and a line from the console this is where we get the numbers from the string (the line)
// and puts them into the vector nums which holds the numbers used to create the rectangle
void CreateRectangle::setNums(std::string str, std::regex reg)
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

// same as above only thing is now that we put the words into words (the vector)
void CreateRectangle::setWords(std::string str, std::regex reg)
{
	std::sregex_iterator currentMatch(str.begin(), str.end(), reg);
	std::sregex_iterator lastMatch;

	while (currentMatch != lastMatch)
	{
		std::smatch match = *currentMatch;
		words.push_back(match.str());
		currentMatch++;
	}

	for (int i = 0; i < words.size(); i++)
	{
		// remove create and rectangle because we don't need them
		if (words[i] == "create" || words[i] == "rectangle")
		{
			words.erase(words.begin() + i);
			i--;
		}
	}
}

// function to check whether the last number is after all the words meaning that this is the stroke-width number
const bool CreateRectangle::checkIfStrokeWidthExists(const std::string str)
{
	if (str.find(nums[nums.size() - 1]) > str.find(words[words.size() - 1]))
	{
		// we change the value of stroke-width so that we use this as an indicator that there was a strokeWidth
		// which we will use in the case functions
		strokeWidth = -2;
		return true;
	}
	return false;
}

// function to check if the colors given are correct ones using the vector colorChecker
const bool CreateRectangle::checkIfCorrectColor()
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

		// if it hasn't found a match
		if (!isItCorrect)
		{
			return false;
		}
	}

	return true;
}

// return the size of nums which helps out the caller to determine how many numbers there are and therefore 
// pick a correct case through which to create a rectangle
const int CreateRectangle::getNumsCount()
{
	return nums.size();
}

// checks whether the numbers start with 0 (in which case we return false to indicate that we have incorrect 
// numbers) or not
const bool CreateRectangle::checkForCorrectNumbers() const
{
	for (int i = 0; i < nums.size(); i++)
	{
		// if the number is not 0
		if (nums[i].size() > 1 && nums[i][0] == '0')
		{
			return false;
		}
	}
	return true;
}

// only one word: fill
const bool CreateRectangle::case1Char()
{
	return words.size() == 1;
}

// two words: fill and stroke
const bool CreateRectangle::case2Chars()
{
	return words.size() == 2;
}

// we have 2 numbers: width and height and with lineForFile we can write the line for the file ourselves
// having in mind the different cases for the words
void CreateRectangle::caseNums2(std::string& lineForFile)
{
	setWidth(std::stoi(nums[0]));
	setHeight(std::stoi(nums[1]));

	// if there are more than 2 words we consider this bad input
	if (words.size() > 2)
	{
		lineForFile = "";
		return;
	}

	// checks whether we have correct colors... if not then we return "" to indicate that there was something wrong
	if (!checkIfCorrectColor())
	{
		lineForFile = "";
		return;
	}

	if (case1Char())
	{
		fill = words[0];
		lineForFile += "<rect width=\"";
		lineForFile += nums[0];
		lineForFile += "\" height=\"";
		lineForFile += nums[1];
		lineForFile += "\" fill=\"";
		lineForFile += fill;
	}
	else if (case2Chars())
	{
		fill = words[0];
		stroke = words[1];
		lineForFile += "<rect width=\"";
		lineForFile += nums[0];
		lineForFile += "\" height=\"";
		lineForFile += nums[1];
		lineForFile += "\" fill=\"";
		lineForFile += fill;
		lineForFile += "\" stroke=\"";
		lineForFile += stroke;
	}

	// note: even though this is the third item we are setting to stroke-width and we are in the case where there
	// are 2 numbers from the input, we put this here because we will use it whenever there are 3 numbers including
	// stroke-width
	// we put it in here because we don't want to write another function just for this case, that would mean 
	// doubling the amount of the case functions
	if (strokeWidth == -2)
	{
		strokeWidth = std::stoi(nums[2]);
		lineForFile += "\" stroke-width=\"";
		lineForFile += nums[2];
	}
	lineForFile += "\" />";
}

// this is when we get 3 numbers from the input or potentially 4 (including the stroke-width)
// the same principles apply here as in the above function
void CreateRectangle::caseNums3(std::string& lineForFile)
{
	setX(std::stoi(nums[0]));
	setWidth(std::stoi(nums[1]));
	setHeight(std::stoi(nums[2]));

	// if there are more than 2 words we consider this bad input
	if (words.size() > 2)
	{
		lineForFile = "";
		return;
	}

	// checks whether we have correct colors... if not then we return "" to indicate that there was something wrong
	if (!checkIfCorrectColor())
	{
		lineForFile = "";
		return;
	}
	
	if (case1Char())
	{
		fill = words[0];
		lineForFile += "<rect x=\"";
		lineForFile += nums[0];
		lineForFile += "\" width=\"";
		lineForFile += nums[1];
		lineForFile += "\" height=\"";
		lineForFile += nums[2];
		lineForFile += "\" fill=\"";
		lineForFile += fill;

	}
	else if (case2Chars())
	{
		fill = words[0];
		stroke = words[1];
		lineForFile += "<rect x=\"";
		lineForFile += nums[0];
		lineForFile += "\" width=\"";
		lineForFile += nums[1];
		lineForFile += "\" height=\"";
		lineForFile += nums[2];
		lineForFile += "\" fill=\"";
		lineForFile += fill;
		lineForFile += "\" stroke=\"";
		lineForFile += stroke;
	}

	if (strokeWidth == -2)
	{
		strokeWidth = std::stoi(nums[3]);
		lineForFile += "\" stroke-width=\"";
		lineForFile += nums[3];
	}
	lineForFile += "\" />";
}

// when we get 4 - 5 numbers (if there is a number for stroke-width)
// same principles apply here as in the above case functions
void CreateRectangle::caseNums4(std::string& lineForFile)
{
	setX(std::stoi(nums[0]));
	setY(std::stoi(nums[1]));
	setWidth(std::stoi(nums[2]));
	setHeight(std::stoi(nums[3]));

	// if there are more than 2 words we consider this bad input
	if (words.size() > 2)
	{
		lineForFile = "";
		return;
	}

	// checks whether we have correct colors... if not then we return "" to indicate that there was something wrong
	if (!checkIfCorrectColor())
	{
		lineForFile = "";
		return;
	}

	if (case1Char())
	{
		fill = words[0];
		lineForFile += "<rect x=\"";
		lineForFile += nums[0];
		lineForFile += "\" y=\"";
		lineForFile += nums[1];
		lineForFile += "\" width=\"";
		lineForFile += nums[2];
		lineForFile += "\" height=\"";
		lineForFile += nums[3];
		lineForFile += "\" fill=\"";
		lineForFile += fill;
	}
	else if (case2Chars())
	{
		fill = words[0];
		stroke = words[1];
		lineForFile += "<rect x=\"";
		lineForFile += nums[0];
		lineForFile += "\" y=\"";
		lineForFile += nums[1];
		lineForFile += "\" width=\"";
		lineForFile += nums[2];
		lineForFile += "\" height=\"";
		lineForFile += nums[3];
		lineForFile += "\" fill=\"";
		lineForFile += fill;
		lineForFile += "\" stroke=\"";
		lineForFile += stroke;
	}

	if (strokeWidth == -2)
	{
		strokeWidth = std::stoi(nums[4]);
		lineForFile += "\" stroke-width=\"";
		lineForFile += nums[4];
	}
	lineForFile += "\" />";
}

// when we get 5 numbers
// same principles as in the above case functions
void CreateRectangle::caseNums5(std::string& lineForFile)
{
	setX(std::stoi(nums[0]));
	setY(std::stoi(nums[1]));
	setWidth(std::stoi(nums[2]));
	setHeight(std::stoi(nums[3]));
	setStrokeWidth(std::stoi(nums[4]));

	// if there are more than 2 words we consider this bad input
	if (words.size() > 2)
	{
		lineForFile = "";
		return;
	}

	// checks whether we have correct colors... if not then we return "" to indicate that there was something wrong
	if (!checkIfCorrectColor())
	{
		lineForFile = "";
		return;
	}

	if (case1Char())
	{
		fill = words[0];
		lineForFile += "<rect x=\"";
		lineForFile += nums[0];
		lineForFile += "\" y=\"";
		lineForFile += nums[1];
		lineForFile += "\" width=\"";
		lineForFile += nums[2];
		lineForFile += "\" height=\"";
		lineForFile += nums[3];
		lineForFile += "\" fill=\"";
		lineForFile += fill;
	}
	else if (case2Chars())
	{
		fill = words[0];
		stroke = words[1];
		lineForFile += "<rect x=\"";
		lineForFile += nums[0];
		lineForFile += "\" y=\"";
		lineForFile += nums[1];
		lineForFile += "\" width=\"";
		lineForFile += nums[2];
		lineForFile += "\" height=\"";
		lineForFile += nums[3];
		lineForFile += "\" fill=\"";
		lineForFile += fill;
		lineForFile += "\" stroke=\"";
		lineForFile += stroke;
	}

	lineForFile += "\" stroke-width=\"";
	lineForFile += nums[4];
	lineForFile += "\" />";
}

// normal setters
void CreateRectangle::setX(const double x)
{
	this->x = x;
}

void CreateRectangle::setY(const double y)
{
	this->y = y;
}

void CreateRectangle::setHeight(const double height)
{
	this->height = height;
}

void CreateRectangle::setWidth(const double width)
{
	this->width = width;
}

void CreateRectangle::setStrokeWidth(const double strokeWidth)
{
	this->strokeWidth = strokeWidth;
}

void CreateRectangle::setFill(const std::string fill)
{
	this->fill = fill;
}

void CreateRectangle::setStroke(const std::string stroke)
{
	this->stroke = stroke;
}

// getters
const double CreateRectangle::getX() const
{
	return x;
}

const double CreateRectangle::getY() const
{
	return y;
}

const double CreateRectangle::getHeight() const
{
	return height;
}

const double CreateRectangle::getWidth() const
{
	return width;
}

const double CreateRectangle::getStrokeWidth() const
{
	return strokeWidth;
}

const std::string CreateRectangle::getFill() const
{
	return fill;
}

const std::string CreateRectangle::getStroke() const
{
	return stroke;
}
