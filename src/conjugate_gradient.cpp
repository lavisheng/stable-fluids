#include <Eigen/Sparse>

// implementation of pseudocode on wikipedia
void conjugate_gradient(Eigen::VectorXd &x, Eigen::SparseMatrixXd A, Eigen::VectorXd b){
  x = Eigen::VectorXd(GX * GY *GZ).zero();
  Eigen::VectorXd r = b; 
  Eigen::VectorXd p = r; 
  Eigen::VectorXd rsold = r.transpose() * r;
  for(int iter = 0; iter < 10; iter++){
    double alpha = (r.transpose() * r) / (p.transpose() * A * p);
    x += alpha * p;
    Eigen::Vector rprime -= alpha * A * p;
    if(rprime < 1e-10) break;
    double beta = (rprime.transpose() * rprime)/ (r.transpose() * r);
    p = rprime * beta * p;
    r = rprime;
  }
}
