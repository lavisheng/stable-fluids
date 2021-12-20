#include "conjugate_gradient.h"

// implementation of pseudocode on wikipedia
void conjugate_gradient(Eigen::VectorXd &x, Eigen::SparseMatrixd A, Eigen::VectorXd b){
  x = Eigen::VectorXd::Zero(GX * GY * GZ);
  Eigen::VectorXd r = b; 
  Eigen::VectorXd p(r.size());
  p << r; 
  Eigen::VectorXd rsold = r.transpose() * r;
  for(int iter = 0; iter < 10; iter++){
    double alpha = (r.transpose() * r)(0) / (p.transpose() * A * p)(0);
    x += alpha * p;
    Eigen::VectorXd rprime = r -  alpha * A * p;
    if(rprime.norm() < 1e-10) break;
    double beta = (rprime.transpose() * rprime)(0)/ (r.transpose() * r)(0);
    p = rprime * beta * p;
    r = rprime;
  }
}
