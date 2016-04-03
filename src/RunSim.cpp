#include <chrono>
#include <iostream>
#include <list>
#include <memory>
#include "Sim.h"
#include "SimUtil.h"
#include "Card.h"
#include "Deck.h"
#include "Shoe.h"

#define DEBUG true

using namespace std::chrono;

int main(int argc, char ** argv)
{
    std::cout << "Starting sim." << std::endl;

    auto start = std::chrono::steady_clock::now();

    //
    // Use custom cfg file if provided, else default to Sim.cfg
    //
    std::map<std::string, std::string> cfgMap;
    cfgMap = LoadConfig("cfg/Sim.cfg");

    //
    // DECK_TYPE
    //
    TDeckType deckType = TDeckType::BLACKJACK;
    if (cfgMap.find("DECK_TYPE") != cfgMap.end())
    {
        auto& cfgDeckType = cfgMap.find("DECK_TYPE")->second;
        if (cfgDeckType == "BLACKJACK")
        {
            deckType = TDeckType::BLACKJACK;
        }
        else if (cfgDeckType == "SPANISH21")
        {
            deckType = TDeckType::SPANISH21;
        }
        else
        {
            std::cerr << "Unknown DECK_TYPE (" << cfgDeckType << ") when reading cfg." << std::endl;
            deckType = TDeckType::BLACKJACK;
        }
    }
    if (DEBUG)
    {
        if (cfgMap.find("DECK_TYPE") != cfgMap.end())
        {
            std::cout << "DECK_TYPE: " << cfgMap.find("DECK_TYPE")->second << std::endl;
        }
    }

    //
    // SIM_MODE
    //
    TSimMode simMode = TSimMode::STRATEGY;
    if (cfgMap.find("SIM_MODE") != cfgMap.end())
    {
        auto& cfgSimMode = cfgMap.find("SIM_MODE")->second;
        if (cfgSimMode == "STRATEGY")
        {
            simMode = TSimMode::STRATEGY;
        }
        else if (cfgSimMode == "EOR")
        {
            simMode = TSimMode::EOR;
        }
        else if (cfgSimMode == "INDEX")
        {
            simMode = TSimMode::INDEX;
        }
        else
        {
            std::cerr << "Unknown SIM_MODE (" << cfgSimMode << ") when reading cfg. Exiting." << std::endl;
            exit(-1);
        }
    }
    if (DEBUG)
    {
        if (cfgMap.find("SIM_MODE") != cfgMap.end())
        {
            std::cout << "SIM_MODE: " << cfgMap.find("SIM_MODE")->second << std::endl;
        }
    }

    //
    // HANDS_TO_PLAY
    //
    int handsToPlay = 0;
    std::vector<std::string> players;

    if (cfgMap.find("HANDS_TO_PLAY") != cfgMap.end())
    {
        handsToPlay = std::stoi(cfgMap.find("HANDS_TO_PLAY")->second);
    }
    if (DEBUG)
    {
        if (cfgMap.find("HANDS_TO_PLAY") != cfgMap.end())
        {
            std::cout << "HANDS_TO_PLAY: " << cfgMap.find("HANDS_TO_PLAY")->second << std::endl;
        }
    }

    //
    // PLAYERS
    //
    if (cfgMap.find("PLAYERS") != cfgMap.end())
    {
        std::string playerStr = cfgMap.find("PLAYERS")->second;
        for (auto& player : split_string(playerStr, ' '))
        {
            players.push_back(player);
        }
    }
    else
    {
        players.push_back("DEFAULT_PLAYER");
    }
    if (DEBUG)
    {
        if (cfgMap.find("PLAYERS") != cfgMap.end())
        {
            for (auto& player : split_string(cfgMap.find("PLAYERS")->second, ' '))
            {
                std::cout << "Player: " << player << std::endl;
            }
        }
    }

    //
    // HIT_17
    //
    bool hit17 = false;
    if (cfgMap.find("HIT_17") != cfgMap.end())
    {
        auto& cfgHit17 = cfgMap.find("HIT_17")->second;
        if (cfgHit17 == "FALSE" ||
            cfgHit17 == "NO"   ||
            cfgHit17 == "False" ||
            cfgHit17 == "No"   ||
            cfgHit17 == "false" ||
            cfgHit17 == "no")
        {
            hit17 = false;
        }
        else if (cfgHit17 == "TRUE" ||
                 cfgHit17 == "YES"  ||
                 cfgHit17 == "True" ||
                 cfgHit17 == "Yes"  ||
                 cfgHit17 == "true" ||
                 cfgHit17 == "yes")
        {
            hit17 = true;
        }
        else
        {
            std::cerr << "Unknown HIT_17 (" << cfgHit17 << ") when reading cfg. Exiting." << std::endl;
            exit(-1);
        }
    }
    if (DEBUG)
    {
        if (cfgMap.find("HIT_17") != cfgMap.end())
        {
            std::cout << "HIT_17: " << cfgMap.find("HIT_17")->second << std::endl;
        }
    }

    //
    // Run the simulation!
    //
    std::unique_ptr<Sim> sim(new Sim(simMode, deckType, handsToPlay, players, hit17));
    //sim->GetPlayerAt(1)->SetCounting(false);
    //sim->GetPlayerAt(1)->SetDeviating(false);
    sim->RunSimulation();

    auto end = std::chrono::steady_clock::now();
    auto timeSpan = std::chrono::duration_cast<duration<double> >(end - start);

    std::cout << "Done. Elapsed time: "
              << timeSpan.count()
              << " seconds."
              << std::endl;

    return 0;
}

