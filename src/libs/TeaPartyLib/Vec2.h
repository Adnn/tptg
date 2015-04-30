//
//  Vec2.h
//
//  Created by Adrien David.
//
//

#ifndef BenchingBall_Vec2_h
#define BenchingBall_Vec2_h

#include <cmath>
#include <Polycode.h>

namespace TeaParty {

struct Vec2
{
    Vec2(double x, double y):
        x(x),
        y(y)
    {}

    Vec2(Polycode::Vector2 v):
        x(v.x),
        y(v.x)
    {}

    Vec2 operator+(const Vec2 &aRhs) const
    {
        return {x+aRhs.x, y+aRhs.y};
    }

    Vec2 operator-(const Vec2 &aRhs) const
    {
        return *this + (aRhs * -1);
    }

    Vec2 &operator-()
    {
        x = -x;
        y = -y;
        return *this;
    }

    Vec2 & operator+=(const Vec2 &aRhs)
    {
        x += aRhs.x;
        y += aRhs.y;
        return *this;
    }

    Vec2 & operator-=(const Vec2 &aRhs)
    {
        x -= aRhs.x;
        y -= aRhs.y;
        return *this;
    }

    bool operator!=(const Vec2 &aRhs)
    {
        return x != aRhs.x || y != aRhs.y;
    }

    bool operator==(const Vec2 &aRhs)
    {
        return x == aRhs.x && y == aRhs.y;
    }

    Vec2 operator*(double k) const
    {
        return {x*k, y*k};
    }

	Vec2 operator/(double k) const
	{
		return{ x/k, y/k };
	}

    double dot(const Vec2 &aRhs) const
    {
        return x*aRhs.x + y*aRhs.y;
    }

    Vec2 &normalize()
    {
        double len = length();
        x /= len;
        y /= len;
        return *this;
    }

    double length() const
    {
        return std::sqrt(x*x + y*y);
    }

    double x;
    double y;
};

inline double distance(const Vec2 &aLhs, const Vec2 &aRhs)
{
    return (aLhs-aRhs).length();
}


} // namespace TeaParty

#endif
