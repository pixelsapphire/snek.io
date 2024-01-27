#ifndef SNEK_IO_CONFIG_HPP
#define SNEK_IO_CONFIG_HPP

#include <map>
#include <string>

namespace snek {

    class config {

        std::map<std::string, std::string> data;

    public:

        explicit config(const std::string& filename);

        [[nodiscard]] bool has_key(const std::string& key) const;

        [[nodiscard]] const std::string& get_string(const std::string& key) const;

        [[nodiscard]] int32_t get_int32(const std::string& key) const;

        [[nodiscard]] uint64_t get_uint64(const std::string& key) const;

        [[nodiscard]] static const std::string& path();
    };
}

#endif //SNEK_IO_CONFIG_HPP
