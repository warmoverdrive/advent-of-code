#include <iostream>
#include <vector>
#include <chrono>
#include "busInput.h"

ulong BusMaths(const std::vector<int> &input);
ulong FindStartingNum(const std::vector<int> &input);

int main()
{ // ulong == unsigned long - defined in busInput.h
    std::vector<int> input = BusInput::GetExtraBusData("PuzzleInput/Day13Test.txt", ',');

    for (auto s : input)
    {
        std::cout << s << ", ";
    }

    auto start = std::chrono::high_resolution_clock::now();
    ulong result = BusMaths(input);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Result: " << result << '\n';
    std::cout << "Found in " << duration << "ms\n";
}

ulong BusMaths(const std::vector<int> &input)
{
    //ulong i = FindStartingNum(input);

    ulong i = input.at(0);
    while (1)
    {
        ulong t = i;
        if (t % input.at(0) == 0)
        {
            t++;
            for (int n{1}; n < input.size(); n++)
            {
                if (n % 2 == 0 && input.at(n) % t == 0)
                {
                    if (n == input.size() - 1)
                        return i;
                    else
                        t++; // continue
                }
                else if (n % 2 == 1)
                    t += input.at(n);
                else
                    break;
            }
        }

        i += input.at(0);
        std::cout << '.';
    }

    return 0;
}

ulong FindStartingNum(const std::vector<int> &input)
{
    ulong startingNum{};
    int mod{};
    for (int i{}; i < input.size(); i += 2)
    {
        std::cout << input.at(i);
        if (input.at(i) > startingNum)
            startingNum = input.at(i);
    }

    mod = startingNum % input.at(0);
    startingNum = (startingNum / input.at(0));

    return startingNum;
}