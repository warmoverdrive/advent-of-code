#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <string>
#include "../headers/Inputv2.h"

size_t CheckValidPasswords(const std::vector<std::string> &input);
size_t *GetIndexies(const std::string &in);
bool IsValidPassword(const std::string &pass, char &test, size_t indexies[]);

int main()
{
    Input<std::string> in("PuzzleInput/Day2Input.txt", '\n');

    //Test data:
    // std::vector<std::string> data{
    //     "1-3 a: abcde",
    //     "1-3 b: cdefg",
    //     "2-9 c: ccccccccc"};
    // first substring is indexes of characters to test
    // second substring is character to test
    // third substring is password
    // check if 1 but not 2 indexes of the password match the test char
    // example: 1-3 a: abcde = true because 'a' appears at i1 and not i3

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
        size_t *indexies = GetIndexies(lineData.at(0));

        // parse second input
        char *test = &lineData.at(1).at(0);

        // check the password for validation - if valid inc counter
        if (IsValidPassword(lineData.at(2), *test, indexies))
            counter++;

        lineData.clear();
        sstream.clear(); // IMPORTANT TO CLEAR STREAMS TO AVOID INPUT ERROR
    }
    return counter;
}

size_t *GetIndexies(const std::string &input)
{
    static size_t indexies[2];
    std::stringstream sstream;
    sstream << input;

    int temp{};
    sstream >> indexies[0];
    sstream >> temp;         // sstream parses second number as negative
    indexies[1] = abs(temp); // get the abs value for the size_t

    sstream.clear();
    return indexies;
}

bool IsValidPassword(const std::string &pass, char &test, size_t indexies[])
{
    bool index1valid = pass.at(indexies[0] - 1) == test;
    bool index2valid = pass.at(indexies[1] - 1) == test;
    if (index1valid != index2valid)
        return true;
    else
        return false;
}