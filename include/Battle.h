#ifndef BATTLE_H
#define BATTLE_H

#include "Pokemon.h"
#include <memory>

class Battle {
private:
    std::shared_ptr<Pokemon> pokemon1;
    std::shared_ptr<Pokemon> pokemon2;
    
    void executeTurn(Pokemon& attacker, Pokemon& defender, int moveIndex);
    Pokemon& determineFirstAttacker();

public:
    Battle(std::shared_ptr<Pokemon> p1, std::shared_ptr<Pokemon> p2);
    
    // Start the battle and return the winner
    std::shared_ptr<Pokemon> start();
    
    // Display battle state
    void displayBattleState() const;
};

#endif // BATTLE_H
