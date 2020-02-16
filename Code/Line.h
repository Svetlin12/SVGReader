#pragma once
#include "Shape.h"

class Line : public Shape
{
private:

	// a variable for x1
	double x1Num;

	// a variable for x2
	double x2Num;

	// a variable for y1
	double y1Num;

	// a variable for y2
	double y2Num;

	// a variable for stroke-width
	double strokeWidthNum;

	// a variable for stroke
	std::string stroke;

	// the functions down below all set their corresponding member from an entire line from a file
	void setX1(const std::string line);
	void setX2(const std::string line);
	void setY1(const std::string line);
	void setY2(const std::string line);
	void setStrokeWidth(const std::string line);
	void setStrokeFromEntireLine(const std::string line);

public:

	// default constructor
	Line();

	// getter for each member
	const double getX1() const;
	const double getX2() const;
	const double getY1() const;
	const double getY2() const;
	const double getStrokeWidth() const;
	const std::string getStroke() const;

	// a normal setter for each member
	void setAsNumX1(const double x1);
	void setAsNumX2(const double x2);
	void setAsNumY1(const double y1);
	void setAsNumY2(const double y2);
	void setAsNumStrokeWidth(const double strokeWidth);
	void setStroke(const std::string stroke);

	// this returns "line"
	const std::string getType() const override;

	// a print function which prints the data for the line to the console
	void print() const override;

	// translates the line
	void translate(const double horizontal, const double vertical) override;

	// virtual destructor
	virtual ~Line();

	// sets all members using the set functions in the private section
	void setAllMembers(const std::string str) override;
};