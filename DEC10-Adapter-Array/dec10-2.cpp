#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <map>
#include "../headers/Inputv4.h"

unsigned long long AdapterOptions(std::vector<size_t> &input);
void SortInput(std::vector<size_t> &input);
void DeepSearch(std::vector<size_t> &input, unsigned long long &iterator);

int main()
{
    std::vector<size_t> input = Input::GetNumberData<size_t>("PuzzleInput/Day10Input.txt", '\n');

    auto start = std::chrono::high_resolution_clock::now();
    unsigned long long result = AdapterOptions(input);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Result: " << result << '\n';
    std::cout << "Found in " << duration << "ms\n";
}

unsigned long long AdapterOptions(std::vector<size_t> &input)
{
    SortInput(input);

    unsigned long long iterator{1};
    DeepSearch(input, iterator);

    return iterator;
}

/* === Figured this solution out with help from u/Nunki3 on the A0C subreddit === */
void DeepSearch(std::vector<size_t> &input, unsigned long long &iterator)
{
    std::map<size_t, unsigned long long> pathMap;

    for (auto const &val : input)
    {
        pathMap[val] = 0;
    }
    pathMap[0]++;

    for (size_t i{0}; i < input.size(); i++)
    {
        auto r1 = std::find(input.begin() + i, input.end(), input.at(i) + 1);
        auto r2 = std::find(input.begin() + i, input.end(), input.at(i) + 2);
        auto r3 = std::find(input.begin() + i, input.end(), input.at(i) + 3);

        if (r1 != input.end())
            pathMap.at(*r1) += pathMap.at(input.at(i));
        if (r2 != input.end())
            pathMap.at(*r2) += pathMap.at(input.at(i));
        if (r3 != input.end())
            pathMap.at(*r3) += pathMap.at(input.at(i));
    }

    iterator = pathMap.at(input.at(input.size() - 1));
}

void SortInput(std::vector<size_t> &input)
{
    input.push_back(0);
    std::sort(input.begin(), input.end());
    input.push_back(input.at(input.size() - 1) + 3);
}