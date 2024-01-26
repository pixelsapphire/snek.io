#include <fstream>
#include "config.hpp"

snek::config::config(const std::string& filename) {
    std::ifstream file(filename);
    if (not file.is_open()) throw std::runtime_error("Failed to open config file");
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        auto delimiter_pos = line.find('=');
        auto name = line.substr(0, delimiter_pos);
        auto value = line.substr(delimiter_pos + 1);
        data[name] = value;
    }
}

bool snek::config::has_key(const std::string& key) const { return data.contains(key); }

const std::string& snek::config::get_string(const std::string& key) const { return data.at(key); }

int32_t snek::config::get_int32(const std::string& key) const { return std::stoi(data.at(key)); }

uint64_t snek::config::get_uint64(const std::string& key) const { return std::stoul(data.at(key)); }