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
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 3
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 4
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 5
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 6
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
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 2
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 3
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 4
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 5
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 6
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 7
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 8
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 9
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // T
        }
    }, 
    {"11", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 1, dealer ace
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 2
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 3
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 4
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 5
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 6
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 7
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 8
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 9
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // T
        }
    }, 
    {"12", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 1, dealer ace
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 2
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 3
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 4
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 5
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 6
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
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 2
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 3
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 4
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 5
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 6
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
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 2
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 3
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 4
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 5
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 6
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
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 2
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 3
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 4
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 5
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 6
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 7
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 8
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 9
            make_pair(TPlayAction::HIT, TPlayAction::SURRENDER), // T
        }
    }, 
    {"16", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::SURRENDER), // 1, dealer ace
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 2
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 3
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 4
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 5
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 6
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 7
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 8
            make_pair(TPlayAction::HIT, TPlayAction::SURRENDER), // 9
            make_pair(TPlayAction::HIT, TPlayAction::SURRENDER), // T
        }
    }, 
    {"17", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 1, dealer ace
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 2
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 3
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 4
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 5
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 6
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 7
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 8
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 9
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // T
        }
    }, 
    {"18", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 1, dealer ace
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 2
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 3
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 4
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 5
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 6
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 7
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 8
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 9
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // T
        }
    }, 
    {"19", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 1, dealer ace
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 2
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 3
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 4
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 5
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 6
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 7
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 8
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 9
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // T
        }
    }, 
    {"20", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 1, dealer ace
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 2
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 3
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 4
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 5
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 6
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 7
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 8
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 9
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // T
        }
    }, 
    {"s13", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 1, dealer ace
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 2
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 3
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 4
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 5
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 6
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
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 5
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 6
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
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 4
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 5
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 6
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
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 4
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 5
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 6
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
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 3
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 4
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 5
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 6
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
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 2
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 3
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 4
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 5
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 6
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 7
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 8
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 9
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // T
        }
    }, 
    {"s19", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 1, dealer ace
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 2
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 3
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 4
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 5
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 6
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 7
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 8
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 9
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // T
        }
    }, 
    {"s20", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 1, dealer ace
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 2
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 3
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 4
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 5
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 6
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 7
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 8
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 9
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // T
        }
    }, 
    {"p1", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 1, dealer ace
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 2
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 3
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 4
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 5
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 6
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 7
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 8
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 9
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // T
        }
    }, 
    {"p2", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 1, dealer ace
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 2
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 3
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 4
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 5
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 6
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 7
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 8
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 9
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // T
        }
    }, 
    {"p3", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 1, dealer ace
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 2
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 3
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 4
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 5
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 6
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 7
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
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 5
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 6
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
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 2
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 3
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 4
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 5
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 6
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 7
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 8
            make_pair(TPlayAction::HIT, TPlayAction::DOUBLE), // 9
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // T
        }
    }, 
    {"p6", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 1, dealer ace
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 2
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 3
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 4
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 5
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 6
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
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 2
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 3
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 4
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 5
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 6
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 7
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 8
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // 9
            make_pair(TPlayAction::HIT, TPlayAction::HIT), // T
        }
    }, 
    {"p8", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 1, dealer ace
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 2
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 3
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 4
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 5
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 6
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 7
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 8
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 9
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // T
        }
    }, 
    {"p9", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 1, dealer ace
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 2
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 3
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 4
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 5
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 6
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 7
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 8
            make_pair(TPlayAction::HIT, TPlayAction::SPLIT), // 9
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // T
        }
    }, 
    {"p10", vector<pair<TPlayAction, TPlayAction> >
        {
            make_pair(TPlayAction::NONE, TPlayAction::NONE), // 0, non-situation
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 1, dealer ace
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 2
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 3
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 4
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 5
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 6
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 7
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 8
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // 9
            make_pair(TPlayAction::HIT, TPlayAction::STAND), // T
        }
    }
};
