#include <Eigen/Sparse>
#include "grid.h"
#include "conjugate_gradient.h"

void diffuse(Eigen::VectorXd &S1, Eigen::VectorXd S0, double visc, double dt, Eigen::SparseMatrixd A);
