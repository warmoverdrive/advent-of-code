#include <iostream>
#include <vector>
#include <chrono>
#include "busInput.h"

ulong BusMaths(const std::vector<ulong> &input);

int main()
{ // ulong == unsigned long - defined in busInput.h
    std::vector<ulong> input = BusInput::GetBusData("PuzzleInput/Day13Input.txt", ',');

    auto start = std::chrono::high_resolution_clock::now();
    ulong result = BusMaths(input);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Result: " << result << '\n';
    std::cout << "Found in " << duration << "ms\n";
}

ulong BusMaths(const std::vector<ulong> &input)
{
    ulong departTime = input.at(0);
    int routeNum, waitingTime;

    for (int i{1}; i < input.size(); i++)
    {
        // get waiting time
        int temp = (((departTime / input.at(i)) + 1) * input.at(i)) - departTime;
        if (waitingTime == 0 || temp < waitingTime)
        {
            routeNum = input.at(i);
            waitingTime = temp;
        }
    }

    return routeNum * waitingTime;
}