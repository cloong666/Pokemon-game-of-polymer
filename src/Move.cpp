#include "Move.h"
#include "Pokemon.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Move::Move(const std::string& name, const std::string& scriptPath, 
           int power, int accuracy, const std::string& type)
    : name(name), scriptPath(scriptPath), basePower(power), accuracy(accuracy), type(type) {
    // Default effect function (basic damage calculation)
    effectFunction = [this](Pokemon& attacker, Pokemon& defender) -> int {
        // Simple damage formula: (Attack * Power / Defense) / 2
        int damage = (attacker.getAttack() * basePower) / (defender.getDefense() * 2);
        damage = std::max(1, damage); // Minimum 1 damage
        return damage;
    };
}

int Move::execute(Pokemon& attacker, Pokemon& defender) {
    // Check accuracy
    int roll = rand() % 100;
    if (roll >= accuracy) {
        std::cout << attacker.getName() << "'s " << name << " missed!" << std::endl;
        return 0;
    }
    
    // Execute the effect function
    int damage = effectFunction(attacker, defender);
    defender.takeDamage(damage);
    
    std::cout << attacker.getName() << " used " << name << "!" << std::endl;
    std::cout << "It dealt " << damage << " damage!" << std::endl;
    
    return damage;
}

void Move::setEffectFunction(std::function<int(Pokemon&, Pokemon&)> func) {
    effectFunction = func;
}
