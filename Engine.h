#ifndef METHOD_ENCAPSULATION_ENGINE_H
#define METHOD_ENCAPSULATION_ENGINE_H

#include <unordered_map>
#include "Wrapper.h"

class Engine {
    std::unordered_map<std::string, Wrapper *> commands;
public:
    int execute(const std::string& name, const std::unordered_map<std::string, int>& args) {
        if (!commands.contains(name))
            throw std::runtime_error("command not found");

        commands.at(name)->setArgs(args);
        return commands.at(name)->execute();
    }

    void registerCommand (Wrapper * wrapper, const std::string& name) {
        if (commands.contains(name))
            throw std::runtime_error("command has already been announced");
        commands.insert({name, wrapper});
    }
};


#endif //METHOD_ENCAPSULATION_ENGINE_H
