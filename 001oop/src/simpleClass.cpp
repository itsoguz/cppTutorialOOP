#include <iostream>
#include <string>

class Person{
	public:
	std::string name;
	int age;

	Person(const std::string& n, int age_) : name(n), age(age_) {		
		std::cout << "Constructor called for the object refering to ";
		printName();
	}

	~Person(){
		std::cout << "Destructor called for the object refering to ";
		printName();
	}
	
	void printName(){
		std::cout << name << std::endl;
	}
};

int main(){
	Person person1("John Hop", 30);
	Person person2(person1);
	person2.name = "Alice Doe";

	return 0;
}
