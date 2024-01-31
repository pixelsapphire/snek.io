#ifndef SNEK_IO_COMMON_UTILITY_HPP
#define SNEK_IO_COMMON_UTILITY_HPP

#include <sstream>
#include <string>

#ifdef __clang__
#define __clang_std std
#else
#define __clang_std
#endif

namespace snek {

    [[nodiscard]] std::string get_executable_path();

    template<typename ...Args>
    [[nodiscard]] std::string concat(Args&& ...args) {
        std::ostringstream oss;
        (oss << ... << std::forward<Args>(args));
        return oss.str();
    }
}

#endif // SNEK_IO_COMMON_UTILITY_HPP
