#include "grid.h"
#include <Eigen/Sparse>

/**
 * Assembles a laplacian matrix
 * out:
 * A - the laplacian, ∇²
 */
void assemble_laplacian(Eigen::SparseMatrixd &A);
