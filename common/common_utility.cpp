#include <filesystem>
#include "common_utility.hpp"

#ifdef __APPLE__

#include <mach-o/dyld.h>

#endif

std::string snek::get_executable_path() {
#ifdef __APPLE__
    std::string path(1024, 0);
    auto size = uint32_t(path.length());
    if (_NSGetExecutablePath(path.data(), &size) == -1 or path.empty()) return ".";
    return std::filesystem::canonical(std::filesystem::path(path)).parent_path().string();
#elif __linux__
    return std::filesystem::canonical(std::filesystem::path("/proc/self/exe")).parent_path().string();
#else
    return ".";
#endif
}