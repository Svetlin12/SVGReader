#include "Reader.h"

Reader* Reader::instance = nullptr;

// function that returns true if there has been found a match between the string and the regular expression
// and false when that was not the case
bool Reader::matches(std::string str, std::regex reg) const
{
	std::sregex_iterator currentMatch(str.begin(), str.end(), reg);
	std::sregex_iterator lastMatch;

	return currentMatch != lastMatch;
}

// The next four functions (default constructor, destructor, copy constructor and copy operator) have definitions
// only because otherwise the compiler would have created them 'behind the scenes', rendering our singleton
// pattern incomplete
Reader::Reader()
{
}

Reader::~Reader()
{
}

Reader::Reader(const Reader & p)
{
}

Reader & Reader::operator=(const Reader & p)
{
	return *this;
}

// this function is used whenever we need to determine if a line from file has completed a statement in svg
// (that is for instance <rect x="20" y="20" width="20" height="20" fill="yellow" />), because the file might 
// contain lines that do not have statements such as the above one, but rather they have a separated statement
// (i.e. line 1: <rect x="20" y="20"
//       line 2: width="20" height="20" fill="yellow" /> ; note: there might be empty lines inbetween which does
// not matter in our case as we are about to see)
const bool Reader::checkStringBegEnd(const std::string str)
{
	int find1 = str.find("<");
	int find2 = str.find(">");

	if (find1 == std::string::npos || find2 == std::string::npos)
	{
		return false;
	}

	return true;
}

// function to get the information inside <svg> ... </svg> which is the figures
void Reader::extractMatchesFromContent(std::vector<std::string>& content)
{
	// content is basically all the information that the file contains stored line by line inside a vector
	// I intend to change it so that's why I am using &

	// these are the regular expressions used for the search of the lines of type <rect ... />, <circle ... />
	// and <line ... />. The order of the different coordinates is one because I consider the rest as 'bad' input
	// but nevertheless it can be made so that it covers all permutations of the positions of the different coordinates
	std::regex rectCheck("<rect(\\s)*(x(\\s)*=(\\s)*\"(\\s)*[\\d]+(\\s)*\")?(\\s)*(y(\\s)*=(\\s)*\"(\\s)*[\\d]+(\\s)*\")?(\\s)*width(\\s)*=(\\s)*\"(\\s)*[\\d]+(\\s)*\"(\\s)*height(\\s)*=(\\s)*\"(\\s)*[\\d]+(\\s)*\"(\\s)*.*");
	std::regex circleCheck("<circle(\\s)*(cx(\\s)*=(\\s)*\"(\\s)*[\\d]+(\\s)*\")?(\\s)*(cy(\\s)*=(\\s)*\"(\\s)*[\\d]+(\\s)*\")?(\\s)*(r(\\s)*=(\\s)*\"(\\s)*[\\d]+(\\s)*\")?.*");
	std::regex lineCheck("<line(\\s)*(x1(\\s)*=(\\s)*\"(\\s)*[\\d]+(\\s)*\")?(\\s)*(y1(\\s)*=(\\s)*\"(\\s)*[\\d]+(\\s)*\")?(\\s)*(x2(\\s)*=(\\s)*\"(\\s)*[\\d]+(\\s)*\")?(\\s)*(y2(\\s)*=(\\s)*\"(\\s)*[\\d]+(\\s)*\")?.*");

	for (int i = 0; i < content.size(); i++)
	{
		// if the line is matched with the regular expression for rect then put it in matchesStore and erase
		// the information because it will be useful when we write to the end file
		if (matches(content[i], rectCheck))
		{
			matchesStore.push_back(content[i]);
			content[i] = "";
		}
		// if the line is matched with the regular expression for circle then put it in matchesStore and erase
		// the information
		else if (matches(content[i], circleCheck))
		{
			matchesStore.push_back(content[i]);
			content[i] = "";
		}
		// if the line is mathced with the regular expression for line then put it in matchesStore and erase
		// the information
		else if (matches(content[i], lineCheck))
		{
			matchesStore.push_back(content[i]);
			content[i] = "";
		}
	}
}

// pretty simple function: all it does is to open a file and print to the console a message so that we know if we
// have successfully opened a file or not
const bool Reader::openFile(const std::string fileName)
{
	myFile.open(fileName);
	if (myFile.is_open())
	{
		// variable that stores the initial name because the user might save his changes 
		// inside the same file later instead of saving them in another one
		this->fileName = fileName;
		std::cout << "Successfully opened " << fileName << std::endl;
		// extracts the information for the figures in that file
		readFromFile();
		return true;
	}
	else
	{
		std::cout << "Could not find file under the name " << fileName << std::endl;
		return false;
	}
	// closes the file
	myFile.close();
}

// function to write all the information the user changed or did not inside a given file
void Reader::writeToFile(const std::string fileName)
{
	std::ofstream write;
	// we erase the previous information because we have all the previous data and the new one inside vectors
	write.open(fileName, std::ios::trunc);
	if (write.is_open())
	{
		for (int i = 0; i < fileContent.size(); i++)
		{
			// determine when we get to the point when we are supposed to switch to the other vector
			// which stores the information for the figures
			int findSVG = fileContent[i].find("<svg");

			if (findSVG == std::string::npos)
			{

				// ???
				if (fileContent[i] == "")
				{
					continue;
				}

				// keep on writing the previous data
				write << fileContent[i] << std::endl;
			}
			else
			{
				// write the line <svg...
				write << fileContent[i] << std::endl;
				for (int j = 0; j < matchesStore.size(); j++)
				{
					// writes the data for the figures
					write << matchesStore[j] << std::endl;
				}
			}
		}
	}

	write.close();
}

// function that reads information from file and stores it inside a vector
void Reader::readFromFile()
{
	if (myFile.is_open())
	{
		// temporary holder of the current line from the file
		std::string tmp;

		// string used when there is a figure which information is on separate lines (check the example in the
		// explanation for the funtion checkStringBegEnd
		std::string storeStrings = "";

		// this will be the variable to signal when to start checking the figures because we don't need to
		// check the other data (we won't use it, neither does the user need it)
		bool startCheckingStrings = false;

		while (std::getline(myFile, tmp))
		{
			int findSVG = tmp.find("<svg");

			// if we get to the line <svg...
			if (findSVG != std::string::npos)
			{
				fileContent.push_back(tmp);

				// initiate the checking
				startCheckingStrings = true;
				continue;
			}
			else if (!startCheckingStrings)
			{
				fileContent.push_back(tmp);
			}

			if (startCheckingStrings)
			{
				// concatinate the strings until storeStrings is of the type < .... />
				storeStrings += tmp;
				if (checkStringBegEnd(storeStrings))
				{
					fileContent.push_back(storeStrings);

					// reset the string
					storeStrings = "";
				}
			}
		}
		extractMatchesFromContent(fileContent);
	}
}

// function to close the current file
const bool Reader::closeFile()
{
	myFile.close();
	if (!myFile.is_open())
	{
		std::cout << "Successfully closed " << fileName << std::endl;
	}
	return myFile.is_open();
}

void Reader::save(const std::vector<std::string> changedMatches)
{
	if (myFile.is_open())
	{
		// replace the previous data with the new one and then write it to the currently opened file
		setMatches(changedMatches);
		writeToFile(fileName);
		std::cout << "Successfully saved " << fileName << std::endl;
	}
	else
	{
		std::cout << "Could not save " << fileName << ". It was closed beforehand." << std::endl;
	}
}

void Reader::saveAs(const std::string fileName, const std::vector<std::string> changedMatches)
{
	if (myFile.is_open())
	{
		// change the previous data to the new one and then write it to a new file
		setMatches(changedMatches);
		writeToFile(fileName);
		std::cout << "Successfully saved " << fileName << std::endl;
	}
	else
	{
		std::cout << "Could not save " << fileName << ". It was closed beforehand." << std::endl;
	}
}

// gives access to the lines containing the information of the figures which we will use in other classes
const std::vector<std::string> Reader::getMatches() const
{
	return this->matchesStore;
}

// replace the old data with the new one
void Reader::setMatches(std::vector<std::string> changedMatches)
{
	// clear the old data
	matchesStore.clear();
	for (int i = 0; i < changedMatches.size(); i++)
	{
		// add the new one
		matchesStore.push_back(changedMatches[i]);
	}
}

// singleton implementation in the functions below
Reader * Reader::getInstance()
{
	if (nullptr == instance)
	{
		instance = new Reader();
	}
	return instance;
}

void Reader::releaseInstance()
{
	if (nullptr != instance)
	{
		delete instance;
		instance = nullptr;
	}
}
