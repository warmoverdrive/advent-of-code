#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include "../headers/Inputv4.h"

size_t VoltDifference(std::vector<size_t> &input);

int main()
{
    std::vector<size_t> input = Input::GetNumberData<size_t>("PuzzleInput/Day10Input.txt", '\n');

    auto start = std::chrono::high_resolution_clock::now();
    size_t result = VoltDifference(input);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Result: " << result << '\n';
    std::cout << "Found in " << duration << "ms\n";
}

size_t VoltDifference(std::vector<size_t> &input)
{
    std::sort(input.begin(), input.end());

    input.insert(input.begin(), 0);
    input.insert(input.end(), input.at(input.size() - 1) + 3);

    size_t voltDiff1{}, voltDiff3{};

    for (size_t i{}; i < input.size() - 1; i++)
    {
        if (input.at(i + 1) - input.at(i) == 1)
            voltDiff1++;
        else if (input.at(i + 1) - input.at(i) == 3)
            voltDiff3++;
    }

    std::cout << voltDiff1 << " :: " << voltDiff3 << '\n';

    return voltDiff1 * voltDiff3;
}
