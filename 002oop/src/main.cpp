#include <iostream>
#include "Shape.hpp"

int main(){
	Circle circle(5.0);
	Rectangle rectangle(4.0, 6.0);

	std::cout << "Area of circle: " << circle.area() << std::endl; 
	std::cout << "Area of rectangle: " << rectangle.area() << std::endl;

	return 0;
}
