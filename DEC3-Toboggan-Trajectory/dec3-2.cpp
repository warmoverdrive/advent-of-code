#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <string>
#include "../headers/Inputv3.h"

size_t CheckCourses(const std::vector<std::string> &map);
size_t TraverseMap(const std::vector<std::string> &map, size_t deltaX, size_t deltaY);

int main()
{
    Input<std::string> in("PuzzleInput/Day3Input.txt", '\n');

    // Part 2 Specs:
    // start in top left index of input map (x0 y0)
    // Same as part 1, but plot different courses:
    //      Right 1 Down 1
    //      Right 3 Down 1 (slope already checked)
    //      Right 5 Down 1
    //      Right 7 Down 1
    //      Right 1 Down 2
    // Multiply all results together adn return.
    // Puzzle input is a series of strings defining the map

    auto start = std::chrono::high_resolution_clock::now();
    size_t result = CheckCourses(in.data);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Multiplied Collisions: " << result << '\n';
    std::cout << "Time to complete: " << duration << "ms\n";
}

size_t CheckCourses(const std::vector<std::string> &map)
{
    size_t result{1};
    std::vector<std::vector<size_t>> courses{
        {1, 1},
        {3, 1},
        {5, 1},
        {7, 1},
        {1, 2}};
    std::vector<size_t> results{};

    for (auto course : courses)
    {
        results.push_back(TraverseMap(map, course.at(0), course.at(1)));
    }

    for (size_t collisions : results)
    {
        result *= collisions;
    }

    return result;
}

size_t TraverseMap(const std::vector<std::string> &map, size_t deltaX, size_t deltaY)
{
    size_t collisions{};
    size_t x{};
    for (size_t y{}; y < map.size(); y += deltaY)
    {
        if (map.at(y).at(x) == '#')
            collisions++;
        x = (x + deltaX) % map.at(y).size();
    }

    return collisions;
}