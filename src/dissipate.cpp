#include "grid.hpp"
// a is dissipation rate
void dissipate(GRID &S1, GRID S0, double a, double dt ){
  for(int x = 0; x < GX; x++){
    for(int y = 0; y < GY; y++){
      for(int z = 0; z < GZ; z++){
        S1[x][y][z] = S0[x][y][z] / (1 + dt * a);
      }
    }
  }
}
