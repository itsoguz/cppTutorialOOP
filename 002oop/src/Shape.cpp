#include "Shape.hpp"

//Shape::Shape() = default;	// defined in Shape.hpp
//Shape::~Shape() = default;
//const double Shape::area() const = 0; // area() is pure virtual, therefore no need to implement it.

Circle::Circle(double r) : Shape(), radius(r) {}
const double Circle::area() const {
	return static_cast<const double> (3.1415 * radius * radius);
}

Rectangle::Rectangle(double l, double w) : Shape(), length(l), width (w){}
const double Rectangle::area() const {
	return static_cast<const double> (length * width);
}
