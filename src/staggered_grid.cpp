#include <iostream>
#include <array>
#define GX 1
#define GY 1
#define GZ 1
#define GRID std::array<std::array<std::array<double, GZ>, GY>, GX>
typedef struct Velocity_{
  GRID u1;
  GRID u2;
} Velocity;
// sets up the staggered grid
void staggered_grid(double (&u1)[GX][GY][GZ], double (&u2)[GX][GY][GZ], double (&p)[GX][GY][GZ]){
}