#ifndef POWERCUBE_H
#define POWERCUBE_H
#include <iostream>
#include <unordered_map>
#include <functional>

class Powercube
{
    friend bool operator==(const Powercube &lhs, const Powercube &rhs);
    friend std::ostream &operator<<(std::ostream &os, const Powercube &rhs);
    friend Powercube operator+(const Powercube &lhs, const Powercube &rhs);

public:
    int x;
    int y;
    int z;

    Powercube() : Powercube(0, 0, 0) {}
    Powercube(int x = 0, int y = 0, int z = 0)
        : x{x}, y{y}, z{z} {}
};

Powercube operator+(const Powercube &lhs, const Powercube &rhs)
{
    return Powercube(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

std::ostream &operator<<(std::ostream &os, const Powercube &rhs)
{
    os << "[" << rhs.x << ", " << rhs.y << ", " << rhs.z << "]";
    return os;
}

bool operator==(const Powercube &lhs, const Powercube &rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

namespace std
{
    template <>
    struct hash<Powercube>
    {
        size_t operator()(const Powercube &cube) const
        {
            size_t x = std::hash<int>{}(cube.x);
            size_t y = std::hash<int>{}(cube.y);
            size_t z = std::hash<int>{}(cube.z);
            return x ^ y ^ (z << 1);
        }
    };
} // namespace std

#endif // POWERCUBE_H