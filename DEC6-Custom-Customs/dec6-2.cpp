#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <sstream>
#include <unordered_map>
#include "../headers/Inputv4.h"

/*  === Day 6 Part B Specs ===
    Goal: Find out how many questions everyone in a GROUP answered the same.
    Groups are seperated by an extra new line.
    Test data's result should be 6

    Implimentation:
    Parse the input for strings seperated by spaces, store in a vector of strings
    for each string, read each char into an unordered map, incrementing for repeats
    compare the char's repeats against the size of the vector of answers, inc counter
    return counter - add to result
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
    static std::stringstream sstream;
    static std::string temp{};
    static std::vector<std::string> answers{};
    static std::unordered_map<char, size_t> chars{};
    size_t count{};

    sstream << input;
    while (sstream >> temp)
        answers.push_back(temp);

    for (std::string str : answers)
    {
        for (char c : str)
        {
            if (chars.find(c) == chars.end())
                chars.insert({c, 1});
            else
                chars[c]++;
        }
    }
    for (auto set : chars)
    {
        if (set.second == answers.size())
            count++;
    }

    chars.clear();
    answers.clear();
    sstream.clear();

    return count;
}