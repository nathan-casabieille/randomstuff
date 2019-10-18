#include <iostream>
#include <string>
#include <map>

//VariablesManager by Nathan.Casabieille
//Need to add templates for data types

class VariablesManager {
private:
    std::map<std::string, std::string> variablesMap;
    bool exists(std::string variableName){
        std::map<std::string, std::string>::iterator it = variablesMap.find(variableName);
        if (it != variablesMap.end())
            return true;
        return false;
    }
public:
    void mainLoop();
    bool add(std::string variableName, std::string variableValue){
        if (exists(variableName))
            return false;
        variablesMap[variableName] = variableValue;
        return true;
    }
    bool update(std::string variableName, std::string variableValue){
        if (!exists(variableName))
            return false;
        variablesMap[variableName] = variableValue;
        return  true;
    }
    bool remove(std::string variableName){
        if (!exists(variableName))
            return false;
        variablesMap.erase(variableName);
        return true;
    }
    void dump(){
        std::map<std::string, std::string>::iterator it = variablesMap.begin();
        for (; it != variablesMap.end(); it++){
            std::cout << it->first << " = " << it->second << "\n";
        }
    }
};

void VariablesManager::mainLoop() {
    VariablesManager& localVariablesManager = *this;
    std::string cmd;
    std::string variableName, variableValue;
    while (1) {
        std::cout << "action  (c/u/r/d) : ";
        std::cin >> cmd;
        if (cmd == "c"){
            std::cout << "Variable name : ";
            std::cin >> variableName;
            std::cout << "Variable value : ";
            std::cin >> variableValue;
            if (!localVariablesManager.add(variableName, variableValue))
                std::cerr << "This variable already exists.\n";
        }
        else if (cmd == "u"){
            std::cout << "Variable name : ";
            std::cin >> variableName;
            std::cout << "Variable value : ";
            std::cin >> variableValue;
            if (!localVariablesManager.update(variableName, variableValue))
                std::cerr << "This variable does not exists.\n";
        }
        else if (cmd == "r"){
            std::cout << "Variable name : ";
            std::cin >> variableName;
            if (!localVariablesManager.remove(variableName))
                std::cerr << "This variable does not exists.\n";
        }
        else if (cmd == "d")
            localVariablesManager.dump();
        else
            std::cerr << "Syntax Error, \"" << cmd << "\" does not exists.\n";
    }
}

int main(int argc, char** argv) {
    VariablesManager* localVariablesManagerPointer = new VariablesManager;
    localVariablesManagerPointer -> mainLoop();
    delete localVariablesManagerPointer;
    return (1);
}
