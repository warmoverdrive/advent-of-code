// Completes in ~20k milliseconds

#include <iostream>
#include <vector>
#include <deque>
#include <chrono>
#include <unordered_map>

using MemMap = std::unordered_map<int, std::pair<int, int>>;

int const iterations{30000000}; // global cause of size issues
int spokenOrder[iterations]{};  // using an array for speed of access, bringing the calc to a
                                // "reasonable" 20 sec
int MemoryGame(std::vector<int> &startingNums);

int main()
{
    /* TEST INPUTS */
    //std::vector<int> startingNums{0, 3, 6}; // iterations10 = 0 : 175594
    //std::vector<int> startingNums{1, 3, 2}; // 1 : 2578
    // std::vector<int> startingNums{2,1,3};                // 10
    // std::vector<int> startingNums{1,2,3};                // 27
    // std::vector<int> startingNums{2,3,1};                // 78
    // std::vector<int> startingNums{3,2,1};                // 438
    //std::vector<int> startingNums{3, 1, 2}; // 1836

    std::vector<int> startingNums{13, 16, 0, 12, 15, 1}; // Puzzle Input

    auto start = std::chrono::high_resolution_clock::now();
    int result = MemoryGame(startingNums);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Result after " << iterations << " is " << result << ".\n";
    std::cout << "Found in " << duration << "ms\n";

    return 0;
}

int MemoryGame(std::vector<int> &startingNums)
{
    static MemMap memoryMap{};

    for (int i{}; i < startingNums.size(); i++)
    {
        spokenOrder[i] = startingNums.at(i);
        memoryMap[startingNums.at(i)].first = 1;
        memoryMap[startingNums.at(i)].second = i;
    }

    for (size_t i{startingNums.size()}; i < iterations; i++)
    {

        if (memoryMap[spokenOrder[i - 1]].first > 1)
        {
            spokenOrder[i] = (i - 1) - memoryMap[spokenOrder[i - 1]].second;
            memoryMap[spokenOrder[i - 1]].second = i - 1;
            memoryMap[spokenOrder[memoryMap[spokenOrder[i - 1]].second]].first++;
            memoryMap[spokenOrder[i]].first++;
        }
        else if (memoryMap[spokenOrder[i - 1]].first == 1)
        {
            spokenOrder[i] = 0;
            memoryMap[0].first++;
            memoryMap[spokenOrder[i - 1]].first++;
            memoryMap[spokenOrder[i - 1]].second = i - 1;
        }
        else
        {
            memoryMap[spokenOrder[i - 1]].first++;
            memoryMap[spokenOrder[i - 1]].second = i - 1;
            spokenOrder[i] = 0;
            memoryMap[0].first++;
            memoryMap[0].second = i;
        }

        // if (i % 10000 == 0 || i > 29999995)
        //     std::cout << i << '\n';
    }

    std::cout << "Unique numbers: " << memoryMap.size() << '\n';

    return spokenOrder[iterations - 1];
}