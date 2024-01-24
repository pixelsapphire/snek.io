#ifndef SNEK_IO_VECTOR_2F_HPP
#define SNEK_IO_VECTOR_2F_HPP

namespace snek {

    class vector_2f {

        float x, y;

    public:

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

        vector_2f& operator*=(float scalar);

        vector_2f operator/(float scalar) const;

        vector_2f& operator/=(float scalar);

        friend vector_2f operator*(float scalar, const vector_2f& vector);

        bool operator==(const vector_2f& other) const;
    };
}


#endif //SNEK_IO_VECTOR_2F_HPP
