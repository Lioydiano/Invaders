#include "coordinate.h"

Coordinate& Coordinate::operator=(const Coordinate& other) { //overloading dell'operatore =
    x = other.x;
    y = other.y;
    return *this;
}
bool Coordinate::operator==(const Coordinate& other) const //overloading dell'operatore ==
{ 
    return x == other.x && y == other.y;
}
bool Coordinate::operator!=(const Coordinate& other) const //overloading dell'operatore !=
{
    return !(*this == other);
}
Coordinate Coordinate::operator+(const Coordinate& other) const //overloading dell'operatore +
{ 
    return Coordinate(y + other.y, x + other.x);
}
Coordinate Coordinate::operator-(const Coordinate& other) const //overloading dell'operatore -
{ 
    return Coordinate(y - other.y, x - other.x);
}