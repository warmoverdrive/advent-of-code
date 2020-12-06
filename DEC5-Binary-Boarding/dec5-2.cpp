#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>
#include "../headers/Inputv3.h"

/* === Part 2 Specs ===
    Using the seat IDs from part 1, find your seat.

    Add all seat IDs to a vector, and use a sort algo to get them in order

    Quick and dirty solution is to iterate through the list, checking each next seat
    against the current: if subtracting the current seat from the next = 2, then our seat
    is 1 less than the next in the vector

    We can reuse the BinarySort and GetPassID functions from the last part
*/

size_t BinarySort(const std::string &string, size_t lowerBound, size_t upperBound);
size_t GetPassID(const std::string &pass);
size_t FindSeat(const std::vector<std::string> &input);
std::vector<size_t> *ConvertToIDs(const std::vector<std::string> &input);

int main()
{
    Input<std::string> in("PuzzleInput/Day5Input.txt", '\n');

    auto start = std::chrono::high_resolution_clock::now();
    size_t result = FindSeat(in.data); // TODO REPLACE WITH FIND MY SEAT FUNCTION
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "My seat is ID " << result << '\n';
    std::cout << "Found in " << duration << "ms\n";
}

size_t FindSeat(const std::vector<std::string> &input)
{
    std::vector<size_t> *seatIDs = ConvertToIDs(input);

    std::sort(seatIDs->begin(), seatIDs->end());

    for (size_t i{}; i < seatIDs->size(); i++)
    {
        if (seatIDs->at(i + 1) - seatIDs->at(i) == 2)
            return seatIDs->at(i) + 1;
    }
}

std::vector<size_t> *ConvertToIDs(const std::vector<std::string> &input)
{
    static std::vector<size_t> seatIDs{};

    for (std::string pass : input)
    {
        seatIDs.push_back(GetPassID(pass));
    }

    return &seatIDs;
}

size_t GetPassID(const std::string &pass)
{
    size_t passID{};

    size_t row = BinarySort(pass.substr(0, 7), 0, 127);
    size_t column = BinarySort(pass.substr(7, std::string::npos), 0, 7);

    passID = row * 8 + column;

    return passID;
}

size_t BinarySort(const std::string &string, size_t lowerBound, size_t upperBound)
{
    size_t result{};
    size_t divisor{(upperBound + 1) / 2}; // procedurally get the divisor ie 128/2 = 64,
                                          // so we can add or subtract from the bounds
                                          //using this and divide by two afterwards
    // F and L = lower half			B and R = upper half
    for (char c : string)
    {
        if (c == 'F' || c == 'L')
        {
            upperBound -= divisor;
            divisor /= 2;
        }
        else if (c == 'B' || c == 'R')
        {
            lowerBound += divisor;
            divisor /= 2;
        }
    }

    if (string.at(string.size() - 1) == 'F' || string.at(string.size() - 1) == 'L')
        result = lowerBound;
    else
        result = upperBound;

    return result;
}