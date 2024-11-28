/*
  2차원 벡터를 정의하였습니다.

  연산자 오버로딩도 일부 정의하였습니다.

  스칼라 곱, 두 벡터간 거리를 구하는 함수도 정의하였습니다.
*/

#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>  // sqrtf

// Vector2 component
class Vector2 
{
public:
  float x = 0.0f;
  float y = 0.0f;
  Vector2() { }
  Vector2(float x, float y) : x(x), y(y) { }
  Vector2(const Vector2& vector) : x(vector.x), y(vector.y) { }

  // Vector operator +,-,*,/
  Vector2 operator+(const Vector2& rhs) const 
  {
    return Vector2(x+rhs.x, y+rhs.y);
  }
  Vector2 operator-(const Vector2& rhs) const 
  {
    return Vector2(x-rhs.x, y-rhs.y);
  }
  Vector2 operator*(const Vector2& rhs) const 
  {
    return Vector2(x*rhs.x, y*rhs.y);
  }
  Vector2 operator/(const Vector2& rhs) const 
  {
    return Vector2(x/rhs.x, y/rhs.y);
  }
  
  // Vector operator +=, -=, *=, /=
  // operator += 는 객체 내부를 변경하기 때문에 const 선언이 불가능합니다.
  Vector2& operator+=(const Vector2& rhs) 
  {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }
  Vector2& operator-=(const Vector2& rhs) 
  {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }
  Vector2& operator*=(const Vector2& rhs) 
  {
    x *= rhs.x;
    y *= rhs.y;
    return *this;
  }
  Vector2& operator/=(const Vector2& rhs) 
  {
    x /= rhs.x;
    y /= rhs.y;
    return *this;
  }

  // ==, !=
  bool operator==(const Vector2& rhs) const 
  {
    if (x == rhs.x && y == rhs.y) return true;
    return false;
  }

  bool operator!=(const Vector2& rhs) const 
  {
    if (x != rhs.x && y != rhs.y) return true;
    return false;
  }

  // Vector * scalar
  Vector2& scale(float scale) 
  {
    x *= scale;
    y *= scale;
    return *this;
  }
  Vector2 operator*(float& scale) const
  {
    return Vector2{x*scale, y*scale};
  }

  // Two vector's between distance
  float distance(const Vector2& vector) const 
  {
    return sqrtf( ((vector.x-x)*(vector.x-x)) + ((vector.y-y)*(vector.y-y)) );
  }

  // Vector's length
  float length() const 
  {
    return sqrtf( (x*x) + (y*y) );
  }

  Vector2& normalize()
  {
    float len = length();
    if (len > 0.0f)
    {
      x /= len;
      y /= len;
    }
    return *this;
  }
};


#endif
