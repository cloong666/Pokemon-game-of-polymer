#ifndef POKEMON_H
#define POKEMON_H

#include <string>
#include <vector>
#include <memory>

class Move;

class Pokemon {
private:
    std::string name;
    int maxHP;
    int currentHP;
    int attack;
    int defense;
    int speed;
    std::vector<std::shared_ptr<Move>> moves;

public:
    Pokemon(const std::string& name, int hp, int atk, int def, int spd);
    
    // Getters
    std::string getName() const { return name; }
    int getMaxHP() const { return maxHP; }
    int getCurrentHP() const { return currentHP; }
    int getAttack() const { return attack; }
    int getDefense() const { return defense; }
    int getSpeed() const { return speed; }
    const std::vector<std::shared_ptr<Move>>& getMoves() const { return moves; }
    
    // Battle methods
    void takeDamage(int damage);
    void heal(int amount);
    bool isFainted() const { return currentHP <= 0; }
    void addMove(std::shared_ptr<Move> move);
    
    // Display
    void displayStatus() const;
};

#endif // POKEMON_H
