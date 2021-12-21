#include "grid.h"
#include "bound.h"
#include <Eigen/Sparse>
#include "conjugate_gradient.h"
/**
 * Calculates the projection onto a div free solution
 * In:
 * v0 - initial grids representing velocity 
 * A - matrix to use in conjugate gradient
 * Out:
 * v1 - the solution
 */
void project(Velocity &v1, Velocity v0, Eigen::SparseMatrixd A);
