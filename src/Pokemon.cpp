#include "Pokemon.h"
#include "Move.h"
#include <iostream>
#include <algorithm>

Pokemon::Pokemon(const std::string& name, int hp, int atk, int def, int spd)
    : name(name), maxHP(hp), currentHP(hp), attack(atk), defense(def), speed(spd) {
}

void Pokemon::takeDamage(int damage) {
    currentHP = std::max(0, currentHP - damage);
}

void Pokemon::heal(int amount) {
    currentHP = std::min(maxHP, currentHP + amount);
}

void Pokemon::addMove(std::shared_ptr<Move> move) {
    moves.push_back(move);
}

void Pokemon::displayStatus() const {
    std::cout << name << " - HP: " << currentHP << "/" << maxHP << std::endl;
    std::cout << "Stats - ATK: " << attack << ", DEF: " << defense << ", SPD: " << speed << std::endl;
    std::cout << "Moves: ";
    for (size_t i = 0; i < moves.size(); ++i) {
        std::cout << moves[i]->getName();
        if (i < moves.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;
}
