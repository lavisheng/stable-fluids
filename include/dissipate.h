#include "grid.h"

/**
 * Calculates disspation, which is the elementwise division of 1 * dt * a
 * In:
 * S0 - the initial field
 * a - the constant in 1 * dt * a
 * dt - time delta
 * Out:
 * S1 - resulting field
 */
void dissipate(Eigen::VectorXd &S1, Eigen::VectorXd S0, double a, double dt);
