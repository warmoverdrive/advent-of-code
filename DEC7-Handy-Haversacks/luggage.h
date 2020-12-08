#ifndef LUGGAGE
#define LUGGAGE

#include <string>
#include <unordered_map>

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

    Luggage(std::string &nameValue);
};

#endif