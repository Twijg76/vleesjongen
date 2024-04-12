#include "position.h"

namespace vlees {

Position::Position(float x, float y) : x(x), y(y) {}

float Position::getX() const { return x; }
float Position::getY() const { return y; }

void Position::setX(float xn) { this->x = xn; }
void Position::setY(float yn) { this->y = yn; }

Position Position::operator+(const Position& rhs) const
{
        float newx = x + rhs.getX();
        float newy = y + rhs.getY();
        return {newx, newy};
}

Position Position::operator-(const Position& rhs) const
{
        float newx = x - rhs.getX();
        float newy = y - rhs.getY();
        return {newx, newy};
}

Position Position::operator*(const float& c) const
{
        float newx = x * c;
        float newy = y * c;
        return {newx, newy};
}

Position Position::operator+=(const Position& rhs)
{
        x += rhs.getX();
        y += rhs.getY();
        return *this;
}

Position Position::operator-=(const Position& rhs)
{
        x -= rhs.getX();
        y -= rhs.getY();
        return *this;
}

Position Position::operator*=(const float& c)
{
        x *= c;
        y *= c;
        return *this;
}
} // namespace vlees
