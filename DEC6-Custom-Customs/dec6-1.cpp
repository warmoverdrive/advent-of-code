#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <fstream>
#include "../headers/Inputv4.h"

/*  === Day 6 Part A Specs ===
    Parse the input for lines of characters. count each character only once (if it repeats dont count it)
    add the counts for each line of input together for the result

    Implimentation:
    create temp string
    take input string, and parse per char
    if char is between 'a' and 'z', check if it exists in temp
    if its not in temp, push back char
    else continue
    check size of temp string and add it to result
    repeat for each input string
*/

size_t GetAnswerCounts(const std::string &input);

int main()
{
    std::vector<std::string> data = Input::GetEmptyNewLineData("PuzzleInput/Day6Input.txt");

    size_t result{};

    auto start = std::chrono::high_resolution_clock::now();
    for (auto d : data)
    {
        result += GetAnswerCounts(d);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Sum of answer counts: " << result << '\n';
    std::cout << "Found in " << duration << "ms\n";
}

size_t GetAnswerCounts(const std::string &input)
{
    std::string temp{};
    for (char c : input)
    {
        if (c >= 'a' && c <= 'z') //filter out non-alpha chars
        {
            if (temp.find(c) == std::string::npos)
                temp.push_back(c);
        }
    }

    return temp.size();
}