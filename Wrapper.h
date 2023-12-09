#ifndef METHOD_ENCAPSULATION_WRAPPER_H
#define METHOD_ENCAPSULATION_WRAPPER_H

#include <iostream>
#include <vector>
#include <functional>

class Wrapper {
    std::function<int (const std::vector<int> & vector_args_for_func)> wrapFunc;
    std::unordered_map<std::string, int> funcArgs;

    template<typename Subject, typename Method, size_t... argsNum>
    int callFunc(Subject* subject, Method method, std::vector<int> args, std::index_sequence<argsNum...>){
        return((subject->*method)(args[argsNum]...));
    }


public:
    template<typename Subject, typename ...Args>
    Wrapper(Subject * sub, int (Subject::*func)(Args...), std::unordered_map<std::string, int> initArgs) {
        funcArgs = std::move(initArgs);

        wrapFunc = [this, sub, func] (std::vector<int> inputArgs) -> int {
            return callFunc(sub, func, inputArgs, std::make_index_sequence<sizeof...(Args)>{});
        };
    }

    void setArgs (const std::unordered_map<std::string, int>& inputArgs) {
        if (inputArgs.size() != funcArgs.size())
            throw std::runtime_error("incorrect signature");

        for (const auto& [key, value] : funcArgs){
            if (!inputArgs.contains(key))
                throw std::runtime_error("incorrect signature");
            funcArgs[key] = inputArgs.at(key);
        }
    }

    int execute () {
        std::vector<int> args;
        for (const auto& [key, value] : funcArgs)
            args.push_back(value);
        return wrapFunc(args);
    }
};


#endif //METHOD_ENCAPSULATION_WRAPPER_H
