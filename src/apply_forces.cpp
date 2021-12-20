#include "grid.hpp"
#include "apply_forces.hpp"
#include <Eigen/Dense>

void apply_forces(Eigen::VectorXd &S, Eigen::VectorXd F, double dt){
  for(int k = 0; k < GZ; k++){
    for(int j = 0; j < GY; j++){
      for(int i = 0; i < GX; i++){
        S(IND(i, j, k)) += F(IND(i, j, k)) * dt;
      }
    }
  }
}

