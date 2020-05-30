/*
** EPITECH PROJECT, 2020
** Nathan Casabieille
** File description:
** variables manager
*/

#include <iostream>
#include <string>
#include <map>

class VariablesManager {
private:
    std::map<std::string, std::string> variablesMap;

    bool exists(std::string variableName){
        std::map<std::string, std::string>::iterator it = variablesMap.find(variableName);

        if (it != variablesMap.end()) {
            return (true);
        }
        return (false);
    }
public:
    void mainLoop();

    void getVariableName(std::string &variableName)
    {
        std::cout << "Variable name : ";
        std::cin >> variableName;
    }

    void getVariableValue(std::string &variableValue)
    {
        std::cout << "Variable value : ";
        std::cin >> variableValue;
    }

    bool add(std::string variableName, std::string variableValue){
        if (exists(variableName)) {
            return (false);
        }
        variablesMap[variableName] = variableValue;
        return (true);
    }

    bool update(std::string variableName, std::string variableValue){
        if (!exists(variableName)) {
            return (false);
        }
        variablesMap[variableName] = variableValue;
        return  (true);
    }

    bool remove(std::string variableName){
        if (!exists(variableName)) {
            return (false);
        }
        variablesMap.erase(variableName);
        return (true);
    }

    void dump(){
        std::map<std::string, std::string>::iterator it = variablesMap.begin();

        for (; it != variablesMap.end(); it++){
            std::cout << it->first << " = " << it->second << "\n";
        }
    }
};

void VariablesManager::mainLoop() {
    bool active = true;
    std::string cmd;
    std::string variableName, variableValue;
    VariablesManager& localVariablesManager = *this;

    while (active) {
        std::cout << "action  (c/u/r/d/q) : ";
        std::cin >> cmd;
        if (cmd == "c"){ // create a variable
            getVariableName(variableName);
            getVariableValue(variableValue);
            if (!localVariablesManager.add(variableName, variableValue)) {
                std::cerr << "This variable already exists.\n";
            }
        }
        else if (cmd == "u"){ // modify a variable
            getVariableName(variableName);
            getVariableValue(variableValue);
            if (!localVariablesManager.update(variableName, variableValue)) {
                std::cerr << "This variable does not exists.\n";
            }
        }
        else if (cmd == "r"){ // delete a variable
            getVariableName(variableName);
            if (!localVariablesManager.remove(variableName)) {
                std::cerr << "This variable does not exists.\n";
            }
        }
        else if (cmd == "d") { // display variables
            localVariablesManager.dump();
        }
        else if (cmd == "q") { // quit
            active = false;
        }
        else {
            std::cerr << "Syntax Error, \"" << cmd << "\" does not exists.\n";
        }
    }
}

int main(int argc, char** argv) {
    VariablesManager *localVariablesManagerPointer = new VariablesManager;

    localVariablesManagerPointer->mainLoop();
    delete localVariablesManagerPointer;
    return (1);
}
