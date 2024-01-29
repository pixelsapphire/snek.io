#include <cmath>
#include <cstdio>
#include <sstream>
#include "common_utility.hpp"
#include "utility.hpp"

float snek::sgn(float value, float if_zero) {
    if (value > 0) return 1;
    else if (value < 0) return -1;
    else return if_zero;
}

std::string snek::to_string(float value) {
    const std::string str = std::to_string(value);
    return str.substr(0, str.find('.') + 2);
}

bool snek::is_nearby(const snek::vector2f& position1, const snek::vector2f& position2, float distance) {
    float length = __clang_std::powf(position1.x - position2.x, 2) +
                   __clang_std::powf(position1.y - position2.y, 2);
    return length <= __clang_std::powf(distance, 2);
}

std::string snek::get_local_ip() {
    FILE* fp;
#ifdef __APPLE__
    fp = popen("/usr/sbin/ipconfig getifaddr en0", "r");
#elif __linux__
    fp = popen("/usr/bin/hostname -I", "r");
#else
    return "";
#endif
    if (fp == nullptr) return "";
    std::ostringstream ss;
    char path[1035];
    while (fgets(path, sizeof(path), fp) != nullptr) ss << path;
    pclose(fp);
    std::string ip = ss.str();
    ip.erase(ip.find_last_not_of(" \n\r\t") + 1);
    return ip;
}