#include <iostream>
#include <vector>
#include <deque>
#include <chrono>
#include <unordered_map>

int MemoryGame(std::vector<int> &startingNums, int &iterations);

int main()
{
    /* TEST INPUTS */
    //std::vector<int> startingNums{0, 3, 6};               // iterations10 = 0
    //std::vector<int> startingNums{1, 3, 2};               // 1
    // std::vector<int> startingNums{2,1,3};                // 10
    // std::vector<int> startingNums{1,2,3};                // 27
    // std::vector<int> startingNums{2,3,1};                // 78
    // std::vector<int> startingNums{3,2,1};                // 438
    // std::vector<int> startingNums{3, 1, 2};              // 1836

    std::vector<int> startingNums{13, 16, 0, 12, 15, 1}; // Puzzle Input
    int iterations{2020};

    auto start = std::chrono::high_resolution_clock::now();
    int result = MemoryGame(startingNums, iterations);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Result after " << iterations << " is " << result << ".\n";
    std::cout << "Found in " << duration << "ms\n";
}

int MemoryGame(std::vector<int> &startingNums, int &iterations)
{
    std::unordered_map<int, int> memoryMap{};
    std::deque<int> spokenOrder{};

    for (auto num : startingNums)
    {
        spokenOrder.push_back(num);
        memoryMap.emplace(num, 0);
    }

    for (int i{}; i < iterations - startingNums.size(); i++)
    {
        if (memoryMap.find(spokenOrder.back()) != memoryMap.end())
        {
            if (memoryMap[spokenOrder.back()] == 0)
            {
                memoryMap[spokenOrder.back()]++;
                spokenOrder.push_back(0);
                if (memoryMap.find(0) == memoryMap.end())
                    memoryMap[0];
                else
                    memoryMap[0]++;
            }
            else
            {
                int n{0};
                do
                {
                    n++;
                } while (*(spokenOrder.rbegin() + n) != spokenOrder.back());
                spokenOrder.push_back(n);
                if (memoryMap.find(n) == memoryMap.end())
                    memoryMap[n];
                else
                    memoryMap[n]++;
            }
        }
        else
        {
            memoryMap[spokenOrder.back()]++;
            spokenOrder.push_back(0);
            memoryMap[0]++;
        }
    }

    return spokenOrder.back();
}