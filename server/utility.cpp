#include <cmath>
#include <cstdio>
#include <sstream>
#include "common_utility.hpp"
#include "utility.hpp"

bool snek::is_nearby(const snek::vector2f& position, const snek::vector2f& segment, float distance) {
    float length = __clang_std::powf(position.x - segment.x, 2) +
                   __clang_std::powf(position.y - segment.y, 2);
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
    std::stringstream ss;
    char path[1035];
    while (fgets(path, sizeof(path), fp) != nullptr) ss << path;
    pclose(fp);
    std::string ip = ss.str();
    ip.erase(ip.find_last_not_of(" \n\r\t") + 1);
    return ip;
}

float snek::sgn(float value, float if_zero) {
    if (value > 0) return 1;
    else if (value < 0) return -1;
    else return if_zero;
}