#include <iostream>
#include "Player.hpp"

int main(){
	Player p1("TR34-1111-2222");
	Player p2("TR78-2222-3333");

	p1.setBal(1000);
	p2.addBal(500);
	p2.decBal(20);

	std::cout << "Player1's balance: " << p1.getBal() << std::endl;
	std::cout << "Player2's balance: " << p2.getBal() << std::endl;
	
	Player pCombined = p1 + p2;
	pCombined.printBal();

	return 0;
}
