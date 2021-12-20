#include "diffuse.h"
#include <vector>
typedef Eigen::Triplet<double> TRIPLET;
void diffuse(Eigen::VectorXd &S1, Eigen::VectorXd S0, double visc, double dt, Eigen::SparseMatrixd A){
  // setup identity (is this really the only way)
  Eigen::SparseMatrixd I;
  I.resize(GX*GY*GZ, GX*GY*GZ);
  std::vector<TRIPLET> triplets;
  for(int i = 0; i < GX* GY*GZ; i++){
    triplets.push_back(TRIPLET(i, i, 1));
  }
  I.setFromTriplets(triplets.begin(), triplets.end());
  // setup variables to solve (I - visc * dt * A) w3 = w2
  //Eigen::VectorXd x;
  //Eigen::VectorXd b;
  //grid2vec(b, S0);
  Eigen::SparseMatrixd mat = I - visc * dt * A;
  conjugate_gradient(S1, mat, S0);

  //vec2grid(S1, x);
}
