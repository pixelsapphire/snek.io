#ifndef SNEK_IO_VECTOR_2F_HPP
#define SNEK_IO_VECTOR_2F_HPP

#include <string>

namespace snek {

    class vector_2f {

        float x, y;

    public:

        static const vector_2f zero;

        vector_2f();

        vector_2f(float x, float y);

        vector_2f(int x, int y);

        [[nodiscard]] float get_x() const;

        [[nodiscard]] float get_y() const;

        vector_2f& operator=(const vector_2f& other) = default;

        vector_2f& operator=(vector_2f&& other) noexcept = default;

        vector_2f(const vector_2f& other) = default;

        vector_2f(vector_2f&& other) noexcept = default;

        vector_2f operator+(const vector_2f& other) const;

        vector_2f& operator+=(const vector_2f& other);

        vector_2f operator-(const vector_2f& other) const;

        vector_2f& operator-=(const vector_2f& other);

        vector_2f operator*(float scalar) const;

        friend vector_2f operator*(float scalar, const vector_2f& vector);

        vector_2f& operator*=(float scalar);

        vector_2f operator/(float scalar) const;

        vector_2f& operator/=(float scalar);

        bool operator==(const vector_2f& other) const;

        [[nodiscard]] float length() const;

        [[nodiscard]] vector_2f normalized() const;

        [[nodiscard]] std::string str() const;

        [[nodiscard]] static snek::vector_2f direction_change(const snek::vector_2f& origin,
                                                              const snek::vector_2f& target, float delta_max);
    };
}


#endif //SNEK_IO_VECTOR_2F_HPP
