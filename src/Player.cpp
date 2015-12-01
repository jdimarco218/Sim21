#include <iostream>
#include <memory>
#include "Game.h"
#include "Player.h"

Player::Player()
{
    _chips = 0;
    ResetPlayer();
}

void Player::ResetPlayer()
{
    std::cout << "Resetting player..." << std::endl;
    _betVec.clear();
    _hands.clear();

    // Create an empty initial hand
    //
    _hands.push_back(std::vector<std::unique_ptr<Card> >());
    //std::cout << "While resetting, made _hands.size(): " << _hands.size() << std::endl;
}

void Player::SetInitialBet(Game * game)
{
    int betAmount = 25;
    _betVec.push_back(Bet(betAmount, (double)betAmount));
    _chips -= betAmount;  
}

void Player::MakeAdditionalBet(int handIdx, int betAmount)
{
    if (handIdx == _betVec.size()) // Adding bet (e.g. doubling)
    {
    }
    else if (handIdx < _betVec.size()) // New hand's bet (e.g. split)
    { 
        _betVec[handIdx] += betAmount;
        _totalWagered += betAmount;
        _chips -= betAmount;
    }
    else // Shouldn't happen
    {
        std::cerr << "ERROR: unknown hand for adding a new bet!" << std::endl; 
        return;
    }
    return;
}

void Player::MakeInsuranceBet()
{

    return;
}
