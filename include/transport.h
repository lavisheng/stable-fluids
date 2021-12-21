#include "grid.h"
#include "lin_interp.h"
#include <algorithm>
#include <Eigen/Dense>

/**
 * Calculates advection. For each point in the grid backtracks to -dt to get that velocity
 * In:
 * S0 - the input field
 * v - velocity grids to use for backtracking
 * dt - time delta to calculate backtrack location
 * Out:
 * S1 - the output field 
 */
void transport(Eigen::VectorXd &S1, Eigen::VectorXd S0, Velocity v, double dt);
