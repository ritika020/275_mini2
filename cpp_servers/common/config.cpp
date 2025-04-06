#include "config.hpp"
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

std::vector<std::string> get_children(const std::string& node_name) {
    std::ifstream file("../../configs/overlay.json");
    json j;
    file >> j;
    std::vector<std::string> children;
    for (const auto& c : j[node_name]) {
        children.push_back(c);
    }
    return children;
}
