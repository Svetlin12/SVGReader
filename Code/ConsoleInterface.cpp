#include "ConsoleInterface.h"

// set the instance to nullptr at the beginning
ConsoleInterface* ConsoleInterface::instance = nullptr;

void ConsoleInterface::getInputFromFile()
{
	inputFromFile = Reader::getInstance()->getMatches();
}

const std::string ConsoleInterface::getTypeFromInput(const std::string input)
{
	int find1 = input.find("rect");
	int find2 = input.find("circle");
	int find3 = input.find("line");

	if (find1 != std::string::npos)
	{
		return "rect";
	}
	else if (find2 != std::string::npos)
	{
		return "circle";
	}
	else if (find3 != std::string::npos)
	{
		return "line";
	}
	else
	{
		return "";
	}
}

const std::string ConsoleInterface::getMatch(std::string str, std::regex reg)
{
	std::sregex_iterator currentMatch(str.begin(), str.end(), reg);
	std::sregex_iterator lastMatch;

	if (currentMatch != lastMatch)
	{
		// returns the first match found by the regular expression reg in the string str
		return (*currentMatch).str();
	}
	else
	{
		// if no match is found return the empty string so that the caller knows in which case he is
		return "";
	}
}

void ConsoleInterface::getNumbersToVector(std::vector<std::string>& vector, std::string str, std::regex reg)
{
	std::sregex_iterator currentMatch(str.begin(), str.end(), reg);
	std::sregex_iterator lastMatch;

	// while there is a match
	while (currentMatch != lastMatch)
	{
		std::smatch match = *currentMatch;
		// pushes each match found in the string str by the regular expression reg into the vector
		// we intend to change an already existing vector so that's why we need &
		vector.push_back(match.str());

		// move to the next match
		currentMatch++;
	}
}

const double ConsoleInterface::getNumberFromString(std::string str)
{
	// if the string is an empty one then return 0 because this function is used in translate
	// and we cannot set horizontal or vertical number as negative values because they are valid
	// if horizontal or vertical number are set to 0 then they cannot change the figures
	if (str == "")
	{
		return 0;
	}

	// a regular expression designed to find a number (positive and negative) - even if this number has a decimal point
	std::regex numFinder("[\\d\.-]+");

	// gets the first match in str (or because of the use of this program - the only match in str (str will have 
	// only strings of the type vertical = ... and horizontal = ...))
	std::string number = getMatch(str, numFinder);

	// initiate the number
	double numInDigits = 0;

	// if the number is negative
	if (number[0] == '-')
	{
		// erase the minus so that we can use stoi
		number.erase(number.begin());
		numInDigits = -(std::stoi(number));
	}
	// otherwise
	else
	{
		numInDigits = std::stoi(number);
	}
	return numInDigits;
}

// craetes a line for the file
// we use this function to update the lines in the file when we translate a figure
const std::string ConsoleInterface::makeLineForFile(Shape * shape)
{
	// initiate the string and add a whitespace 
	std::string toAppendToFile = " ";

	// if the figure is a rectangle
	if (shape->getType() == "rectangle")
	{
		toAppendToFile += "<rect ";
		// if x exists
		if (dynamic_cast<Rect*>(shape)->getX() != -1)
		{
			toAppendToFile += "x=\"";
			toAppendToFile += std::to_string((int)dynamic_cast<Rect*>(shape)->getX());
			toAppendToFile += "\" ";
		}
		// if y exists
		if (dynamic_cast<Rect*>(shape)->getY() != -1)
		{
			toAppendToFile += "y=\"";
			toAppendToFile += std::to_string((int)dynamic_cast<Rect*>(shape)->getY());
			toAppendToFile += "\" ";
		}
		// the rest are sure to exists since if they don't then the figure would not exist
		toAppendToFile += "width=\"";
		toAppendToFile += std::to_string((int)dynamic_cast<Rect*>(shape)->getWidth());
		toAppendToFile += "\" height=\"";
		toAppendToFile += std::to_string((int)dynamic_cast<Rect*>(shape)->getHeight());
		toAppendToFile += "\" fill=\"";
		toAppendToFile += dynamic_cast<Rect*>(shape)->getFill();
		toAppendToFile += "\" ";

		// if stroke exists
		if (dynamic_cast<Rect*>(shape)->getStroke() != "")
		{
			toAppendToFile += "stroke=\"";
			toAppendToFile += dynamic_cast<Rect*>(shape)->getStroke();
			toAppendToFile += "\" ";
		}
		// if stroke-width exists
		if (dynamic_cast<Rect*>(shape)->getStrokeWidth() != -1)
		{
			toAppendToFile += "stroke-width=\"";
			toAppendToFile += std::to_string((int)dynamic_cast<Rect*>(shape)->getStrokeWidth());
			toAppendToFile += "\" ";
		}

		// finish the line
		toAppendToFile += "/>";
	}
	// if the shape is a circle
	else if (shape->getType() == "circle")
	{
		// cx, cy, r and fill are sure to exists because without any one of them the circle would have not existed
		toAppendToFile += "<circle cx=\"";
		toAppendToFile += std::to_string((int)dynamic_cast<Circle*>(shape)->getCX());
		toAppendToFile += "\" cy=\"";
		toAppendToFile += std::to_string((int)dynamic_cast<Circle*>(shape)->getCY());
		toAppendToFile += "\" r=\"";
		toAppendToFile += std::to_string((int)dynamic_cast<Circle*>(shape)->getR());
		toAppendToFile += "\" fill=\"";
		toAppendToFile += dynamic_cast<Circle*>(shape)->getFill();
		toAppendToFile += "\" ";

		// if stroke exists
		if (dynamic_cast<Circle*>(shape)->getStroke() != "")
		{
			toAppendToFile += "stroke=\"";
			toAppendToFile += dynamic_cast<Circle*>(shape)->getStroke();
			toAppendToFile += "\" ";
		}

		// if stroke-width exists
		if (dynamic_cast<Circle*>(shape)->getStrokeWidth() != -1)
		{
			toAppendToFile += "stroke-width=\"";
			toAppendToFile += std::to_string((int)dynamic_cast<Circle*>(shape)->getStrokeWidth());
			toAppendToFile += "\" ";
		}

		// finish the line
		toAppendToFile += "/>";
	}
	else
	{
		// x1, y1, x2, y2 and stroke are sure to exists because otherwise the line would not exist
		toAppendToFile += "<line x1=\"";
		toAppendToFile += std::to_string((int)dynamic_cast<Line*>(shape)->getX1());
		toAppendToFile += "\" y1=\"";
		toAppendToFile += std::to_string((int)dynamic_cast<Line*>(shape)->getY1());
		toAppendToFile += "\" x2=\"";
		toAppendToFile += std::to_string((int)dynamic_cast<Line*>(shape)->getX2());
		toAppendToFile += "\" y2=\"";
		toAppendToFile += std::to_string((int)dynamic_cast<Line*>(shape)->getY2());
		toAppendToFile += "\" stroke=\"";
		toAppendToFile += dynamic_cast<Line*>(shape)->getStroke();

		// if stroke-width exists
		if (dynamic_cast<Line*>(shape)->getStrokeWidth() != -1)
		{
			toAppendToFile += "\" stroke-width=\"";
			toAppendToFile += std::to_string((int)dynamic_cast<Line*>(shape)->getStrokeWidth());
		}

		// finish the line
		toAppendToFile += "\" />";
	}

	return toAppendToFile;
}

// checks the input in the translate function
// note: the input that we will get as a parameter in this function is of the type:
// vertical = ...
// horizontal = ...
// we won't be checking the full input here
const bool ConsoleInterface::checkTranslateInput(const std::string input)
{
	// go through each character
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == '=')
		{
			for (int j = i + 1; j < input.size(); j++)
			{
				if (input[j] == '"')
				{
					for (int k = j + 1; k < input.size(); k++)
					{
						// return true (meaning that the input is correct)if the k-th character reaches the closing
						// quotation mark and if this was not the second iteration of the loop
						if (input[k] == '"' && k != j + 2)
						{
							return true;
						}

						// go to the next iteration if the k-th character is one of those (the numbers might be of type
						// double, there might be whitespaces before or after the number and lastly the number might
						// be negative
						if (input[k] == ' ' || input[k] == '-' || input[k] == '.')
						{
							continue;
						}

						// return false (meaning that the input is incorrect) if the k-th character is not a number
						if (input[k] < '0' || input[k] > '9')
						{
							return false;
						}
					}
					break;
				}

				// same as above for the outer loop
				if (input[j] == ' ' || input[j] == '-' || input[j] == '.')
				{
					continue;
				}

				// if it finds a character it returns false and therefore stops the function
				if (input[j] < '0' || input[j] > '9')
				{
					return false;
				}
			}
		}
	}

	return true;
}

const bool ConsoleInterface::compareTwoStrings(const std::string string1, const std::string string2)
{
	// string2 has smaller size than size1 because string1 we get from a regular expresion match and it might
	// contain a few extra whitespaces
	for (int i = 0; i < string2.size(); i++)
	{
		if (string1[i] != string2[i])
		{
			return false;
		}
	}
	return true;
}

const std::string ConsoleInterface::getVerticalFromInput(const std::string input)
{
	// finds vertical position in input
	int findVertical = input.find("vertical");

	// finds horizontal position in input in order to determine if vertical is after horizontal or before it
	// this is key to determining where to stop the loop down below
	int findHorizontal = input.find("horizontal");

	// we will return this string, but first we will use it to store the vertical=...
	std::string stringToPass = "";

	// if vertical=... and horizontal = ... exist and the latter is the last
	if (findVertical != std::string::npos && findHorizontal != std::string::npos && findVertical < findHorizontal)
	{
		// start from the number vertical = ... starts and finish when i reaches the number from which horizontal = ... starts
		for (int i = findVertical; i < findHorizontal; i++)
		{
			// push_back each character
			stringToPass.push_back(input[i]);
		}
	}
	// if vertical = ... exists and horizontal = ... doesn't or they both exist but vertical = ... is after horizontal = ... 
	else if ((findVertical != std::string::npos && findHorizontal == std::string::npos) ||
		    (findVertical != std::string::npos && findHorizontal != std::string::npos && findVertical > findHorizontal))
	{
		 // start from where vertical = ... starts and finish at the end of the string
		 for (int i = findVertical; i < input.size(); i++)
		 {
		 	stringToPass.push_back(input[i]);
		 }
	}

	// if stringToPass has been changed and the last character is a whitespaces start deleting until it finds
	// a non whitespace character
	if (stringToPass != "" && stringToPass[stringToPass.size() - 1] == ' ')
	{
		for (int i = stringToPass.size() - 1; stringToPass[i] == ' '; i--)
		{
			stringToPass.erase(stringToPass.begin() + i);

		}
	}

	return stringToPass;
}

// this function works the same as the above function only now we do it to extract horizontal = ...
const std::string ConsoleInterface::getHorizontalFromInput(const std::string input)
{
	// position of horizontal = ...
	int findHorizontal = input.find("horizontal");

	// position of vertical = ...
	int findVertical = input.find("vertical");

	std::string stringToPass = "";

	// if horizontal = ... and vertical = ... exist and the latter is the before horizontal = ... or if only horizontal exists
	if ((findHorizontal != std::string::npos && findVertical != std::string::npos && findHorizontal > findVertical)
		|| (findHorizontal != std::string::npos && findVertical == std::string::npos))
	{
		for (int i = findHorizontal; i < input.size(); i++)
		{
			stringToPass.push_back(input[i]);
		}
	}
	// if horizontal = ... and vertical = ... exist and the latter the last
	else if (findHorizontal != std::string::npos && findVertical != std::string::npos && findHorizontal < findVertical)
	{
		for (int i = findHorizontal; i < findVertical; i++)
		{
			stringToPass.push_back(input[i]);
		}
	}

	// delete the whitespaces at the end
	if (stringToPass != "" && stringToPass[stringToPass.size() - 1] == ' ')
	{
		for (int i = stringToPass.size() - 1; stringToPass[i] == ' '; i--)
		{
			stringToPass.erase(stringToPass.begin() + i);

		}
	}

	return stringToPass;
}

// we check the input of within here
// we store all the words and numbers inside a vector and then we check only the numbers if they are correctly written
// because we know that there are 2 words and they are within and either rect, line or circle
// the cases in which they are not correctly written as well are covered inside within and in main.cpp
const bool ConsoleInterface::checkWithinInput(const std::string input)
{
	// the vector in which we will store the words and the numbers
	std::vector<std::string> wordsFromInput;

	for (int i = 0; i < input.size(); i++)
	{
		// skip the whitespaces
		if (input[i] == ' ')
		{
			continue;
		}
		else
		{
			std::string wordToPass = "";
			// continue through the string (input) until input[j] isn't whitespace or j hasn't reached the 
			// end of the string (we make j a reference because we want to continue from the current i and 
			// change i each time j increases because if we don't change i here then in the next iterations it
			// would add parts of the word that we just added to the vector, for example:
			// the input is "within circle 0 0 5"
			// if we don't change i the words inside wordToPass would be: within, ithin, thin, hin, in, n, circle,
			// ircle, rcle, cle, le, e
			// if we change i the wouds are: within, circle
			// the same thing would happen to the numbers as well if they are multi-digit ones
			for (int& j = i; input[j] != ' ' && j < input.size(); j++)
			{
				wordToPass.push_back(input[j]);
			}

			wordsFromInput.push_back(wordToPass);
		}
	}

	// skip the first two words and start checking the numbers for corectness
	for (int i = 2; i < wordsFromInput.size(); i++)
	{
		for (int j = 0; j < wordsFromInput[i].size(); j++)
		{
			if (wordsFromInput[i][j] < '0' || wordsFromInput[i][j] > '9')
			{
				// return false if any of the numbers is incorrect (it might not be number)
				return false;
			}

			if (j == 0 && wordsFromInput[i].size() > 1 && wordsFromInput[i][j] == '0')
			{
				return false;
			}
		}
	}

	// return true if the numbers are correct
	return true;
}

// gets the information just obtained from getInputFromFile() in order to create the figures it represents
void ConsoleInterface::getFigures()
{
	for (int i = 0; i < inputFromFile.size(); i++)
	{
		// create a figure (we don't know what it is - that's why inheritance there is really helpful)
		Shape* instance;

		// gets the type of figure we should create
		std::string type = getTypeFromInput(inputFromFile[i]);

		// if it is a rectangle
		if (type == "rect")
		{
			instance = new Rect;
			// sets all members by giving the line from the file to the function which will extract the data for
			// each geometric property of the rectangle and set it to the newly created rectangle
			instance->setAllMembers(inputFromFile[i]);
			figures.push_back(instance);
		}
		// if it is a circle
		else if (type == "circle")
		{
			instance = new Circle;
			// sets all members by the same principles as in the above function
			instance->setAllMembers(inputFromFile[i]);
			figures.push_back(instance);
		}
		// if it is a line
		else if (type == "line")
		{
			instance = new Line;
			// same principles as the above ones
			instance->setAllMembers(inputFromFile[i]);
			figures.push_back(instance);
		}
	}
}

// default constructor - we don't have to initialize anything since we are only dealing with vectors
ConsoleInterface::ConsoleInterface()
{
}

// destructor - we need to delete the contents of the vector figures manualy because each one is a pointer 
// and the compiler won't delete it correctly. The other vector contains strings so there is no need to do anything
// there because the compiler will handle it just fine
ConsoleInterface::~ConsoleInterface()
{
	for (int i = 0; i < figures.size(); i++)
	{
		delete figures[i];
	}
	figures.clear();
}

// we don't need to do anything here - we just needed a definition in order to prevent the compiler from creating it
// because then it would be a public one and the Singleton we just implemented will be incomplete
ConsoleInterface::ConsoleInterface(const ConsoleInterface & c)
{
}

// same as above
ConsoleInterface & ConsoleInterface::operator=(const ConsoleInterface & c)
{
	return *this;
}

// explaantion of this function is in ConsoleInterface.h
const int ConsoleInterface::countNumberOfWordsAndNums(const std::string input)
{
	std::regex reg(".[^ ]+");

	std::sregex_iterator currentMatch(input.begin(), input.end(), reg);
	std::sregex_iterator lastMatch;

	// counts the numbers and words in str
	int counter = 0;

	// while there is a match
	while (currentMatch != lastMatch)
	{
		// increase counter by 1
		counter++;

		// move on to the next match
		currentMatch++;
	}

	return counter;
}

// Singleton implementation here - creates the only instance of the class
ConsoleInterface * ConsoleInterface::getInstance()
{
	if (nullptr == instance)
	{
		instance = new ConsoleInterface();
	}
	return instance;
}

// Singleton implementation - releases this and Parser's instance
void ConsoleInterface::releaseInstance()
{
	Reader::getInstance()->releaseInstance();
	if (nullptr != instance)
	{
		delete instance;
		instance = nullptr;
	}
}

// prints the data for each figure on the console using the pure virtual function print in the base class Shape
void ConsoleInterface::print() const
{
	for (int i = 0; i < figures.size(); i++)
	{
		// the number in front of each figure (starts from 1 until the size of figures)
		std::cout << i + 1 << ". ";
		figures[i]->print();
	}
}

// the implementation of one of the 5 functions that we need to create
void ConsoleInterface::create(const std::string input)
{
	// these three will determine whether we have a rectangle, circle or line to create or 
	// possibly no figure meaning that there is a bad input
	int findRectangle = input.find("rectangle");
	int findCircle = input.find("circle");
	int findLine = input.find("line");

	// this will serve as a line in the file for the new figure we just created
	std::string toAppendToFile = " ";

	// if the figure we should create is a rectangle
	if (findRectangle != std::string::npos)
	{
		// minimum words: create, rectangle, (number) for width, (number) for height, (color) for fill - 5 at total
		// maximum words: create, rectangle, (number) for x, (number) for y, (number) for width, (number) for height,
		// (color) for fill, (color) for stroke, (number) for stroke-width - 9 at total
		// any number of words and numbers not inside this range ([5,9]) is considered bad input
		if (countNumberOfWordsAndNums(input) < 5 || countNumberOfWordsAndNums(input) > 9)
		{
			std::cout << "Wrong input! Try again..." << std::endl;
			return;
		}

		// start creating the rectangle
		CreateRectangle cr;

		// regular expression designed to find numbers
		std::regex reg1("([\\d]+)");
		
		// regular expression designed to find words
		std::regex reg2("([A-Za-z]+)");

		// gets the numbers from the input inside a vector in cr
		cr.setNums(input, reg1);

		// if the size of the vector that we just put a bunch of numbers is less than 2 then this is considered 
		// bad input (there should always be numbers for width and height)
		if (cr.getNumsCount() < 2)
		{
			std::cout << "Too few information to work with! Try again..." << std::endl;
			return;
		}

		// checks if the numbers inside that vector are correct (meaning that they don't start with 0)
		if (!cr.checkForCorrectNumbers())
		{
			std::cout << "There are numbers that start with 0! Try again..." << std::endl;
			return;
		}

		// puts the words (that is except create and rectangle) from the input inside the vector words which
		// is a member of CreateRectangle
		cr.setWords(input, reg2);
		
		// check if there are words apart from create and rectangle
		// if not then that's a bad input 
		if (cr.isWordsSizeZero())
		{
			std::cout << "Your input doesn't contain a color for fill! Try again..." << std::endl;
			return;
		}

		// create a rectangle that will represent the new figure and that will be added to the vector figures
		Shape* newRect = new Rect;

		// if there was a number for stroke-width
		if (cr.checkIfStrokeWidthExists(input))
		{
			// if the numbers are 4 + stroke-width
			if (cr.getNumsCount() == 5)
			{
				// check the 4 numbers for correctness
				if (cr.checkForBadInput(input, 4))
				{
					std::cout << "There is a mistake in some of the numbers! Try again..." << std::endl;

					// delete the new instance we just created to free the memory that we took
					delete newRect;
					return;
				}

				// this will set all the properties of the rectangle
				cr.caseNums5(toAppendToFile);

				// check if the above function has ended well
				if (toAppendToFile == "")
				{
					std::cout << "Bad input!" << std::endl;

					// free the memory we just took
					delete newRect;
					return;
				}

				// transfer the data from cr to the new instance newRect
				dynamic_cast<Rect*>(newRect)->setAsNumX(cr.getX());
				dynamic_cast<Rect*>(newRect)->setAsNumY(cr.getY());
				dynamic_cast<Rect*>(newRect)->setAsNumWidth(cr.getWidth());
				dynamic_cast<Rect*>(newRect)->setAsNumHeight(cr.getHeight());
				dynamic_cast<Rect*>(newRect)->setAsNumStrokeWidth(cr.getStrokeWidth());
				dynamic_cast<Rect*>(newRect)->setFill(cr.getFill());
				dynamic_cast<Rect*>(newRect)->setStroke(cr.getStroke());
			}

			// if the numbers are 3 + stroke-width
			else if (cr.getNumsCount() == 4)
			{
				// check the three numbers for correctness
				if (cr.checkForBadInput(input, 3))
				{
					std::cout << "There is a mistake in some of the numbers! Try again..." << std::endl;

					// deallocate the memory we just took
					delete newRect;
					return;
				}

				// sets the 3 numbers to their corresponding properties and the last one goes to stroke-width
				cr.caseNums3(toAppendToFile);

				// check if the function has ended correctly
				if (toAppendToFile == "")
				{
					std::cout << "Bad input!" << std::endl;

					// deallocate the memory we just took
					delete newRect;
					return;
				}

				// transfer the data from cr to the new instance newRect
				dynamic_cast<Rect*>(newRect)->setAsNumX(cr.getX());
				dynamic_cast<Rect*>(newRect)->setAsNumY(cr.getY());
				dynamic_cast<Rect*>(newRect)->setAsNumWidth(cr.getWidth());
				dynamic_cast<Rect*>(newRect)->setAsNumHeight(cr.getHeight());
				dynamic_cast<Rect*>(newRect)->setAsNumStrokeWidth(cr.getStrokeWidth());
				dynamic_cast<Rect*>(newRect)->setFill(cr.getFill());
				dynamic_cast<Rect*>(newRect)->setStroke(cr.getStroke());
			}
			// the numbers are 2 + stroke-width
			else if (cr.getNumsCount() == 3)
			{
				// checks the correctness of those 2 numbers
				if (cr.checkForBadInput(input, 2))
				{
					std::cout << "There is a mistake in some of the numbers! Try again..." << std::endl;

					// frees the memory that we just took
					delete newRect;
					return;
				}

				// sets width, height and stroke-width
				cr.caseNums2(toAppendToFile);

				// checks if the function ended correctly
				if (toAppendToFile == "")
				{
					std::cout << "Bad input!" << std::endl;

					// frees the memory that has just been taken
					delete newRect;
					return;
				}

				// transfer the data from cr to the instance newRect
				dynamic_cast<Rect*>(newRect)->setAsNumX(cr.getX());
				dynamic_cast<Rect*>(newRect)->setAsNumY(cr.getY());
				dynamic_cast<Rect*>(newRect)->setAsNumWidth(cr.getWidth());
				dynamic_cast<Rect*>(newRect)->setAsNumHeight(cr.getHeight());
				dynamic_cast<Rect*>(newRect)->setAsNumStrokeWidth(cr.getStrokeWidth());
				dynamic_cast<Rect*>(newRect)->setFill(cr.getFill());
				dynamic_cast<Rect*>(newRect)->setStroke(cr.getStroke());
			}
		}
		// if there is no number for stroke-width
		else
		{
			// if the numbers are 4
			if (cr.getNumsCount() == 4)
			{
				// check those 4 numbers for correctness
				if (cr.checkForBadInput(input, 4))
				{
					std::cout << "There is a mistake in some of the numbers! Try again..." << std::endl;

					// free the memory that we just took
					delete newRect;
					return;
				}

				// sets the 4 numbers to x, y, width and height
				cr.caseNums4(toAppendToFile);

				// checks whether the above function ended well
				if (toAppendToFile == "")
				{
					std::cout << "Bad input!" << std::endl;

					// free the memory we just took
					delete newRect;
					return;
				}

				// transfer the data from cr to newRect
				dynamic_cast<Rect*>(newRect)->setAsNumX(cr.getX());
				dynamic_cast<Rect*>(newRect)->setAsNumY(cr.getY());
				dynamic_cast<Rect*>(newRect)->setAsNumWidth(cr.getWidth());
				dynamic_cast<Rect*>(newRect)->setAsNumHeight(cr.getHeight());
				dynamic_cast<Rect*>(newRect)->setAsNumStrokeWidth(cr.getStrokeWidth());
				dynamic_cast<Rect*>(newRect)->setFill(cr.getFill());
				dynamic_cast<Rect*>(newRect)->setStroke(cr.getStroke());
			}
			// if the numbers are 3
			else if (cr.getNumsCount() == 3)
			{
				// check the numbers for correctness
				if (cr.checkForBadInput(input, 3))
				{
					std::cout << "There is a mistake in some of the numbers! Try again..." << std::endl;

					// free the memory that we just took
					delete newRect;
					return;
				}

				// sets numbers to x, width and height
				cr.caseNums3(toAppendToFile);

				// checks whether the above function ended well
				if (toAppendToFile == "")
				{
					std::cout << "Bad input!" << std::endl;

					// free the memory we just took
					delete newRect;
					return;
				}

				// transfer the information from cr to newRect
				dynamic_cast<Rect*>(newRect)->setAsNumX(cr.getX());
				dynamic_cast<Rect*>(newRect)->setAsNumY(cr.getY());
				dynamic_cast<Rect*>(newRect)->setAsNumWidth(cr.getWidth());
				dynamic_cast<Rect*>(newRect)->setAsNumHeight(cr.getHeight());
				dynamic_cast<Rect*>(newRect)->setAsNumStrokeWidth(cr.getStrokeWidth());
				dynamic_cast<Rect*>(newRect)->setFill(cr.getFill());
				dynamic_cast<Rect*>(newRect)->setStroke(cr.getStroke());
			}
			// if the numbers are 2
			else if (cr.getNumsCount() == 2)
			{
				// check the 2 numbers for correctness
				if (cr.checkForBadInput(input, 2))
				{
					std::cout << "There is a mistake in some of the numbers! Try again..." << std::endl;

					// free the memory that we just took
					delete newRect;
					return;
				}

				// sets the numbers to width and height
				cr.caseNums2(toAppendToFile);

				// check if the above function ended well
				if (toAppendToFile == "")
				{
					std::cout << "Bad input!" << std::endl;

					// free the memory that we just took
					delete newRect;
					return;
				}

				// transfer the information from cr to newRect
				dynamic_cast<Rect*>(newRect)->setAsNumX(cr.getX());
				dynamic_cast<Rect*>(newRect)->setAsNumY(cr.getY());
				dynamic_cast<Rect*>(newRect)->setAsNumWidth(cr.getWidth());
				dynamic_cast<Rect*>(newRect)->setAsNumHeight(cr.getHeight());
				dynamic_cast<Rect*>(newRect)->setAsNumStrokeWidth(cr.getStrokeWidth());
				dynamic_cast<Rect*>(newRect)->setFill(cr.getFill());
				dynamic_cast<Rect*>(newRect)->setStroke(cr.getStroke());
			}
		}

		// add the line corresponding to that figure in order to add it to the file
		inputFromFile.push_back(toAppendToFile);

		// put the new figure inside the vector figures
		figures.push_back(newRect);

		// a message to the console that the function finished working correctly
		std::cout << "Successfully created rectangle (" << figures.size() << ")" << std::endl;
	}
	// if the figure we should create is a circle
	else if (findCircle != std::string::npos)
	{
		// minimum amount of words: create, circle, (number) for cx, (number) for cy, (number) for r, (color)
		// for fill
		// maximum amount of words: create, circle, (number) for cx, (number) for cy, (number) for r, (color)
		// for fill, (color) for stroke, (number) for stroke-width
		// any number of words out of this range ([6,8]) is considered as bad input
		if (countNumberOfWordsAndNums(input) < 6 || countNumberOfWordsAndNums(input) > 8)
		{
			std::cout << "Wrong input! Try again..." << std::endl;
			return;
		}

		// start creating the circle
		CreateCircle cc;

		// regular expression used to find numbers in string
		std::regex reg1("([\\d]+)");

		// regular expression used to find words in string
		std::regex reg2("([A-Za-z]+)");

		// puts all numbers from the input to a vector inside cc
		cc.setNums(input, reg1);

		// check if the numbers we just added to that vector don't start with 0 in which case it is considered bad
		// input
		if (!cc.checkForCorrectNumbers())
		{
			std::cout << "Some of the numbers start with 0! Try again..." << std::endl;
			return;
		}

		// extracts the words (excluding create and circle) from the input and putting them inside a vector in cc
		cc.setWords(input, reg2);

		// if there are no other words than create and circle then that is a bad input
		if (cc.isWordsCountZero())
		{
			std::cout << "There is no color for the fill! Try again..." << std::endl;
			return;
		}

		// this will be the instance that we will add to the vector figures (it will represent the figure)
		Shape* newCircle = new Circle;

		// if there is a number for stroke-width
		if (cc.checkIfStrokeWidthExists(input))
		{
			// checks whether the numbers are correct and there are no words in their place, or no mix of the two
			if (cc.checkForBadInput(input))
			{
				std::cout << "There is a mistake in some of the numbers! Try again..." << std::endl;

				// free the memory that we just took
				delete newCircle;
				return;
			}

			// sets the number to cx, cy, r and stroke-width
			cc.caseNums4(toAppendToFile);

			// check whether the above function ended correctly
			if (toAppendToFile == "")
			{
				std::cout << "Bad input!" << std::endl;

				// free the memory we just took 
				delete newCircle;
				return;
			}

			// transfer the information from cc to newCircle
			dynamic_cast<Circle*>(newCircle)->setAsNumCX(cc.getCX());
			dynamic_cast<Circle*>(newCircle)->setAsNumCY(cc.getCY());
			dynamic_cast<Circle*>(newCircle)->setAsNumR(cc.getR());
			dynamic_cast<Circle*>(newCircle)->setAsNumStrokeWidth(cc.getStrokeWidth());
			dynamic_cast<Circle*>(newCircle)->setFill(cc.getFill());
			dynamic_cast<Circle*>(newCircle)->setStroke(cc.getStroke());
		}
		// if there is no number for stroke-width
		else
		{
			// checks whether the numbers are correct and there are no words in their place, or no mix of the two
			if (cc.checkForBadInput(input))
			{
				std::cout << "There is a mistake in some of the numbers! Try again..." << std::endl;

				// free the memory we just took
				delete newCircle;
				return;
			}

			// sets the numbers to cx, cy and r
			cc.caseNums3(toAppendToFile);

			// checks whether the above function ended correctly
			if (toAppendToFile == "")
			{
				std::cout << "Bad input!" << std::endl;

				// free the memory we just took
				delete newCircle;
				return;
			}

			// transfer the information from cc to newCircle
			dynamic_cast<Circle*>(newCircle)->setAsNumCX(cc.getCX());
			dynamic_cast<Circle*>(newCircle)->setAsNumCY(cc.getCY());
			dynamic_cast<Circle*>(newCircle)->setAsNumR(cc.getR());
			dynamic_cast<Circle*>(newCircle)->setAsNumStrokeWidth(cc.getStrokeWidth());
			dynamic_cast<Circle*>(newCircle)->setFill(cc.getFill());
			dynamic_cast<Circle*>(newCircle)->setStroke(cc.getStroke());
		}

		// add the line for the file corresponding to the new figure
		inputFromFile.push_back(toAppendToFile);

		// add the new figure
		figures.push_back(newCircle);

		// message to let the user know that the figure has been successfully created
		std::cout << "Successfully created circle (" << figures.size() << ")" << std::endl;
	}
	// if the figure we should create is a line
	else if (findLine != std::string::npos)
	{
		// minimum amount of words: create, line, (number) for x1, (number) for y1, (number) for x2, (number) for
		// y2, (color) for stroke
		// maximum amount of words: create, line, (number) for x1, (number) for y1, (number) for x2, (number) for y2,
		// (color) for stroke, (number) for stroke-width
		// any number outside this range ([7,8]) is considered bad input
		if (countNumberOfWordsAndNums(input) < 7 || countNumberOfWordsAndNums(input) > 8)
		{
			std::cout << "Wrong input! Try again..." << std::endl;
			return;
		}

		// start creating the line
		CreateLine cl;
		
		// regular expression used to find the numbers in a string
		std::regex reg1("([\\d]+)");

		// regular expression used to find the words in a string
		std::regex reg2("([A-Za-z]+)");

		// puts the numbers from the input inside a vector in cl
		cl.setNums(input, reg1);

		// checks if those numbers don't start with 0
		if (!cl.checkForCorrectNumbers())
		{
			std::cout << "Some of the numbers start with 0! Try again..." << std::endl;
			return;
		}

		// puts the words (excluding create and line) from the input inside a vector in cl
		cl.setWords(input, reg2);

		// checks whether there are words apart from create and line
		if (cl.isWordsCountZero())
		{
			std::cout << "There is no color for stroke! Try again..." << std::endl;
			return;
		}

		// see the explanation in CreateLine.cpp
		if (cl.checkIfBadInput(input))
		{
			std::cout << "Wrong numbers! Try again..." << std::endl;
			return;
		}

		// we will add newLine to figures vector
		Shape* newLine = new Line;

		// if there is a number for stroke-width
		if (cl.checkIfStrokeWidthExists(input))
		{
			// sets the numbers to x1, y1, x2, y2, stroke, stroke-width
			cl.caseStrokeWidth(toAppendToFile);

			// checks whether the above function ended well
			if (toAppendToFile == "")
			{
				std::cout << "Bad input!" << std::endl;
				// free the memory that we just took
				delete newLine;
				return;
			}

			// transfer the information from cl to newLine
			dynamic_cast<Line*>(newLine)->setAsNumX1(cl.getX1());
			dynamic_cast<Line*>(newLine)->setAsNumX2(cl.getX2());
			dynamic_cast<Line*>(newLine)->setAsNumY1(cl.getY1());
			dynamic_cast<Line*>(newLine)->setAsNumY2(cl.getY2());
			dynamic_cast<Line*>(newLine)->setAsNumStrokeWidth(cl.getStrokeWidth());
			dynamic_cast<Line*>(newLine)->setStroke(cl.getStroke());
		}
		// if there is no number for stroke-width
		else
		{
			// sets the numbers to x1, y1, x2, y2, stroke
			cl.caseNoStrokeWidth(toAppendToFile);

			// checks whether the above function ended well
			if (toAppendToFile == "")
			{
				std::cout << "Bad input!" << std::endl;
				// free the memory that we just took
				delete newLine;
				return;
			}

			// transfer the information from cl to newLine
			dynamic_cast<Line*>(newLine)->setAsNumX1(cl.getX1());
			dynamic_cast<Line*>(newLine)->setAsNumX2(cl.getX2());
			dynamic_cast<Line*>(newLine)->setAsNumY1(cl.getY1());
			dynamic_cast<Line*>(newLine)->setAsNumY2(cl.getY2());
			dynamic_cast<Line*>(newLine)->setStroke(cl.getStroke());
		}

		// add the line for the file corresponding to the new figure
		inputFromFile.push_back(toAppendToFile);

		// add the new figure
		figures.push_back(newLine);

		// message to let the user know that the figure has been successfully created
		std::cout << "Successfully created line (" << figures.size() << ")" << std::endl;
	}
}

// erase function - deletes a figure
void ConsoleInterface::erase(const int numToErase)
{
	// if the number of the figure we need to delete is out of bounds stop the function
	if (numToErase > figures.size() || numToErase < 0)
	{
		std::cout << "There is no figure number " << numToErase << "!"<< std::endl;
		return;
	}

	std::cout << "Erased a " << figures[numToErase - 1]->getType() << " (" << numToErase << ")" << std::endl;

	// the figures are shown on the console from 1 to figure.size() so we need to remove 1 in order to 
	// remove the correct member
	figures.erase(figures.begin() + numToErase - 1);

	// we remove a figure so we should remove it's corresponding line in the file
	inputFromFile.erase(inputFromFile.begin() + numToErase - 1);
}

// translates a figure
void ConsoleInterface::translate(const std::string input)
{
	// regular expressions to find horizontal = ... and input = ... in the input
	std::regex horizontalFinder("horizontal(\\s)*=(\\s)*(\")?(\\s)*(-)?[\\d\.]+(\\s)*(\")?");
	std::regex verticalFinder("vertical(\\s)*=(\\s)*(\")?(\\s)*(-)?[\\d\.]+(\\s)*(\")?");

	// we get horizontal = ... or "" if no match was found
	std::string horizontal = getMatch(input, horizontalFinder);

	// we get vertical = ... or "" if no match was found
	std::string vertical = getMatch(input, verticalFinder);

	// if both don't exist then it is a bad input since we have nothing to translate with
	if (horizontal == "" && vertical == "")
	{
		std::cout << "There are no numbers with which to translate! Check the input." << std::endl;
		return;
	}

	// prevents cases like vertical = 1eg5 from bugging the program
	// note: the string found by the regular expression (vertical) will be vertical = 1 in this case 
	// and the normal string we get from the function getVerticalFromInput() is vertical = 1eg5
	if (!compareTwoStrings(vertical, getVerticalFromInput(input)))
	{
		std::cout << "The number for vertical is incorrect! Try again..." << std::endl;
		return;
	}

	// same as above - only now we check for horizontal
	if (!compareTwoStrings(horizontal, getHorizontalFromInput(input)))
	{
		std::cout << "The number for horizontal is incorrect! Try again..." << std::endl;
		return;
	}

	// checks the corectness of horizontal = ...
	if (!checkTranslateInput(horizontal) && horizontal != "")
	{
		std::cout << "There is something wrong in the input! Try again..." << std::endl;
		return;
	}

	// checks the corectness of vertical = ...
	if (!checkTranslateInput(vertical) && vertical != "")
	{
		std::cout << "There is something wrong in the input! Try again..." << std::endl;
		return;
	}

	// regular expression that finds numbers (negative ones and of type double)
	std::regex numFinder("[\\d\.-]+");

	// stores the numbers from the input
	std::vector<std::string> numbers;

	// extracts the numbers from the input and puts them inside the vector
	getNumbersToVector(numbers, input, numFinder);

	for (int i = 0; i < numbers.size(); i++)
	{
		// check if any number starts with 0 which we consider bad input
		if (numbers[i].size() > 1 && numbers[i][0] == '0')
		{
			std::cout << "Some of the numbers start with 0! Try again..." << std::endl;
			return;
		}
	}
	
	// represents the object we will translate (if it is 0 we translate all figures)
	int objectToTranslate = 0;

	// if the numbers in the vector numbers are 3 then the first one is the number of the figure we should
	// translate
	if (numbers.size() == 3)
	{
		objectToTranslate = std::stoi(numbers[0]);
	}
	// if the numbers are 2 and either horizontal or vertical is the empty string then the first number again
	// is the number of the figure we shoudl translate
	else if (numbers.size() == 2 && (horizontal == "" || vertical == ""))
	{
		objectToTranslate = std::stoi(numbers[0]);
	}

	// checks whether we have been given a number out of bounds so that there is no such figure
	if (objectToTranslate < 0 || objectToTranslate > figures.size())
	{
		std::cout << "Object to translate out of bounds! Check the input." << std::endl;
		return;
	}

	// holds the number that we will use to move horizontally (horizontal = ...)
	double horizontalNum = getNumberFromString(horizontal);

	// holds the number that we will use to move vertically (vertical = ...)
	double verticalNum = getNumberFromString(vertical);

	// in the case when we should translate all figures and horizontalNum is negative, 
	// check whether the absolute value of horizontalNum is bigger than the x (cx, x1, x2) value 
	// of the figures and therefore the latter will become negative as well after the addition
	if (horizontalNum < 0 && !objectToTranslate)
	{
		// go through all the figures
		for (int i = 0; i < figures.size(); i++)
		{
			if (figures[i]->getType() == "rectangle")
			{
				if (dynamic_cast<Rect*>(figures[i])->getX() < std::abs(horizontalNum))
				{
					std::cout << "Cannot translate with such low horizontal value!" << std::endl;
					return;
				}
			}
			else if (figures[i]->getType() == "circle")
			{
				if (dynamic_cast<Circle*>(figures[i])->getCX() < std::abs(horizontalNum))
				{
					std::cout << "Cannot translate with such low horizontal value!" << std::endl;
					return; 
				}
			}
			else
			{
				if (dynamic_cast<Line*>(figures[i])->getX1() < std::abs(horizontalNum) || dynamic_cast<Line*>(figures[i])->getX2() < std::abs(horizontalNum))
				{
					std::cout << "Cannot translate with such low horizontal value!" << std::endl;
					return;
				}
			}
		}
	}
	// in the case when we have to translate a figure and again horizontalNum is negative, check for the 
	// same thing but only for the figure
	else if (objectToTranslate && horizontalNum < 0)
	{
		if (figures[objectToTranslate - 1]->getType() == "rectangle")
		{
			if (dynamic_cast<Rect*>(figures[objectToTranslate - 1])->getX() < std::abs(horizontalNum))
			{
				std::cout << "Cannot translate with such low horizontal value!" << std::endl;
				return;
			}
		}
		else if (figures[objectToTranslate - 1]->getType() == "circle")
		{
			if (dynamic_cast<Circle*>(figures[objectToTranslate - 1])->getCX() < std::abs(horizontalNum))
			{
				std::cout << "Cannot translate with such low horizontal value!" << std::endl;
				return;
			}
		}
		else
		{
			if (dynamic_cast<Line*>(figures[objectToTranslate - 1])->getX1() < std::abs(horizontalNum) || dynamic_cast<Line*>(figures[objectToTranslate - 1])->getX2() < std::abs(horizontalNum))
			{
				std::cout << "Cannot translate with such low horizontal value!" << std::endl;
				return;
			}
		}
	}

	// same principles as in the above if statement only now we do it for verticalNum
	// note: we check for the y parameter because we are moving vertically after all
	if (verticalNum < 0 && !objectToTranslate)
	{
		for (int i = 0; i < figures.size(); i++)
		{
			if (figures[i]->getType() == "rectangle")
			{
				if (dynamic_cast<Rect*>(figures[i])->getY() < std::abs(verticalNum))
				{
					std::cout << "Cannot translate with such low vertical value!" << std::endl;
					return;
				}
			}
			else if (figures[i]->getType() == "circle")
			{
				if (dynamic_cast<Circle*>(figures[i])->getCY() < std::abs(verticalNum))
				{
					std::cout << "Cannot translate with such low vertical value!" << std::endl;
					return;
				}
			}
			else
			{
				if (dynamic_cast<Line*>(figures[i])->getY1() < std::abs(verticalNum) || dynamic_cast<Line*>(figures[i])->getY2() < std::abs(verticalNum))
				{
					std::cout << "Cannot translate with such low vertical value!" << std::endl;
					return;
				}
			}
		}
	}
	else if (objectToTranslate && verticalNum < 0)
	{
		if (figures[objectToTranslate - 1]->getType() == "rectangle")
		{
			if (dynamic_cast<Rect*>(figures[objectToTranslate - 1])->getY() < std::abs(verticalNum))
			{
				std::cout << "Cannot translate with such low vertical value!" << std::endl;
				return;
			}
		}
		else if (figures[objectToTranslate - 1]->getType() == "circle")
		{
			if (dynamic_cast<Circle*>(figures[objectToTranslate - 1])->getCY() < std::abs(verticalNum))
			{
				std::cout << "Cannot translate with such low vertical value!" << std::endl;
				return;
			}
		}
		else
		{
			if (dynamic_cast<Line*>(figures[objectToTranslate - 1])->getY1() < std::abs(verticalNum) || dynamic_cast<Line*>(figures[objectToTranslate - 1])->getY2() < std::abs(verticalNum))
			{
				std::cout << "Cannot translate with such low vertical value!" << std::endl;
				return;
			}
		}
	}

	// in the case when we should translate only one figure
	if (objectToTranslate)
	{
		// translates the figure by calling the pure virtual function translate
		figures[objectToTranslate - 1]->translate(horizontalNum, verticalNum);
		// message to the console that the translation was successfull
		std::cout << "Translated object number " << objectToTranslate << std::endl;
		// use the function makeLineForFile in order to update the file with the change we just made
		inputFromFile[objectToTranslate - 1] = makeLineForFile(figures[objectToTranslate - 1]);
	}
	// in the case when we should translate all figures
	else
	{
		// perform the same thing as in the above case only now we do it for every figure
		for (int i = 0; i < figures.size(); i++)
		{
			figures[i]->translate(horizontalNum, verticalNum);
			inputFromFile[i] = makeLineForFile(figures[i]);
		}
		std::cout << "Translated all figures" << std::endl;
	}
}

void ConsoleInterface::within(const std::string input)
{
	// finds the position of the words circle and rectangle in input
	int findCircle = input.find("circle");
	int findRectangle = input.find("rectangle");

	// check whether input is correct or not
	if (!checkWithinInput(input))
	{
		std::cout << "There is something wrong in the input! Try again..." << std::endl;
		return;
	}

	// counts the number of figures inside
	// we use this counter in order to determine whether or not there were any figures inside the figure 
	// from the input
	int counterFigures= 0;
	
	// if the figure from the input is a rectangle
	if (findRectangle != std::string::npos)
	{
		// regular expression to find numbers in a string
		std::regex numFinder("[\\d]+");

		// we store the coordinates of the figure here
		std::vector<std::string> nums;

		// assings the numbers from the input to the vector nums
		getNumbersToVector(nums, input, numFinder);

		// we need x, y, width and height in order to compare correctly
		if (nums.size() < 4)
		{
			std::cout << "Too little information to calculate within operation! Try again..." << std::endl;
			return;
		}
		// any additional information is considered as bad input
		else if (nums.size() > 4)
		{
			std::cout << "Too much information! Try again..." << std::endl;
			return;
		}

		// create the rect from the input
		Rect newRect;

		newRect.setAsNumX(std::stoi(nums[0]));
		newRect.setAsNumY(std::stoi(nums[1]));
		newRect.setAsNumWidth(std::stoi(nums[2]));
		newRect.setAsNumHeight(std::stoi(nums[3]));

		// this will be the number in front of each figure that is inside the rectangle:
		// 1. ...
		// 2. ...
		// 3. ...
		// etc.
		int counter = 1;

		// go through the figures and check if each one is inside
		for (int i = 0; i < figures.size(); i++)
		{
			if (figures[i]->getType() == "rectangle")
			{
				// get the parameters of the current figure into variables
				double figureX = dynamic_cast<Rect*>(figures[i])->getX();
				double figureY = dynamic_cast<Rect*>(figures[i])->getY();
				double figureWidth = dynamic_cast<Rect*>(figures[i])->getWidth();
				double figureHeight = dynamic_cast<Rect*>(figures[i])->getHeight();

				// if the upper left corner of the current rectangle is on the upper left corner of the 
				// rectangle we are checking with or it is on any point on the left and upper side, or it is inside
				// the rectangle
				if (figureX >= newRect.getX() && figureY >= newRect.getY())
				{
					// figureX - newRect.getX() will get the distance between the two points (judging from the x-axis) and after adding it to
					// the width of the current figure we will get the furthest point of the rectangle compared to
					// newRect
					// the same is for figureY - newRect.getY() + figureHeight
					// if the furthest point is 
					if (figureX - newRect.getX() + figureWidth <= newRect.getWidth() && figureY - newRect.getY() + figureHeight <= newRect.getHeight())
					{
						// the number in front each figure that is inside
						std::cout << counter++ << ". ";
						figures[i]->print();
						// one (more) figure is inside
						counterFigures++;
					}
				}
			}
			else if (figures[i]->getType() == "circle")
			{
				// store the parameters of the circle inside variables
				double figureCX = dynamic_cast<Circle*>(figures[i])->getCX();
				double figureCY = dynamic_cast<Circle*>(figures[i])->getCY();
				double figureR = dynamic_cast<Circle*>(figures[i])->getR();

				// check whether the furthest points of the circle (x-wise and y-wise) are inside the rectangle (check both ways)
				if (figureCX + figureR <= newRect.getX() + newRect.getWidth() && figureCY + figureR <= newRect.getY() + newRect.getHeight()
					&& figureCX - figureR >= newRect.getX() && figureCY - figureR >= newRect.getY())
				{
					std::cout << counter++ << ". ";
					figures[i]->print();
					counterFigures++;
				}
			}
			else
			{
				// store the parameters of the line inside variables
				double figureX1 = dynamic_cast<Line*>(figures[i])->getX1();
				double figureX2 = dynamic_cast<Line*>(figures[i])->getX2();
				double figureY1 = dynamic_cast<Line*>(figures[i])->getY1();
				double figureY2 = dynamic_cast<Line*>(figures[i])->getY2();

				// check whether x1, x2, y1 and y2 are inside the rectangle
				if (figureX1 >= newRect.getX() && figureY1 >= newRect.getY() && figureX2 <= newRect.getX() + newRect.getWidth() &&
					figureY2 <= newRect.getY() + newRect.getHeight())
				{
					std::cout << counter++ << ". ";
					figures[i]->print();
					counterFigures++;
				}
			}
		}
	}
	// if the figure from the input is circle
	else if (findCircle != std::string::npos)
	{
		// regular expression used to find numbers in a string
		std::regex numFinder("[\\d]+");

		// holds the numbers from the input
		std::vector<std::string> nums;

		// puts the numbers from the input into nums
		getNumbersToVector(nums, input, numFinder);

		// we need numbers for cx, cy and r, any number less than 3 is considered a bad input
		if (nums.size() < 3)
		{
			std::cout << "Not enough numbers to create a circle with which to compare! Try again..." << std::endl;
			return;
		}

		// same goes for any number bigger than 3
		if (nums.size() > 3)
		{
			std::cout << "Too much information! Try again..." << std::endl;
			return;
		}

		// this will be the number in front of each figure that is inside the rectangle:
		// 1. ...
		// 2. ...
		// 3. ...
		// etc.
		int counter = 1;

		// create the circle from the input
		Circle newCircle;
		newCircle.setAsNumCX(std::stoi(nums[0]));
		newCircle.setAsNumCY(std::stoi(nums[1]));
		newCircle.setAsNumR(std::stoi(nums[2]));

		// go through all figures we have at the moment
		for (int i = 0; i < figures.size(); i++)
		{
			if (figures[i]->getType() == "rectangle")
			{
				// store the parameters of the current figure in variables
				double figureX = dynamic_cast<Rect*>(figures[i])->getX();
				double figureY = dynamic_cast<Rect*>(figures[i])->getY();
				double figureWidth = dynamic_cast<Rect*>(figures[i])->getWidth();
				double figureHeight = dynamic_cast<Rect*>(figures[i])->getHeight();

				// the following booleans store the information about each edge of the rectangle
				// the first determines whether the upper left edge is inside the circle using vector calculations
				// the second determines whether the upper right edge is inside the circle using vector calculations
				// the third and the forth perform the same things for the lower left and right edges
				// note on how we calculate the distance: using vectors we can easily calculate the distance.
				// To compute the distance we need to add the subtraction of the x and y coordinates of the circle and rectangle
				// each raised to the power of 2 and then square root the product
				// keep in mind that the x coordinate of the upper right edge is: figureX + figureWidth because figureX
				// starts at the upper left edge so we need to add the width value so that we go to the other edge
				// the same goes for the x coordinate of the lower right edge
				// it is the same for the y coordinate of some of the edges as well (only now we add figureHeight)
				bool isUpperLeftCornerInside = (std::sqrt(std::pow(newCircle.getCX() - figureX, 2) + std::pow(newCircle.getCY() - figureY, 2)) <= newCircle.getR());
				bool isUpperRightCornerInside = (std::sqrt(std::pow(newCircle.getCX() - figureX - figureWidth, 2) + std::pow(newCircle.getCY() - figureY, 2)) <= newCircle.getR());
				bool isLowerLeftCornerInside = (std::sqrt(std::pow(newCircle.getCX() - figureX, 2) + std::pow(newCircle.getCY() - figureY - figureHeight, 2)) <= newCircle.getR());
				bool isLowerRightCornerInside = (std::sqrt(std::pow(newCircle.getCX() - figureX - figureWidth, 2) + std::pow(newCircle.getCY() - figureY - figureHeight, 2)) <= newCircle.getR());

				// when all of the edges are inside
				if (isUpperLeftCornerInside && isUpperRightCornerInside && isLowerLeftCornerInside && isLowerRightCornerInside)
				{
					std::cout << counter++ << ". ";
					figures[i]->print();
					counterFigures++;
				}
			}
			else if (figures[i]->getType() == "circle")
			{
				// we shall name this circle: circle 2
				// we store the parameters of circle 2 in variables
				double figureCX = dynamic_cast<Circle*>(figures[i])->getCX();
				double figureCY = dynamic_cast<Circle*>(figures[i])->getCY();
				double figureR = dynamic_cast<Circle*>(figures[i])->getR();

				// compute the distance between the two radiuses first
				double distanceBetweenRadiuses = std::sqrt(std::pow(figureCX - newCircle.getCX(), 2) + std::pow(figureCY - newCircle.getCY(), 2));

				// then if the sum of the radius of circle 2 and the distance between the two radiuses is smaller than the 
				// radius of the initial circle, circle 2 is inside the initial one
				if (distanceBetweenRadiuses + figureR <= newCircle.getR())
				{
					std::cout << counter++ << ". ";
					figures[i]->print();
					counterFigures++;
				}
			}
			else
			{
				// we store the coordinates of the figure in variables
				double figureX1 = dynamic_cast<Line*>(figures[i])->getX1();
				double figureX2 = dynamic_cast<Line*>(figures[i])->getX2();
				double figureY1 = dynamic_cast<Line*>(figures[i])->getY1();
				double figureY2 = dynamic_cast<Line*>(figures[i])->getY2();

				// check whether the starting and ending points of the line are inside the circle
				// note: the calculations are the same as in the case when the figure was a rectangle
				bool isPoint1Inside = (std::sqrt(std::pow(figureX1 - newCircle.getCX(), 2) + std::pow(figureY1 - newCircle.getCY(), 2)) <= newCircle.getR());
				bool isPoint2Inside = (std::sqrt(std::pow(figureX2 - newCircle.getCX(), 2) + std::pow(figureY2 - newCircle.getCY(), 2)) <= newCircle.getR());

				// if both points are inside the circle
				if (isPoint1Inside && isPoint2Inside)
				{
					std::cout << counter++ << ". ";
					figures[i]->print();
					counterFigures++;
				}
			}
		}
	}
	// if the figure wasn't rectangle or circle, or if no figure was mentioned
	else
	{
		std::cout << "No figure to check with" << std::endl;
		return;
	}

	// if cno figure was inside the figure from the input
	if (!counterFigures)
	{
		std::cout << "No figures are located " << input << std::endl;
	}
}

// opens a file with the name fileName
const bool ConsoleInterface::open(const std::string fileName)
{
	// uses the function openFile() to extract the information from the file and then
	// transfer it to the two member vectors here
	Reader::getInstance()->openFile(fileName);	
	getInputFromFile();
	getFigures();

	// let the caller know that the file was empty
	if (inputFromFile.size() == 0)
	{
		return false;
	}
	return true;
}

// closes the currently opened file
void ConsoleInterface::close()
{
	Reader::getInstance()->closeFile();
	// delete the instance since we don't need it anymore (we just closed the current file) and to make it
	// possible to open another file (creating the instance again)
	Reader::getInstance()->releaseInstance();
	// release this instance in order to refresh everything in case the user wants to open another file
	releaseInstance();
}

// saves the changes to the currently opened file
void ConsoleInterface::save()
{
	Reader::getInstance()->save(inputFromFile);
}

// saves the changes to another file (old or new)
void ConsoleInterface::saveAs(const std::string fileName)
{
	Reader::getInstance()->saveAs(fileName, inputFromFile);
}
