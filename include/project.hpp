#include "grid.hpp"
#include <Eigen/Sparse>
#include "ind.hpp"
#include "conjugate_gradient.hpp"
void project(Velocity &v1, Velocity v0, Eigen::SparseMatrixd A);
