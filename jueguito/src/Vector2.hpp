#include "raylib.h"
#include "raymath.h"
#include <cmath>

#ifndef VECTOR_OVERLOADS
#define VECTOR_OVERLOADS

float dot(const Vector2& v1, const Vector2& v2) {
  return v1.x * v2.x + v1.y * v2.y;
}

float cross(const Vector2& v1, const Vector2& v2) {
  return v1.x * v2.y - v1.y * v2.x;
}

float mag(const Vector2& v) {
  return std::sqrt(v.x * v.x + v.y * v.y);
}

float magSq(const Vector2& v) {
  return v.x * v.x + v.y * v.y;
}

float dist(const Vector2& v1, const Vector2& v2) {
  return mag(v1 - v2);
}

Vector2 normalized(const Vector2& v) {
  float magnitude = mag(v);
  if (magnitude == 0) {
    return Vector2{0, 0};
  }
  return v / magnitude;
}

const Vector2& normalize(Vector2& v) {
  float magnitude = mag(v);
  if (magnitude == 0) {
    return v;
  }
  return v /= magnitude;
}

Vector2 limited(const Vector2& v, float max_mag) {
  float max_factor = max_mag / mag(v);
  if (max_factor > 1) {
    return v;
  }
  return v * max_factor;
}

const Vector2& limit(Vector2& v, float max_mag) {
  float max_factor = max_mag / mag(v);
  if (max_factor > 1) {
    return v;
  }
  return v *= max_factor;
}

float heading(const Vector2& v) {
  return atan2(v.y, v.x);
}

Vector2 rotated(const Vector2& v, float angle) {
  float cosine = cos(angle);
  float sine = sin(angle);
  return Vector2{v.x * cosine - v.y * sine, v.x * sine + v.y * cosine};
}

Vector2& rotate(Vector2& v, float angle) {
  float cosine = cos(angle);
  float sine = sin(angle);
  return v = Vector2{v.x * cosine - v.y * sine, v.x * sine + v.y * cosine};
}

Vector2 fromAngle(float angle) {
  return Vector2{cos(angle), sin(angle)};
}

Vector2 lerp(const Vector2& v1, const Vector2& v2, float t) {
  t = t > 1 ? 1 : t;
  t = t < 0 ? 0 : t;

  return v1 * (1 - t) + v2 * t;
}

float angleBetween(const Vector2& v1, const Vector2& v2) {
  float cosine = dot(v1, v2) / mag(v1) / mag(v2);
  return acos(cosine);
}

bool operator==(const Color& c1, const Color& c2) {
  return (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a);
}

#endif
