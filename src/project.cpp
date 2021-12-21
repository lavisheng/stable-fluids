#include "project.h"

void project(Velocity &v1, Velocity v0,  Eigen::SparseMatrixd A){
  // calculate a div, negate it
  // stores a negated div
  Eigen::VectorXd div((int)GRIDSIZE);
  
  for(int k = 1; k < GZ; k++){
    for(int j = 1; j < GY; j++){
      for(int i = 1; i < GX; i++){
        div(IND(i, j, k)) = -(v0.u1(IND(i+1, j ,k)) - v0.u1(IND(i-1, j ,k)) +
                              v0.u2(IND(i, j+1, k)) - v0.u2(IND(i, j-1, k)) +
                              v0.u3(IND(i, j, k+1)) - v0.u3(IND(i, j, k-1))) / 2.;
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
        v1.u1(IND(i, j, k)) = v0.u1(IND(i, j ,k)) -
          0.5 * (x(IND(i+1, j, k)) - x(IND(i-1, j ,k)));
        v1.u2(IND(i, j, k)) = v1.u2(IND(i, j, k)) -
          0.5 * (x(IND(i, j+1, k)) - x(IND(i, j-1, k)));
        v1.u3(IND(i, j, k)) = v1.u3(IND(i, j ,k)) -
          0.5 * (x(IND(i, j, k+1)) - x(IND(i, j, k-1)));
      }
    }
  }
}
