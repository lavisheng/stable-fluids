#include "grid.h"
#include <Eigen/Dense>
#include <EigenTypes.h>
enum Dir { xDim, yDim, zDim};

/**
 * Bounds a field
 * In:
 * field - the field to bound
 * dir - the dimension to bound in
 * Out:
 * field - the resulting field
 */
void bound(Eigen::VectorXd &field, Dir dir);
