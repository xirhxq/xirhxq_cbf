#include <iostream>
#include "nlohmann/json.hpp"
using json = nlohmann::json;

int main() {
    freopen("../data/test.json", "w", stdout);
    json j;
    j["pi"] = 3.141;
    j["happy"] = true;
    j["nothing"] = nullptr;
    j["answer"]["everything"] = 42;
    j["object"] = { {"currency", "USD"}, {"value", 42.99}};
    json k;
    k.push_back(j);
    j["pi"] = 3.14;
    j["new"].push_back({{"x", 1}, {"y", 1}});
    k.push_back(j);
    k[2]["state"] = true;
    k[2]["time"] = 1.0;
    std::cout << k.dump(4) << std::endl;
    return 0;
}