#include <iostream>
#include "Game.h"
#include "Player.h"

Player::Player()
{
    _chips = 0;
}

void Player::ResetPlayer()
{
    std::cout << "Resetting player..." << std::endl;
    _betVec.clear();
    _hands.clear();

    // Create an empty initial hand
    //
    _hands.push_back(std::vector<Card>());
    std::cout << "While resetting, made _hands.size(): " << _hands.size() << std::endl;
}

void Player::SetInitialBet(Game game)
{
    int betAmount = 25;
    _betVec.push_back(Bet(betAmount, (double)betAmount));
    _chips -= betAmount;  
}
