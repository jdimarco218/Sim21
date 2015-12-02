#include <iostream>
#include <memory>
#include "Game.h"
#include "Player.h"

Player::Player()
{
    _active = false;
    _chips = 0;
    ResetPlayer();
}

void Player::ResetPlayer()
{
    _active = true;
    std::cout << "Resetting player..." << std::endl;
    _handsBetVec.clear();
    _hands.clear();

    // Create an empty initial hand
    //
    _hands.push_back(std::vector<std::unique_ptr<Card> >());
    //std::cout << "While resetting, made _hands.size(): " << _hands.size() << std::endl;
}

void Player::SetInitialBet(Game * game)
{
    int betAmount = 25;
    _handsBetVec.push_back(Bet(betAmount, (double)betAmount));
    _chips -= betAmount;  
}

void Player::MakeAdditionalBet(int handIdx, int betAmount)
{
    if (handIdx == _handsBetVec.size()) // Adding bet (e.g. doubling)
    {
    }
    else if (handIdx < _handsBetVec.size()) // New hand's bet (e.g. split)
    { 
        _handsBetVec[handIdx]._amount += betAmount;
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
    // Set insurance to be half of the 0th hand's bet
    _insuranceBet = std::unique_ptr<Bet>(new Bet(_handsBetVec[0]._amount / 2));
    return;
}
