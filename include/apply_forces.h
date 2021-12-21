#include "grid.h"

/**
 * Applies forces to a field.
 * In:
 * F - a field describing the forces
 * dt - delta time
 * Out: 
 * S - the resulting field
 */
void apply_forces(Eigen::VectorXd &S, Eigen::VectorXd F, double dt);
