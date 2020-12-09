#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <chrono>
#include "../headers/Inputv4.h"
#include "luggage.h"

/* === Day 7A Specs === 
        Input is a list of rules formated as:
    "vibrant plum bags contain 5 faded blue bags, 6 dotted black bags."

    Given the list of bag colors and contents, how many bags could at some
    point contain a shiny gold bag?

    We're store our data in an unordered map:
        <str::string, Luggage *> 
            first.string name of luggage for easy search
            second.unique pointer to luggage object

    Each input starts with 2 words (luggage name). Pull the first two words,
    and check the map of luggages to see if it already exists. if not,
    create a unique pointer of a new Luggage object, setting the name as the
    input. Store that Luggage Object in the map and continue. If it
    already exists, continue.

    The next two words ("bags contain") are useless to us.

    The next words are what is in the bags. 
    If the next word is No, then the bag is empty, move on.
    Else: (DoWhile here) the next three words are important.
        first word is the number of bags
        next two are the name of the next bag.
    Take the bag name and search the map for it. If it doesnt exist,
    create the new bag and add it to the Master Map. Once its on the map,
    add the current bag to the contain bag's From Map, and add this map 
    to the current bags Contain map.
    Then find the next ',' char in the string, and repeat the process
    until there are no more commas to be found, indicating the end of the
    string.

    Repeat this for all rules (input file).

    Once our maps are created and populated, find "shiny gold" luggage
    object from the Master Map. Search backwards through its From map to each
    luggage object referenced there recursively, adding the name of that Luggage
    color to a vector as you go, ignoring duplicates
    The end result of the recursion vector's size will be the puzzle answer.
*/

size_t HaversacksSearcher(std::vector<std::string> &input);

int main()
{
    std::vector<std::string> input = Input::GetData<std::string>("PuzzleInput/Day7Test.txt", '\n');

    auto start = std::chrono::high_resolution_clock::now();
    size_t result = HaversacksSearcher(input); // DO THE PUZZLE
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "The number of bags for Shiny Gold is: " << result << '\n';
    std::cout << "Result found in " << duration << "ms\n";
}

size_t HaversacksSearcher(std::vector<std::string> &input)
{
    // TODO IMPLIMENT
}