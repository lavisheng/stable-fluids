#include "dissipate.h"
// a is dissipation rate
void dissipate(Eigen::VectorXd &S1, Eigen::VectorXd S0, double a, double dt ){
  for(int k = 0; k < GZ; k++){
    for(int j = 0; j < GY; j++){
      for(int i = 0; i < GX; i++){
        S1(IND(i, j, k)) = S0(IND(i,j,k)) / (1. + dt * a);
      }
    }
  }
}
