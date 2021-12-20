#include <Eigen/Sparse>
#include "grid.hpp"
#include "vec2grid.hpp"
#include "grid2vec.hpp"
#include "conjugate_gradient.hpp"

void diffuse(GRID &S1, GRID S0, double visc, double dt, Eigen::SparseMatrixd A);
