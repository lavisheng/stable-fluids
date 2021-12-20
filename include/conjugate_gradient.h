#include "grid.h"
#include <Eigen/Sparse>
#include <Eigen/Dense>

void conjugate_gradient(Eigen::VectorXd &x, Eigen::SparseMatrixd A, Eigen::VectorXd b);
