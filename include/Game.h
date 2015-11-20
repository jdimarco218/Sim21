#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Player.h"
#include "Shoe.h"

class Game
{
public:
    Game();

private:
    std::vector<Player> _playerList;
    Shoe _shoe;
    

};

#endif
