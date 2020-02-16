#pragma once
#include "Shape.h"

class Circle : public Shape
{
private:

	// variable for cx
	double cxNum;

	// variable for cy
	double cyNum;

	// variable for r
	double rNum;

	// variable for stroke-width
	double strokeWidthNum;

	// varaible for fill
	std::string fill;

	// variable for stroke
	std::string stroke;

	// the functions below set their corresponding member using a line from a file
	void setCX(const std::string line);
	void setCY(const std::string line);
	void setR(const std::string line);
	void setStrokeWidthNum(const std::string line);
	void setFillFromEntireLine(const std::string line);
	void setStrokeFromEntireLine(const std::string line);

public:

	// default constructor
	Circle();
	
	// getter for each member
	const double getCX() const;
	const double getCY() const;
	const double getR() const;
	const double getStrokeWidth() const;
	const std::string getFill() const;
	const std::string getStroke() const;

	// a normal setter for each member
	void setAsNumCX(const double cx);
	void setAsNumCY(const double cy);
	void setAsNumR(const double r);
	void setAsNumStrokeWidth(const double strokeWidth);
	void setFill(const std::string fill);
	void setStroke(const std::string stroke);

	// returns "circle"
	const std::string getType() const override;

	// print function
	void print() const override;

	// translates the circle
	void translate(const double horizontal, const double vertical) override;

	// virtual destructor
	virtual ~Circle();

	// sets all members using the functions in the private section
	void setAllMembers(const std::string str) override;
};