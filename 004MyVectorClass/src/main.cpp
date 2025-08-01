#include <iostream>
#include "MyVector.hpp"

int main() {
	MyVector<int> v1 = { 100, 200 };
	v1.push_back(300);
	v1.push_back(400);

	for (const auto& c: v1) {	// pass by const reference
		std::cout << c << " ";
	}
	
	std::cout << std::endl;
	return 0;
}

