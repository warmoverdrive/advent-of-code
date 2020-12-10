#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include "../headers/Inputv4.h"

unsigned long long AdapterOptions(std::vector<size_t> &input);
void SortInput(std::vector<size_t> &input);
void DeepSearch(std::vector<size_t> &input, unsigned long long &iterator, size_t index);

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

    unsigned long long iterator{};
    DeepSearch(input, iterator, 0);

    return iterator;
}

void DeepSearch(std::vector<size_t> &input, unsigned long long &iterator, size_t index)
{
    if (index == input.size() - 1)
    {
        iterator++;
    }
    else
    {
        size_t plus1 = input.at(index) + 1;
        auto result = std::find(input.begin() + index, input.end(), plus1);
        if (result != input.end())
        {
            DeepSearch(input, iterator, result - input.begin()); // result is an iterator so
                                                                 // we have to subtract the beginning
        }                                                        // from it to resovle the index
        size_t plus2 = input.at(index) + 2;
        result = std::find(input.begin() + index, input.end(), plus2);
        if (result != input.end())
        {
            DeepSearch(input, iterator, result - input.begin());
        }
        size_t plus3 = input.at(index) + 3;
        result = std::find(input.begin() + index, input.end(), plus3);
        if (result != input.end())
        {
            DeepSearch(input, iterator, result - input.begin());
        }
    }
}

void SortInput(std::vector<size_t> &input)
{
    input.push_back(0);
    std::sort(input.begin(), input.end());
    input.push_back(input.at(input.size() - 1) + 3);
}