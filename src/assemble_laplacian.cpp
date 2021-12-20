#include "assemble_laplacian.h"
#include <vector>

typedef Eigen::Triplet<double> TRIPLET;
void assemble_laplacian(Eigen::SparseMatrixd &A){
  A.resize(GX*GY*GZ, GX*GY*GZ);
  std::vector<TRIPLET> triplets;
  Eigen::VectorXd BD;
  int count = 0;
  for(int k = 1; k < GZ; k++){
    for(int j = 1; j < GY; j++){
      for(int i = 1; i < GX; i++){
        triplets.push_back(TRIPLET(IND(i+1, j, k), count, BD(0)));
        triplets.push_back(TRIPLET(IND(i, j, k), count, BD(1)));
        triplets.push_back(TRIPLET(IND(i-1,j,k), count, BD(2)));
        triplets.push_back(TRIPLET(IND(i,j+1,k), count, BD(3)));
        triplets.push_back(TRIPLET(IND(i,j-1,k), count, BD(4)));
        triplets.push_back(TRIPLET(IND(i,j,k+1), count, BD(5)));
        triplets.push_back(TRIPLET(IND(i,j,k-1), count, BD(6)));
      }
    }
  }
  A.setFromTriplets(triplets.begin(), triplets.end());
}
