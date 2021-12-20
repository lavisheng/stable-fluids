#include "grid.h"
#include <Eigen/Sparse>
#include "conjugate_gradient.h"
void project(Velocity &v1, Velocity v0, Eigen::SparseMatrixd A);
