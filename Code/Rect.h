#pragma once
#include "Shape.h"

class Rect : public Shape
{
private:

	// stores the x value
	double xNum;

	// stores the y value
	double yNum;

	// stores the height value
	double heightNum;

	// stores the width value
	double widthNum;

	// stores the stroke-width value
	double strokeWidth;

	// stores the fill string
	std::string fill;

	// stores the stroke string
	std::string stroke;

	// the functions down bellow are all used in the virtual function setAll() and they basically set their
	// corresponding members the values from a line from the file
	void setX(const std::string line);
	void setY(const std::string line);
	void setHeight(const std::string line);
	void setWidth(const std::string line);
	void setStrokeWidth(const std::string line);
	void setFillFromEntireLine(const std::string line);
	void setStrokeFromEntireLine(const std::string line);

public:

	// default constructor
	Rect();

	// setters that sets the members through a (const) double variable
	void setAsNumX(const double x);
	void setAsNumY(const double y);
	void setAsNumHeight(const double height);
	void setAsNumWidth(const double width);
	void setAsNumStrokeWidth(const double strokeWidth);
	void setFill(const std::string fill);
	void setStroke(const std::string stroke);

	// getters for each member
	const double getX() const;
	const double getY() const;
	const double getHeight() const;
	const double getWidth() const;
	const double getStrokeWidth() const;
	const std::string getFill() const;
	const std::string getStroke() const;
	
	// returns "rectangle"
	const std::string getType() const override;

	// prints the data for the rectangle
	void print() const override;

	// translates the current figure
	void translate(const double horizontal, const double vertical) override;

	// virtual destructor
	virtual ~Rect();

	void setAllMembers(const std::string str) override;
};