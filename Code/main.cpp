#include "ConsoleInterface.h"

// counts the number of words and numbers in a line
const int countNumberOfWords(const std::string input)
{
	// find any character except for whitespaces
	std::regex reg(".[^ ]+");

	std::sregex_iterator currentMatch(input.begin(), input.end(), reg);
	std::sregex_iterator lastMatch;

	int counter = 0;

	// while there is a match
	while (currentMatch != lastMatch)
	{
		counter++;
		currentMatch++;
	}

	return counter;
}

// gets the last word in a line
// we use this function to get the name of the file we should open
const std::string getLastWord(std::string command)
{
	// if the command was only the word open then we don't have to get anything since this command has to have 2
	// words
	if (command == "open")
	{
		return "";
	}

	std::string fileName = "";

	// if the command's last character is a whitespace start erasing it's last character until it finds a character
	if (command[command.size() - 1] == ' ')
	{
		command.erase(command.begin() + command.size() - 1);
		for (int i = command.size() - 1; command[i] == ' '; i--)
		{
			command.erase(command.begin() + command.size() - 1);
		}
	}

	// start extracting the name of the file until it finds a whitespace
	for (int i = command.size() - 1; command[i] != ' '; i--)
	{
		fileName.push_back(command[i]);
	}

	// if it finds nothing instead
	if (fileName == "")
	{
		return fileName;
	}

	// since we are going from the end to the beginning of the string we should turn around the string so that we
	// get the real file name
	for (int i = 0; i < fileName.size() / 2; i++)
	{
		char temp = fileName[i];
		fileName[i] = fileName[fileName.size() - i - 1];
		fileName[fileName.size() - i - 1] = temp;
	}

	return fileName;
}

int main()
{
	// is the command open used correctly (is a file opened)
	bool isOpened = false;

	// this is where we will store the commands of the user
	std::string command;

	// while the user doesn't want to exit the program
	while (command != "exit")
	{
		std::cout << "> ";
		std::getline(std::cin, command);

		// these determine which command was used or not used
		int findOpen = command.find("open");
		int findClose = command.find("close");
		int findSave = command.find("save");
		int findSaveAs = command.find("saveas");
		int findExit = command.find("exit");
		int findPrint = command.find("print");
		int findCreate = command.find("create");
		int findErase = command.find("erase");
		int findTranslate = command.find("translate");
		int findWithin = command.find("within");

		// if the command open was used
		if (findOpen != std::string::npos && !isOpened)
		{
			// if the input contained two numbers/words at total
			if (countNumberOfWords(command) == 2)
			{
				// if the file exists
				if (ConsoleInterface::getInstance()->open(getLastWord(command)))
				{
					isOpened = true;
				}
			}
		}

		// the next commands can be used only when the user has opened a file
		if (isOpened)
		{
			// if the command close was used
			if (findClose != std::string::npos)
			{
				// we don't need any other words except for close
				if (countNumberOfWords(command) == 1)
				{
					ConsoleInterface::getInstance()->close();

					// the user needs to open another file if he wishes to use these commands again
					isOpened = false;
				}
				else
				{
					std::cout << "Too many words used for a one-word command!" << std::endl;
				}
			}
			// if the command save was used and not saveas (since findSave will find saveas as well and since
			// we check for this first this case will be used rather than saveas case which is a problem)
			// that's why we check if saveas was typed in
			else if (findSave != std::string::npos && findSaveAs == std::string::npos)
			{
				// we don't need any other words for this command
				if (countNumberOfWords(command) == 1)
				{
					ConsoleInterface::getInstance()->save();
				}
				else
				{
					std::cout << "Too many words used for a one-word command!" << std::endl;
				}
			}
			// if the command saveas was used
			else if (findSaveAs != std::string::npos)
			{
				// we don't need other words apart from saveas and the file name
				if (countNumberOfWords(command) == 2)
				{
					ConsoleInterface::getInstance()->saveAs(getLastWord(command));
				}
				else
				{
					std::cout << "Too many words used for a two-word command!" << std::endl;
				}
			}
			// if the command exit was used
			else if (findExit != std::string::npos)
			{
				// we don't need any other words for this command
				if (countNumberOfWords(command) == 1)
				{
					break;
				}
				else
				{
					std::cout << "Too many words used for a one-word command!" << std::endl;
				}
			}
			// if the command print was used
			else if (findPrint != std::string::npos)
			{
				// we don't need any other words for this command
				if (countNumberOfWords(command) == 1)
				{
					ConsoleInterface::getInstance()->print();
				}
				else
				{
					std::cout << "Too many words used for a one-word command!" << std::endl;
				}
			}
			// if the command create was used
			else if (findCreate != std::string::npos)
			{
				// all the checks are inside that function so we don't need to check anything here
				ConsoleInterface::getInstance()->create(command);
			}
			// if the command erase was used
			else if (findErase != std::string::npos)
			{
				// we don't need other words/numbers apart from erase and the number of the figure that should be deleted
				if (countNumberOfWords(command) == 2)
				{
					ConsoleInterface::getInstance()->erase(std::stoi(getLastWord(command)));
				}
				else
				{
					std::cout << "Too many words used for a two-word command!" << std::endl;
				}
			}
			// if the command translate was used
			else if (findTranslate != std::string::npos)
			{
				// all the checks are inside that function
				ConsoleInterface::getInstance()->translate(command);
			}
			// if the command within was used
			else if (findWithin != std::string::npos)
			{
				// all the checks are inside that function
				ConsoleInterface::getInstance()->within(command);
			}
		}

		std::cout << std::endl;
	}

	// when the user exists the program we release the instance - the rest is held by the function itself
	ConsoleInterface::releaseInstance();
	std::cout << "Exiting the program..." << std::endl;
	std::cin.get();
	return 0;
}