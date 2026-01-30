#ifndef PYTHON_SKILL_LOADER_H
#define PYTHON_SKILL_LOADER_H

#include <string>
#include <functional>
#include <Python.h>

class Pokemon;

class PythonSkillLoader {
private:
    static bool pythonInitialized;
    
public:
    // Initialize Python interpreter
    static void initialize();
    
    // Finalize Python interpreter
    static void finalize();
    
    // Load a skill function from a Python script
    static std::function<int(Pokemon&, Pokemon&)> loadSkill(const std::string& scriptPath, const std::string& functionName);
    
    // Execute Python skill directly
    static int executeSkill(const std::string& scriptPath, const std::string& functionName,
                           Pokemon& attacker, Pokemon& defender);
};

#endif // PYTHON_SKILL_LOADER_H
