// Player.cpp

#include "Player.hpp"
#include <iostream>	// for std::cout

//Player::Player() = delete;	// defined in Player.hpp
//Player::~Player() = default;	// defined in Player.hpp

Player::Player(const std::string& accNum_) : balance(0), accNum(accNum_) {}
void Player::addBal(const long amount_) {
	balance += amount_;
}

void Player::decBal(const long amount_) {
	balance -= amount_;
}

void Player::setBal(const long bal_) {
	balance = bal_;
}

const long Player::getBal() const {
	return static_cast<const long>(balance);
}

void Player::printBal() const {
	std::cout << "Account: " << accNum << std::endl
		<< "Balance: " << balance << std::endl;
}

Player Player::operator+(const Player& other) const {
	Player newPlayer(accNum + " + " + other.accNum);
	newPlayer.balance = balance + other.balance;
	return newPlayer;
}
