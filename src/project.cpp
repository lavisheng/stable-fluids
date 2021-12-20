#include "project.hpp"

void project(Velocity &v1, Velocity v0,  Eigen::SparseMatrixXd A){
  // calculate a div, negate it
  GRID neg_div;
  // stores a negated div
  Eigen::VectorXd div(GX * GY * GZ);
  for(int k = 1; k < GZ; k++){
    for(int j = 1; j < GY; j++){
      for(int i = 1; i < GX; i++){
        div(i + j * GX + k * GX * GY) = -(v0.u1[i+1][j][k] - v0.u1[i-1][j][k] +
          v0.u2[i][j+1][k] - v0.u2[i][j-1][k] +
          v0.u3[i][j][k+1] - v0.u3[i][j][k-1]) / 2.; 
      }
    }
  }
  for(int i = 1; i < GX; i++){
    for(int j = 1; j < GY; j++){
      for(int k = 1; k < GZ; k++){
        neg_div0[i][j][k] = -(v0.u1[i+1][j][k] - v0.u1[i-1][j][k] +
          v0.u2[i][j+1][k] - v0.u2[i][j-1][k] +
          v0.u3[i][j][k+1] - v0.u3[i][j][k-1]) / 2.; 
      }
    }
  }
  //gauss seidl code
  /*GRID S1;
  for(int iter = 0; iter < 10; iter++){
   for(int i = 1; i < GX; i++){
    for(int j = 1; j < GY; j++){
      for(int k = 1; k < GZ; k++){
        S1[i][j][k] = (neg_div[i][j][k] + S1[i-1][j][k] + S1[i+1][j][k] +
                       S1[i][j-1][k] + S1[i][j+1][k] +
                       S1[i][j][k-1] + S1[i][j][k+1]) / 8.;
      }
    }
   }
   }*/
  Eigen::VectorXd x;
  conjugate_gradient(x, A, div);
  // solved a relaxation for q
  // now subtract the difference
  for(int i = 1; i < GX; i++){
    for(int j = 1; j < GY; j++){
      for(int k = 1; k < GZ; k++){
        v1.u1[i][j][k] = v0.u1[i][j][k] - 0.5 * (x(ind(i+1, j, k)) - x(ind(i-1, j, k))); 
        v1.u2[i][j][k] = v0.u2[i][j][k] - 0.5 * (x(ind(i, j+1, k)) - x(ind(i, j-1, k)));
        v1.u1[i][j][k] = v0.u3[i][j][k] - 0.5 * (x(ind(i, j, k+1)) - x(ind(i, j, k-1)));
      }
    }
  }
}
