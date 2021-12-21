#include "project.h"

void project(Velocity &v1, Velocity v0,  Eigen::SparseMatrixd A){
  // calculate a div, negate it
  // stores a negated div
  Eigen::VectorXd div((int)GRIDSIZE);
  for(int k = 1; k < GZ-1; k++){
    for(int j = 1; j < GY-1; j++){
      for(int i = 1; i < GX-1; i++){
        div(IND(i, j, k)) = -(v0.u1(IND(i+1, j ,k)) - v0.u1(IND(i-1, j ,k)) +
                              v0.u2(IND(i, j+1, k)) - v0.u2(IND(i, j-1, k)) +
                              v0.u3(IND(i, j, k+1)) - v0.u3(IND(i, j, k-1))) / 2.;
      }
    }
  }
  Eigen::VectorXd x;
  conjugate_gradient(x, A, div);
  // now subtract the difference
  for(int i = 1; i < GX-1; i++){
    for(int j = 1; j < GY-1; j++){
      for(int k = 1; k < GZ-1; k++){
        v1.u1(IND(i, j, k)) = v0.u1(IND(i, j ,k)) -
          0.5 * (x(IND(i+1, j, k)) - x(IND(i-1, j ,k)));
        v1.u2(IND(i, j, k)) = v1.u2(IND(i, j, k)) -
          0.5 * (x(IND(i, j+1, k)) - x(IND(i, j-1, k)));
        v1.u3(IND(i, j, k)) = v1.u3(IND(i, j ,k)) -
          0.5 * (x(IND(i, j, k+1)) - x(IND(i, j, k-1)));
      }
    }
  }
  bound(v1.u1, xDim);
  bound(v1.u2, yDim);
  bound(v1.u3, zDim);
}
