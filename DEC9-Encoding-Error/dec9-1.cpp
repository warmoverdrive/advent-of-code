#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <chrono>
#include "../headers/Inputv4.h"

/*  === NOTE: 
    Day9Test.txt expects a preample of 5 resulting in 127.
    Real puzzle input expects a preamble of 25.
*/

long long XMASCheck(std::vector<std::string> &input, size_t preambleSize);
std::vector<long long> ConvertToNum(std::vector<std::string> &input);

int main()
{
    size_t preamble{25}; // Set the preamble length (5 for test, 25 for real input)
    std::vector<std::string> input = Input::GetData<std::string>("PuzzleInput/Day9Input.txt", '\n');

    auto start = std::chrono::high_resolution_clock::now();
    long long result = XMASCheck(input, preamble);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "First number not the sum of preamble: " << result << '\n';
    std::cout << "Found in " << duration << "ms\n";
}

long long XMASCheck(std::vector<std::string> &input, size_t preambleSize)
{
    std::vector<long long> xmasInput = ConvertToNum(input);
    std::deque<long long> preamble{};
    long long result{};

    for (auto i : xmasInput)
    {
        if (preamble.size() < preambleSize)
            preamble.push_back(i);
        else
        {
            bool isValid{false};
            for (size_t a{0}; a < preamble.size(); a++)
            {
                for (size_t b{a + 1}; b < preamble.size(); b++)
                {
                    //std::cout << "testing " << i << " == " << preamble.at(a) << " + " << preamble.at(b) << '\n';
                    if (i == preamble.at(a) + preamble.at(b))
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
                result = i;
                break;
            }
            else
            {
                preamble.pop_front();
                preamble.push_back(i);
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