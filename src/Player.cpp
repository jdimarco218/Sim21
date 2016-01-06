#include <iostream>
#include <memory>
#include "Bet.h"
#include "Game.h"
#include "Player.h"
#include "Strategy.h"

Player::Player()
{
    _activeVec = std::vector<bool>();
    _activeVec.push_back(true);
    _doubleVec = std::vector<bool>();
    _doubleVec.push_back(false);
    _chips = 0;
    _wantsInsurance = false;
    _strategy = std::unique_ptr<Strategy>(new Strategy());
    ResetPlayer();
}

void Player::SetWantsInsurance(bool wantsInsurance)
{
    _wantsInsurance = wantsInsurance;
}

void Player::ResetPlayer()
{
    _activeVec.clear();
    _activeVec.push_back(true);
    _doubleVec.clear();
    _doubleVec.push_back(false);
    _handsBetVec.clear();
    _hands.clear();
    _totalWagered = 0.0;
    _totalWinnings = 0.0;

    // Create an empty initial hand
    //
    _hands.push_back(std::vector<std::unique_ptr<Card> >());

    // TODO FIXME
    //_wantsInsurance = true;
}

void Player::SetInitialBet(Game * game)
{
    int betAmount = game->GetMinimumBet() * _strategy->GetNumUnits(game->GetHiloTrueCount());
    _handsBetVec.push_back(std::unique_ptr<Bet>(new Bet(betAmount, (double)betAmount)));
    _chips -= betAmount;  
}

void Player::MakeAdditionalBet(int handIdx, int betAmount)
{
    if (handIdx < _handsBetVec.size()) // Adding bet (e.g. doubling)
    {
        _handsBetVec[handIdx]->_amount += betAmount;
        _totalWagered += betAmount;
        _chips -= betAmount;
    }
    else if (handIdx == _handsBetVec.size()) // New hand's bet (e.g. split)
    { 
        _handsBetVec.push_back(std::unique_ptr<Bet>(new Bet(betAmount)));
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

double Player::GetHandBetAmount(int handIdx)
{
    return _handsBetVec[handIdx]->GetAmount();
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

map<string, vector<pair<TPlayAction, TPlayAction> > > Player::GetMap()
{
    return bs_s17_das_ls;
}

// Basic strategy for Stand-17, DAS LS
map<string, vector<pair<TPlayAction, TPlayAction> > > Player::bs_s17_das_ls = 
{ 
    {"2", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 1, dealer ace
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 2
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 3
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 4
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 5
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 6
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 7
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 8
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 9
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // T
        }
    }, 
    {"3", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 1, dealer ace
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 2
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 3
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 4
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 5
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 6
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 7
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 8
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 9
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // T
        }
    }, 
    {"4", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 1, dealer ace
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 2
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 3
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 4
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 5
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 6
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 7
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 8
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 9
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // T
        }
    }, 
    {"5", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 1, dealer ace
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 2
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 3
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 4
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 5
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 6
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 7
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 8
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 9
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // T
        }
    }, 
    {"6", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 1, dealer ace
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 2
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 3
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 4
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 5
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 6
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 7
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 8
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 9
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // T
        }
    }, 
    {"7", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 1, dealer ace
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 2
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 3
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 4
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 5
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 6
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 7
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 8
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 9
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // T
        }
    }, 
    {"8", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 1, dealer ace
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 2
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 3
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 4
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 5
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 6
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 7
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 8
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 9
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // T
        }
    }, 
    {"9", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 1, dealer ace
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 2
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 3
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 4
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 5
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 6
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 7
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 8
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 9
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // T
        }
    }, 
    {"10", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 1, dealer ace
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 2
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 3
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 4
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 5
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 6
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 7
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 8
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 9
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // T
        }
    }, 
    {"11", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 1, dealer ace
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 2
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 3
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 4
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 5
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 6
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 7
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 8
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 9
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // T
        }
    }, 
    {"12", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 1, dealer ace
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 2
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 3
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 4
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 5
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 6
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 7
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 8
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 9
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // T
        }
    }, 
    {"13", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 1, dealer ace
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 2
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 3
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 4
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 5
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 6
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 7
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 8
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 9
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // T
        }
    }, 
    {"14", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 1, dealer ace
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 2
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 3
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 4
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 5
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 6
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 7
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 8
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 9
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // T
        }
    }, 
    {"15", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 1, dealer ace
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 2
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 3
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 4
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 5
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 6
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 7
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 8
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 9
            make_pair(TPlayAction::SURRENDER, TPlayAction::HIT), // T
        }
    }, 
    {"16", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::SURRENDER, TPlayAction::HIT), // 1, dealer ace
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 2
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 3
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 4
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 5
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 6
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 7
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 8
            make_pair(TPlayAction::SURRENDER, TPlayAction::HIT), // 9
            make_pair(TPlayAction::SURRENDER, TPlayAction::HIT), // T
        }
    }, 
    {"17", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 1, dealer ace
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 2
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 3
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 4
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 5
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 6
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 7
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 8
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 9
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // T
        }
    }, 
    {"18", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 1, dealer ace
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 2
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 3
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 4
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 5
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 6
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 7
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 8
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 9
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // T
        }
    }, 
    {"19", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 1, dealer ace
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 2
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 3
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 4
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 5
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 6
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 7
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 8
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 9
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // T
        }
    }, 
    {"20", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 1, dealer ace
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 2
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 3
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 4
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 5
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 6
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 7
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 8
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 9
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // T
        }
    }, 
    {"s13", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 1, dealer ace
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 2
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 3
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 4
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 5
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 6
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 7
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 8
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 9
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // T
        }
    }, 
    {"s14", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 1, dealer ace
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 2
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 3
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 4
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 5
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 6
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 7
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 8
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 9
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // T
        }
    }, 
    {"s15", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 1, dealer ace
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 2
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 3
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 4
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 5
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 6
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 7
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 8
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 9
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // T
        }
    }, 
    {"s16", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 1, dealer ace
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 2
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 3
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 4
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 5
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 6
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 7
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 8
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 9
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // T
        }
    }, 
    {"s17", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 1, dealer ace
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 2
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 3
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 4
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 5
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 6
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 7
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 8
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 9
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // T
        }
    }, 
    {"s18", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 1, dealer ace
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 2
            make_pair(TPlayAction::DOUBLE, TPlayAction::STAND), // 3
            make_pair(TPlayAction::DOUBLE, TPlayAction::STAND), // 4
            make_pair(TPlayAction::DOUBLE, TPlayAction::STAND), // 5
            make_pair(TPlayAction::DOUBLE, TPlayAction::STAND), // 6
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 7
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 8
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 9
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // T
        }
    }, 
    {"s19", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 1, dealer ace
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 2
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 3
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 4
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 5
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 6
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 7
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 8
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 9
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // T
        }
    }, 
    {"s20", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 1, dealer ace
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 2
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 3
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 4
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 5
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 6
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 7
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 8
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 9
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // T
        }
    }, 
    {"p1", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::SPLIT, TPlayAction::HIT), // 1, dealer ace
            make_pair(TPlayAction::SPLIT, TPlayAction::HIT), // 2
            make_pair(TPlayAction::SPLIT, TPlayAction::HIT), // 3
            make_pair(TPlayAction::SPLIT, TPlayAction::STAND), // 4
            make_pair(TPlayAction::SPLIT, TPlayAction::STAND), // 5
            make_pair(TPlayAction::SPLIT, TPlayAction::STAND), // 6
            make_pair(TPlayAction::SPLIT, TPlayAction::HIT), // 7
            make_pair(TPlayAction::SPLIT, TPlayAction::HIT), // 8
            make_pair(TPlayAction::SPLIT, TPlayAction::HIT), // 9
            make_pair(TPlayAction::SPLIT, TPlayAction::HIT), // T
        }
    }, 
    {"p2", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 1, dealer ace
            make_pair(TPlayAction::SPLIT, TPlayAction::HIT), // 2
            make_pair(TPlayAction::SPLIT, TPlayAction::HIT), // 3
            make_pair(TPlayAction::SPLIT, TPlayAction::HIT), // 4
            make_pair(TPlayAction::SPLIT, TPlayAction::HIT), // 5
            make_pair(TPlayAction::SPLIT, TPlayAction::HIT), // 6
            make_pair(TPlayAction::SPLIT, TPlayAction::HIT), // 7
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 8
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 9
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // T
        }
    }, 
    {"p3", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 1, dealer ace
            make_pair(TPlayAction::SPLIT, TPlayAction::HIT), // 2
            make_pair(TPlayAction::SPLIT, TPlayAction::HIT), // 3
            make_pair(TPlayAction::SPLIT, TPlayAction::HIT), // 4
            make_pair(TPlayAction::SPLIT, TPlayAction::HIT), // 5
            make_pair(TPlayAction::SPLIT, TPlayAction::HIT), // 6
            make_pair(TPlayAction::SPLIT, TPlayAction::HIT), // 7
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 8
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 9
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // T
        }
    }, 
    {"p4", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 1, dealer ace
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 2
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 3
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 4
            make_pair(TPlayAction::SPLIT, TPlayAction::HIT), // 5
            make_pair(TPlayAction::SPLIT, TPlayAction::HIT), // 6
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 7
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 8
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 9
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // T
        }
    }, 
    {"p5", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 1, dealer ace
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 2
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 3
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 4
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 5
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 6
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 7
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 8
            make_pair(TPlayAction::DOUBLE, TPlayAction::HIT), // 9
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // T
        }
    }, 
    {"p6", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 1, dealer ace
            make_pair(TPlayAction::SPLIT, TPlayAction::HIT), // 2
            make_pair(TPlayAction::SPLIT, TPlayAction::HIT), // 3
            make_pair(TPlayAction::SPLIT, TPlayAction::STAND), // 4
            make_pair(TPlayAction::SPLIT, TPlayAction::STAND), // 5
            make_pair(TPlayAction::SPLIT, TPlayAction::STAND), // 6
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 7
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 8
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 9
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // T
        }
    }, 
    {"p7", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 1, dealer ace
            make_pair(TPlayAction::SPLIT, TPlayAction::STAND), // 2
            make_pair(TPlayAction::SPLIT, TPlayAction::STAND), // 3
            make_pair(TPlayAction::SPLIT, TPlayAction::STAND), // 4
            make_pair(TPlayAction::SPLIT, TPlayAction::STAND), // 5
            make_pair(TPlayAction::SPLIT, TPlayAction::STAND), // 6
            make_pair(TPlayAction::SPLIT, TPlayAction::HIT), // 7
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 8
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 9
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // T
        }
    }, 
    {"p8", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::SPLIT, TPlayAction::SURRENDER), // 1, dealer ace
            make_pair(TPlayAction::SPLIT, TPlayAction::STAND), // 2
            make_pair(TPlayAction::SPLIT, TPlayAction::STAND), // 3
            make_pair(TPlayAction::SPLIT, TPlayAction::STAND), // 4
            make_pair(TPlayAction::SPLIT, TPlayAction::STAND), // 5
            make_pair(TPlayAction::SPLIT, TPlayAction::STAND), // 6
            make_pair(TPlayAction::SPLIT, TPlayAction::HIT), // 7
            make_pair(TPlayAction::SPLIT, TPlayAction::HIT), // 8
            make_pair(TPlayAction::SPLIT, TPlayAction::SURRENDER), // 9
            make_pair(TPlayAction::SPLIT, TPlayAction::SURRENDER), // T
        }
    }, 
    {"p9", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 1, dealer ace
            make_pair(TPlayAction::SPLIT, TPlayAction::STAND), // 2
            make_pair(TPlayAction::SPLIT, TPlayAction::STAND), // 3
            make_pair(TPlayAction::SPLIT, TPlayAction::STAND), // 4
            make_pair(TPlayAction::SPLIT, TPlayAction::STAND), // 5
            make_pair(TPlayAction::SPLIT, TPlayAction::STAND), // 6
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 7
            make_pair(TPlayAction::SPLIT, TPlayAction::STAND), // 8
            make_pair(TPlayAction::SPLIT, TPlayAction::STAND), // 9
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // T
        }
    }, 
    {"p10", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 1, dealer ace
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 2
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 3
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 4
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 5
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 6
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 7
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 8
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // 9
            make_pair(TPlayAction::STAND, TPlayAction::STAND), // T
        }
    }
};
