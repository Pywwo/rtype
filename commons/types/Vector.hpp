
/* Created by Romain FOUYER on 18/11/2019 at 18:08. */


#ifndef RTYPE_VECTOR_HPP
#define RTYPE_VECTOR_HPP

#include <iostream>

namespace rtype {
    namespace commons {
        template <typename T>
        struct Vector2 {
            Vector2(T nx = 0, T ny = 0) : x(nx), y(ny) {}

            Vector2<T> &operator=(const Vector2<T> &otherVector)
            {
                x = otherVector.x;
                y = otherVector.y;
                return *this;
            }

            Vector2<T> &operator+=(const Vector2<T> &otherVector)
            {
                x += otherVector.x;
                y += otherVector.y;
                return *this;
            }

            Vector2<T> &operator-=(const Vector2<T> &otherVector)
            {
                x -= otherVector.x;
                y -= otherVector.y;
                return *this;
            }

            T x;
            T y;
        };
    }
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const rtype::commons::Vector2<T> &vector)
{
    os << "{" << vector.x << ";" << vector.y << "}";
    return os;
}


#endif //RTYPE_VECTOR_HPP
