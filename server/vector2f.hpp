#ifndef SNEK_IO_VECTOR2F_HPP
#define SNEK_IO_VECTOR2F_HPP

#include <string>

namespace snek {

    struct vector2f {

        float x, y;

        static const vector2f zero;

        vector2f();

        vector2f(float x, float y);

        vector2f& operator=(const vector2f& other) = default;

        vector2f& operator=(vector2f&& other) noexcept = default;

        vector2f(const vector2f& other) = default;

        vector2f(vector2f&& other) noexcept = default;

        vector2f operator+(const vector2f& other) const;

        vector2f& operator+=(const vector2f& other);

        vector2f operator-(const vector2f& other) const;

        vector2f& operator-=(const vector2f& other);

        vector2f operator*(float scalar) const;

        friend vector2f operator*(float scalar, const vector2f& vector);

        vector2f& operator*=(float scalar);

        vector2f operator/(float scalar) const;

        vector2f& operator/=(float scalar);

        bool operator==(const vector2f& other) const;

        [[nodiscard]] float length() const;

        [[nodiscard]] vector2f normalized() const;

        [[nodiscard]] std::string str() const;

        [[nodiscard]] static snek::vector2f direction_change(const snek::vector2f& origin,
                                                             const snek::vector2f& target, float delta_max);
    };
}


#endif //SNEK_IO_VECTOR2F_HPP
