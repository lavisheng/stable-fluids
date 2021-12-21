#include <Eigen/Sparse>
#include "grid.h"
#include "conjugate_gradient.h"

/**
 * Calculates diffusion, which is the effect of viscosity on the system
 * In:
 * S0 - initial field
 * visc - viscosity constant
 * dt - delta time
 * A - matrix to use in conjugate gradient
 * Out:
 * S1 - the resulting field
 */
void diffuse(Eigen::VectorXd &S1, Eigen::VectorXd S0, double visc, double dt, Eigen::SparseMatrixd A);
