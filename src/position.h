#ifndef VLEESJONGEN_POSITION_H
#define VLEESJONGEN_POSITION_H

namespace vlees {
class Position
{
private:
        float x;
        float y;

public:
        Position(float x, float y);
        [[nodiscard]] float getX() const;
        [[nodiscard]] float getY() const;
        void setX(float x);
        void setY(float y);
        Position operator+(const Position& rhs) const;
        Position operator-(const Position& rhs) const;
        Position operator*(const float& c) const;
        Position operator+=(const Position& rhs);
        Position operator-=(const Position& rhs);
        Position operator*=(const float& c);
};

} // namespace vlees

#endif // VLEESJONGEN_POSITION_H
