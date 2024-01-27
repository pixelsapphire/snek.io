#ifndef SNEK_IO_COMMON_UTILITY_HPP
#define SNEK_IO_COMMON_UTILITY_HPP

#include <string>

#ifdef __APPLE__

#include <mach-o/dyld.h>

#endif

#ifdef __clang__
#define __clang_std std
#else
#define __clang_std
#endif

namespace snek {
    [[nodiscard]] std::string get_executable_path();
}

#endif // SNEK_IO_COMMON_UTILITY_HPP
