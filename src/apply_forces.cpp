#include "grid.hpp"

void apply_forces(Velocity &v, double dt){
  // gravity is only force, so just apply gravity to each coordinate in the y component
  // of the grid
  for(int x = 0; x < GX; x++){
    for(int y = 0; y < GY; y++){
      for(int z = 0; z < GZ; z++){
        v.u2[x][y][z] += 9.81 * dt;
      }
    }
  }
}
