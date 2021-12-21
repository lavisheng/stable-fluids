#include "grid.h"
#include <Eigen/Sparse>
#include <Eigen/Dense>

/**
 * Solves an equation Ax = b 
 * In:
 * A - a matrix in Ax = b
 * b - a vector in Ax = b
 * Out:
 * x - the solution 
 */
void conjugate_gradient(Eigen::VectorXd &x, Eigen::SparseMatrixd A, Eigen::VectorXd b);
