#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

// I implemented Singleton because there is no point of this class having multiple instances - we open the file once,
// read from it once, write to it once and close it once
class Reader
{
private:

	static Reader* instance;

	std::fstream myFile;

	// stores the data for the figures
	std::vector<std::string> matchesStore;

	// stores all the rest data
	std::vector<std::string> fileContent;

	// stores the name of the currently opened file
	std::string fileName;

	// the explanation of the functions below is inside Parser.cpp where their definitions are

	bool matches(std::string str, std::regex reg) const;

	Reader();
	~Reader();
	Reader(const Reader& p);
	Reader& operator= (const Reader& p);

	const bool checkStringBegEnd(const std::string str);
	void extractMatchesFromContent(std::vector<std::string>& content);

public:

	void writeToFile(const std::string fileName);
	void readFromFile();

	const bool openFile(const std::string fileName);
	const bool closeFile();
	void save(const std::vector<std::string> changedMatches);
	void saveAs(const std::string fileName, const std::vector<std::string> changedMatches);

	const std::vector<std::string> getMatches() const;
	void setMatches(std::vector<std::string> changedMatches);

	static Reader* getInstance();
	static void releaseInstance();
};