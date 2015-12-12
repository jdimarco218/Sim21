#include <iostream>
#include <memory>
#include "Bet.h"
#include "Game.h"
#include "Player.h"

Player::Player()
{
    _active = false;
    _chips = 0;
    _wantsInsurance = false;
    ResetPlayer();
}

void Player::SetWantsInsurance(bool wantsInsurance)
{
    _wantsInsurance = wantsInsurance;
}

void Player::ResetPlayer()
{
    _active = true;
    _handsBetVec.clear();
    _hands.clear();

    // Create an empty initial hand
    //
    _hands.push_back(std::vector<std::unique_ptr<Card> >());

    // TODO FIXME
    //_wantsInsurance = true;
}

void Player::SetInitialBet(Game * game)
{
    int betAmount = game->GetMinimumBet();
    _handsBetVec.push_back(std::unique_ptr<Bet>(new Bet(betAmount, (double)betAmount)));
    _chips -= betAmount;  
}

void Player::MakeAdditionalBet(int handIdx, int betAmount)
{
    if (handIdx == _handsBetVec.size()) // Adding bet (e.g. doubling)
    {
    }
    else if (handIdx < _handsBetVec.size()) // New hand's bet (e.g. split)
    { 
        _handsBetVec[handIdx]->_amount += betAmount;
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
    _insuranceBet = std::unique_ptr<Bet>(new Bet(_handsBetVec[0]->_amount / 2.0));
    _chips -= _insuranceBet->_amount;
    _totalWagered += _insuranceBet->_amount;
    return;
}

bool Player::WantsInsurance(Game * game)
{
    // TODO: more intelligent
    return _wantsInsurance;
}
