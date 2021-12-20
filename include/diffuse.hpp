#include <Eigen/Sparse>
#include "grid.hpp"
#include "conjugate_gradient.hpp"

void diffuse(Eigen::VectorXd &S1, Eigen::VectorXd S0, double visc, double dt, Eigen::SparseMatrixd A);
