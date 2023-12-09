#include <iostream>

class Subject {
public:
    int f3 (int a, int b) { return a + b; }
};

int main() {
    Subject subject;

    Wrapper wrapper (&subject, &Subject::f3, {{"arg1", 0}, {"arg2", 0}});

    Engine engine;

    engine.registerCommand(&wrapper, "command1");

    std::cout << engine.execute("command1", {{"arg1", 4}, {"arg2", 5}}) << std::endl;
}
