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

        [[nodiscard]] int get_int(const std::string& key) const;
    };
}

#endif //SNEK_IO_CONFIG_HPP
