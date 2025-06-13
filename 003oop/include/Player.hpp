// Player.hpp

#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <string>

class Player{
	private:
		long balance;
		std::string accNum;	// account number
	public:
		Player() = delete;
		~Player() = default;
		Player(const std::string& accNum_);

		void addBal(const long amount_);
		void decBal(const long amount_);	// decrease balance
		void setBal(const long bal_);
		const long getBal() const;

		void printBal() const;
		Player operator+(const Player& other) const;
};

#endif
