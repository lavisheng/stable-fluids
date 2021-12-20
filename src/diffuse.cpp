#include "grid.hpp"
#include <Eigen/Sparse>
#include <vector>
#define TRIPLET
void diffuse(GRID &S1, GRID S0, double visc, double dt){
  // setup identity (is this really the only way)
  Eigen::SparseMatrixXd I;
  I.resize(GX*GY*GZ, GX*GY*GZ);
  std::vector<TRIPLET> triplets;
  for(int i = 0; i < GX* GY*GZ; i++){
    triplets.push_back(i, i, 1);
  }
  I.setFromTriplets(triplets);
  // Get the laplacian
  Eigen::SparseMatrixXd A;
  assemble_laplacian(A);
  // setup variables to solve (I - visc * dt * A) w3 = w2
  Eigen::VectorXd x;
  Eigen::VectorXd b;
  grid2vec(b, S0);
  conjugate_gradient(x, (I - visc * dt * A), b);
  vec2grid(S1, x);
}
