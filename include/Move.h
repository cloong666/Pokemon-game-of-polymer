#ifndef MOVE_H
#define MOVE_H

#include <string>
#include <functional>

class Pokemon;

class Move {
private:
    std::string name;
    std::string scriptPath;
    int basePower;
    int accuracy;
    std::string type;
    
    // Function to execute Python skill script
    std::function<int(Pokemon&, Pokemon&)> effectFunction;

public:
    Move(const std::string& name, const std::string& scriptPath, 
         int power, int accuracy, const std::string& type);
    
    // Getters
    std::string getName() const { return name; }
    int getBasePower() const { return basePower; }
    int getAccuracy() const { return accuracy; }
    std::string getType() const { return type; }
    std::string getScriptPath() const { return scriptPath; }
    
    // Execute the move
    int execute(Pokemon& attacker, Pokemon& defender);
    
    // Set custom effect function (loaded from Python)
    void setEffectFunction(std::function<int(Pokemon&, Pokemon&)> func);
};

#endif // MOVE_H
