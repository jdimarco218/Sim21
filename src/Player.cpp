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
}

void Player::SetInitialBet(Game game)
{
    int betAmount = 25;
    _betVec.push_back(Bet(betAmount, (double)betAmount));
    _chips -= betAmount;  
}
