#include "element.h"

Coordinate Element::getPosition() const { 
    return position;
}
void Element::setPosition(const Coordinate& position_) {
    position = position_;
}
string Element::getType() const {
    return type;
}
char Element::getSymbol() const {
    return symbol;
}