#include "engine.hpp"

std::string scenarioPath = "../resources/scenario.json";

int main() {
    Engine engine;
    engine.LoadScenario(scenarioPath);
    engine.Run();
    return 0;
}