#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <string>
#include "../headers/Inputv3.h"

size_t TraverseMap(const std::vector<std::string> &map);

int main()
{
    Input<std::string> in("PuzzleInput/Day3Input.txt", '\n');

    // Part 1 Specs:
    // start in top left index of input map (x0 y0)
    // each step move right 3, down 1 (x+3, y+1)
    // on each step check if char at index is #, if so count++
    // Map must be "extended" infinitely to the right
    // use sizeof % x for easy lateral looping of data (ie, 127 % 127 = 0, 127 % 129 = 2)
    // Puzzle input is a series of strings defining the map

    auto start = std::chrono::high_resolution_clock::now();
    size_t collisions = TraverseMap(in.data);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Collisions: " << collisions << '\n';
    std::cout << "Time to complete: " << duration << "ms\n";
}

size_t TraverseMap(const std::vector<std::string> &map)
{
    size_t collisions{};
    size_t x{};
    for (std::string y : map)
    {
        if (y.at(x) == '#')
            collisions++;
        x = (x + 3) % y.size();
    }

    return collisions;
}