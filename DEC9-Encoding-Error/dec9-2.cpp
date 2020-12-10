#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <chrono>
#include "../headers/Inputv4.h"

long long GetWeakness(std::vector<std::string> &input, size_t preambleSize);
long long FindWeakness(std::vector<long long> &input, size_t errorIndex);
long long DigWeakness(std::vector<long long> &input, size_t index, long long target, long long checkNum = 0);
size_t ErrorCheck(std::vector<long long> &input, size_t preambleSize);
std::vector<long long> ConvertToNum(std::vector<std::string> &input);

int main()
{
    // Test result should be 62, or 15+47
    size_t preamble{25}; // Set the preamble length (5 for test, 25 for real input)
    std::vector<std::string> input = Input::GetData<std::string>("PuzzleInput/Day9Input.txt", '\n');

    auto start = std::chrono::high_resolution_clock::now();
    long long result = GetWeakness(input, preamble);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "XMAS Encryption Weakness: " << result << '\n';
    std::cout << "Found in " << duration << "ms\n";
}

long long GetWeakness(std::vector<std::string> &input, size_t preambleSize)
{
    std::vector<long long> xmasInput = ConvertToNum(input);
    size_t errorIndex = ErrorCheck(xmasInput, preambleSize);
    return FindWeakness(xmasInput, errorIndex);
}

long long FindWeakness(std::vector<long long> &input, size_t index)
{
    long long targetNum = input.at(index);
    long long highVal{}, lowVal{LONG_LONG_MAX};
    size_t lowIndex{}, highIndex{};

    for (size_t i{index - 1}; i > 0; i--)
    {
        lowIndex = DigWeakness(input, i, targetNum);
        if (lowIndex > 0)
        {
            highIndex = i;
            break;
        }
    }

    for (size_t i{lowIndex}; i <= highIndex; i++)
    {
        if (input.at(i) < lowVal)
            lowVal = input.at(i);
        if (input.at(i) > highVal)
            highVal = input.at(i);
    }

    return lowVal + highVal;
}

long long DigWeakness(std::vector<long long> &input, size_t index, long long target, long long checkNum)
{
    if (index == 0)
        return 0;
    if (checkNum == 0)
        checkNum = input.at(index) + input.at(index - 1);
    else
    {
        checkNum += input.at(index - 1);
    }

    if (checkNum == target)
        return index - 1;
    else if (checkNum < target)
        return DigWeakness(input, index - 1, target, checkNum);
    else
        return 0;
}

size_t ErrorCheck(std::vector<long long> &input, size_t preambleSize)
{
    std::deque<long long> preamble{};
    size_t result{};

    for (size_t index{}; index < input.size(); index++)
    {
        if (preamble.size() < preambleSize)
            preamble.push_back(input.at(index));
        else
        {
            bool isValid{false};
            for (size_t a{0}; a < preamble.size(); a++)
            {
                for (size_t b{a + 1}; b < preamble.size(); b++)
                {
                    if (input.at(index) == preamble.at(a) + preamble.at(b))
                    {
                        isValid = true;
                        break;
                    }
                }
                if (isValid == true)
                    break;
            }
            if (isValid == false)
            {
                result = index;
                break;
            }
            else
            {
                preamble.pop_front();
                preamble.push_back(input.at(index));
            }
        }
    }

    return result;
}

std::vector<long long> ConvertToNum(std::vector<std::string> &input)
{
    std::vector<long long> convertedVec{};
    for (auto s : input)
    {
        convertedVec.push_back(std::stoll(s));
    }

    return convertedVec;
}