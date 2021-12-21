#include "assemble_laplacian.h"
#include <vector>

typedef Eigen::Triplet<double> TRIPLET;
void assemble_laplacian(Eigen::SparseMatrixd &A){
  A.resize(GRIDSIZE, GRIDSIZE);
  std::vector<TRIPLET> triplets;
  // weird looking compared to video due to flattening
  // note that order of input matrix would be something along the lines of
  // (x,y,z-1), (x,y-1,z), (x-1,y,z),(x,y,z),(x+1,y,z),(x,y+1,z),(x,y,z+1)
  // due to flattening from how its stored
  Eigen::VectorXd B(6);
  B << -1, -1, -1, 1, 1, 1;
  Eigen::MatrixXd D(6,7);
  D.row(0) << -1, 0, 0, 1, 0, 0, 0;
  D.row(1) << 0, -1, 0, 1, 0, 0, 0;
  D.row(2) << 0, 0, -1, 1, 0, 0, 0;
  D.row(3) << 0, 0, 0, -1, 1, 0, 0;
  D.row(4) << 0, 0, 0, -1, 0, 1, 0;
  D.row(5) << 0, 0, 0, -1, 0, 0, 1;
  Eigen::VectorXd BD = B.transpose() * D;
  int count = 0;
  for(int k = 1; k < GZ-1; k++){
    for(int j = 1; j < GY-1; j++){
      for(int i = 1; i < GX-1; i++){
        triplets.push_back(TRIPLET(IND(i+1, j, k), count, BD(0)));
        triplets.push_back(TRIPLET(IND(i-1,j,k), count, BD(1)));
        triplets.push_back(TRIPLET(IND(i,j+1,k), count, BD(2)));
        triplets.push_back(TRIPLET(IND(i,j-1,k), count, BD(3)));
        triplets.push_back(TRIPLET(IND(i,j,k+1), count, BD(4)));
        triplets.push_back(TRIPLET(IND(i,j,k-1), count, BD(5)));
        count++;
      }
    }
  }
  A.setFromTriplets(triplets.begin(), triplets.end());
}
