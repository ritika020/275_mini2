#include "config.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>


using json = nlohmann::json;

std::vector<std::string> get_children(const std::string& node_name) {
    // std::ifstream file("../../configs/overlay.json");
    std::ifstream file("/Users/ritikakhandelwal/Code/275_mini2/configs/overlay.json");
    std::cout << "[CONFIG] Reading overlay config from /Users/ritikakhandelwal/Code/275_mini2/configs/overlay.json" << std::endl;
    json j;
    file >> j;
    std::vector<std::string> children;
    for (const auto& c : j[node_name]) {
        children.push_back(c);
    }
    return children;
}
