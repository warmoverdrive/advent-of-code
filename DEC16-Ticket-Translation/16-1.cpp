#include <iostream>
#include <vector>
#include <chrono>
#include "ticketInput.h"

unsigned long TicketScanErrorRate(const Input &input);
bool IsValid(const Fields &fields, int value);
bool InRange(const Range &range, int value);

int main()
{
    //Input input("PuzzleInput/Day16Test.txt"); // Test Input
    Input input("PuzzleInput/Day16Input.txt"); // Puzzle Input

    //input.DisplayContents();

    auto start = std::chrono::high_resolution_clock::now();
    auto result = TicketScanErrorRate(input);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "\nTicket Scanning Error Rate: " << result << '\n';
    std::cout << "Found in " << duration << "ms\n";
}

unsigned long TicketScanErrorRate(const Input &input)
{
    std::vector<int> errorVals{};
    unsigned long tScanErrorRate{};

    for (auto &ticket : input.nearbyTicks)
    {
        for (auto val : ticket)
        {
            if (IsValid(input.fields, val))
                continue;
            else
                errorVals.push_back(val);
        }
    }

    for (auto val : errorVals)
    {
        tScanErrorRate += val;
    }
    return tScanErrorRate;
}

bool IsValid(const Fields &fields, int value)
{
    bool isPossiblyValid{};
    for (auto &field : fields)
    {
        if (InRange(field.second.first, value) || InRange(field.second.second, value))
        {
            isPossiblyValid = true;
            break;
        }
    }

    return isPossiblyValid;
}

bool InRange(const Range &range, int value)
{
    if (value >= range.first && value <= range.second)
        return true;
    else
        return false;
}