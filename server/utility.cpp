#include <cmath>
#include <cstdio>
#include <sstream>
#include "common_utility.hpp"
#include "utility.hpp"

bool snek::is_nearby(const snek::vector_2f& position, const snek::vector_2f& segment, float distance) {
    float length = __clang_std::powf(position.get_x() - segment.get_x(), 2) +
                   __clang_std::powf(position.get_y() - segment.get_y(), 2);
    return length <= __clang_std::powf(distance, 2);
}

std::string snek::get_local_ip() {
    FILE* fp;
#ifdef __APPLE__
    fp = popen("/usr/sbin/ipconfig getifaddr en0", "r");
#elif __linux__
    fp = popen("/usr/bin/hostname --ip-address", "r");
#else
    return "";
#endif
    if (fp == nullptr) return "";
    std::stringstream ss;
    char path[1035];
    while (fgets(path, sizeof(path), fp) != nullptr) ss << path;
    pclose(fp);
    std::string ip = ss.str();
    ip.resize(ip.size() - 1);
    return ip;
}