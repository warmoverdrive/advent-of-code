#ifndef _BOAT_H
#define _BOAT_H

#include <unordered_map>
#include <stdlib.h>
#include <queue>

using Coords = std::pair<int, int>; // X (-w->e+), Y(-s->n+)

struct Boat
{
    Coords local;
    Coords waypoint;
    Boat(Coords _local = {0, 0}, Coords _waypoint = {10, 1});
    void MoveBoat(int forwardMultiplier);
    void RotateWaypoint(int degrees);
    void MoveWaypoint(char direction, int distance);
};

Boat::Boat(Coords _local, Coords _waypoint)
    : local{_local}, waypoint{_waypoint} {}

void Boat::MoveBoat(int forwardMultiplier)
{
    local.first += forwardMultiplier * waypoint.first;
    local.second += forwardMultiplier * waypoint.second;
}

/*  SOMETHING IS WRONG HERE I THINK- 
    LEFT TURN IS THE ONLY FUNCTION THAT 
    ISN"T USED IN TEST CASE        
*/
void Boat::RotateWaypoint(int degrees)
{
    Coords temp{};
    if (degrees > 0) // turn right
    {
        for (int i{}; i <= degrees; i += 90)
        {
            temp.first = 0;
            temp.second = 0;
            if (waypoint.second > 0)
                temp.first = waypoint.second;
            else if (waypoint.second < 0)
                temp.first = -waypoint.second;

            if (waypoint.first < 0)
                temp.second = abs(waypoint.first);
            else if (waypoint.first > 0)
                temp.second = -waypoint.first;

            waypoint = temp;
        }
    }
    else // turn left
    {
        for (int i{}; i <= abs(degrees); i += 90)
        {
            temp.first = 0;
            temp.second = 0;
            if (waypoint.second > 0)
                temp.first = -waypoint.second;
            else if (waypoint.second < 0)
                temp.first = abs(waypoint.second);

            if (waypoint.first < 0)
                temp.second = -waypoint.first;
            else if (waypoint.first > 0)
                temp.second = waypoint.first;

            waypoint = temp;
        }
    }
}

void Boat::MoveWaypoint(char direction, int distance)
{
    if (direction == 'N')
        waypoint.second += distance;
    else if (direction == 'E')
        waypoint.first += distance;
    else if (direction == 'S')
        waypoint.second -= distance;
    else if (direction == 'W')
        waypoint.first -= distance;
}

#endif // _BOAT_H