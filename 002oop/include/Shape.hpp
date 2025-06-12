#ifndef SHAPE_HPP
#define SHAPE_HPP

class Shape{
	public:
		Shape() = default;
		virtual ~Shape() = default;
		virtual const double area() const = 0;
};

class Circle : public Shape{
	public:
		double radius;

		Circle(double r);
		const double area() const override;
};

class Rectangle : public Shape{
	public:
		double length;
		double width;

		Rectangle(double l, double w);
		const double area() const override;
};

#endif
