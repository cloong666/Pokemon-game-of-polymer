#include "PythonSkillLoader.h"
#include "Pokemon.h"
#include <iostream>
#include <stdexcept>

bool PythonSkillLoader::pythonInitialized = false;

void PythonSkillLoader::initialize() {
    if (!pythonInitialized) {
        Py_Initialize();
        
        // Add current directory to Python path
        PyRun_SimpleString("import sys");
        PyRun_SimpleString("sys.path.append('.')");
        PyRun_SimpleString("sys.path.append('./scripts')");
        
        pythonInitialized = true;
        std::cout << "Python interpreter initialized." << std::endl;
    }
}

void PythonSkillLoader::finalize() {
    if (pythonInitialized) {
        Py_Finalize();
        pythonInitialized = false;
    }
}

int PythonSkillLoader::executeSkill(const std::string& scriptPath, const std::string& functionName,
                                    Pokemon& attacker, Pokemon& defender) {
    if (!pythonInitialized) {
        throw std::runtime_error("Python not initialized!");
    }
    
    // Extract module name from script path (remove .py extension)
    std::string moduleName = scriptPath;
    size_t dotPos = moduleName.find_last_of('.');
    if (dotPos != std::string::npos) {
        moduleName = moduleName.substr(0, dotPos);
    }
    
    // Import the module
    PyObject* pName = PyUnicode_DecodeFSDefault(moduleName.c_str());
    PyObject* pModule = PyImport_Import(pName);
    Py_DECREF(pName);
    
    if (pModule == nullptr) {
        PyErr_Print();
        std::cerr << "Failed to load module: " << moduleName << std::endl;
        return 0;
    }
    
    // Get the function
    PyObject* pFunc = PyObject_GetAttrString(pModule, functionName.c_str());
    
    if (pFunc == nullptr || !PyCallable_Check(pFunc)) {
        if (PyErr_Occurred()) PyErr_Print();
        std::cerr << "Cannot find function: " << functionName << std::endl;
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
        return 0;
    }
    
    // Create a dictionary with Pokemon stats
    PyObject* pAttackerDict = PyDict_New();
    PyDict_SetItemString(pAttackerDict, "name", PyUnicode_FromString(attacker.getName().c_str()));
    PyDict_SetItemString(pAttackerDict, "current_hp", PyLong_FromLong(attacker.getCurrentHP()));
    PyDict_SetItemString(pAttackerDict, "max_hp", PyLong_FromLong(attacker.getMaxHP()));
    PyDict_SetItemString(pAttackerDict, "attack", PyLong_FromLong(attacker.getAttack()));
    PyDict_SetItemString(pAttackerDict, "defense", PyLong_FromLong(attacker.getDefense()));
    PyDict_SetItemString(pAttackerDict, "speed", PyLong_FromLong(attacker.getSpeed()));
    
    PyObject* pDefenderDict = PyDict_New();
    PyDict_SetItemString(pDefenderDict, "name", PyUnicode_FromString(defender.getName().c_str()));
    PyDict_SetItemString(pDefenderDict, "current_hp", PyLong_FromLong(defender.getCurrentHP()));
    PyDict_SetItemString(pDefenderDict, "max_hp", PyLong_FromLong(defender.getMaxHP()));
    PyDict_SetItemString(pDefenderDict, "attack", PyLong_FromLong(defender.getAttack()));
    PyDict_SetItemString(pDefenderDict, "defense", PyLong_FromLong(defender.getDefense()));
    PyDict_SetItemString(pDefenderDict, "speed", PyLong_FromLong(defender.getSpeed()));
    
    // Call the function
    PyObject* pArgs = PyTuple_Pack(2, pAttackerDict, pDefenderDict);
    PyObject* pValue = PyObject_CallObject(pFunc, pArgs);
    
    int damage = 0;
    if (pValue != nullptr) {
        damage = PyLong_AsLong(pValue);
        Py_DECREF(pValue);
    } else {
        PyErr_Print();
        std::cerr << "Call failed" << std::endl;
    }
    
    // Cleanup
    Py_DECREF(pArgs);
    Py_DECREF(pAttackerDict);
    Py_DECREF(pDefenderDict);
    Py_DECREF(pFunc);
    Py_DECREF(pModule);
    
    return damage;
}

std::function<int(Pokemon&, Pokemon&)> PythonSkillLoader::loadSkill(
    const std::string& scriptPath, const std::string& functionName) {
    
    return [scriptPath, functionName](Pokemon& attacker, Pokemon& defender) -> int {
        return executeSkill(scriptPath, functionName, attacker, defender);
    };
}
