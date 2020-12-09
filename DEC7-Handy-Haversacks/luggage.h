#ifndef LUGGAGE
#define LUGGAGE

#include <string>
#include <unordered_map>

/* === TODO === Add from Map of names and pointers */

class Luggage
{
private:
    std::string name{};
    std::unordered_map<Luggage *, size_t> contains;

public:
    void SetLuggageName(std::string &nameValue);
    std::string GetName() const;
    void AddToContainer(Luggage *luggage, size_t number);
    size_t SearchContainer(Luggage *luggage) const;

    Luggage(std::string nameValue);
};

Luggage::Luggage(std::string nameValue)
    : name{nameValue}, contains{} {};

void Luggage::SetLuggageName(std::string &nameValue) { name = nameValue; }

std::string Luggage::GetName() const { return name; }

void Luggage::AddToContainer(Luggage *luggage, size_t number)
{
    // If the input is already contained for some reason, don't add it again
    if (contains.find(luggage) != contains.end())
        return;
    contains.insert({luggage, number});
}

size_t Luggage::SearchContainer(Luggage *luggage) const
{
    auto search = contains.find(luggage);
    if (search != contains.end())
    { // if found, return the number of bags
        return search->second;
    } // if not found, return 0
    else
        return 0;
}

#endif