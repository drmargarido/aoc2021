#include <math.h>

typedef struct Vec2 {
  int x;
  int y;
} Vec2;

Vec2 vec2_vsum(Vec2 a, Vec2 b){
  Vec2 result = {a.x+b.x, a.y+b.y};
  return result;
}

Vec2 vec2_vsub(Vec2 a, Vec2 b){
  Vec2 result = {a.x-b.x, a.y-b.y};
  return result;
}

Vec2 vec2_vmul(Vec2 a, Vec2 b){
  Vec2 result = {a.x*b.x, a.y*b.y};
  return result;
}

Vec2 vec2_vdiv(Vec2 a, Vec2 b){
  Vec2 result = {a.x/b.x, a.y/b.y};
  return result;
}

Vec2 vec2_sum(Vec2 a, int b){
  Vec2 result = {a.x+b, a.y+b};
  return result;
}

Vec2 vec2_sub(Vec2 a, int b){
  Vec2 result = {a.x-b, a.y-b};
  return result;
}

Vec2 vec2_mul(Vec2 a, int b){
  Vec2 result = {a.x*b, a.y*b};
  return result;
}

Vec2 vec2_div(Vec2 a, int b){
  Vec2 result = {a.x/b, a.y/b};
  return result;
}

float vec2_mag(Vec2 v){
  return sqrt(v.x * v.x + v.y * v.y);
}

int vec2_dot(Vec2 a, Vec2 b){
  return a.x * b.x + a.y * b.y;
}

/* Angle is the minimum possible angle between the vectors */
float vec2_angle_between(Vec2 a, Vec2 b){
  int dot = vec2_dot(a, b);
  float norm = vec2_mag(a) * vec2_mag(b);
  float angle = radians_to_degrees(acos(dot / norm));
  return angle;
}
