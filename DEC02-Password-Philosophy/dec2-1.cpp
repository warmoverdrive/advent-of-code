#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <string>
#include "../headers/Inputv2.h"

size_t CheckValidPasswords(const std::vector<std::string> &input);
size_t *GetRange(const std::string &in);
size_t GetAppearances(const std::string &in, char &test);

int main()
{
    Input<std::string> in("PuzzleInput/Day2Input.txt", '\n');

    //Test data:
    // std::vector<std::string> data{
    //     "1-3 a: abcde",
    //     "1-3 b: cdefg",
    //     "2-9 c: ccccccccc"};
    // first substring is range of valid repeats
    // second substring is character to test
    // third substring is password
    // check if test char is repeated no more and no less than range
    // example: 1-3 a: abcde = true because 'a' repeats once
    // example: 1-3 b: cdefg = false because 'b' never appears

    std::cout << "Data size: " << in.data.size() << '\n';

    auto start = std::chrono::high_resolution_clock::now();
    size_t validPasswords = CheckValidPasswords(in.data);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Valid passwords: " << validPasswords << '\n';
    std::cout << "Time to complete: " << duration << "ms\n";

    return 0;
}

size_t CheckValidPasswords(const std::vector<std::string> &input)
{
    size_t counter{};

    std::stringstream sstream;
    std::vector<std::string> lineData{};
    std::string item{};

    for (size_t line{}; line < input.size(); line++)
    {
        // split input string
        sstream << input.at(line);
        while (std::getline(sstream, item, ' '))
            lineData.push_back(item);

        // parse first input
        size_t *range = GetRange(lineData.at(0));

        // parse second input
        char *test = &lineData.at(1).at(0);

        // check count of chars in third input
        size_t repeats = GetAppearances(lineData.at(2), *test);

        // if in bounds inc counter
        if (repeats >= range[0] && repeats <= range[1])
            counter++;

        lineData.clear();
        sstream.clear(); // IMPORTANT TO CLEAR STREAMS TO AVOID INPUT ERROR
    }
    return counter;
}

size_t *GetRange(const std::string &input)
{
    static size_t range[2];
    std::stringstream sstream;
    sstream << input;

    int temp{};
    sstream >> range[0];
    sstream >> temp;      // sstream parses second number as negative
    range[1] = abs(temp); // get the abs value for the size_t

    sstream.clear();
    return range;
}

size_t GetAppearances(const std::string &input, char &test)
{
    size_t repeats{};
    for (char c : input)
        if (c == test)
            repeats++;
    return repeats;
}