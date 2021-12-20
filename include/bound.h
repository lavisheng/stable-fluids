#include "grid.h"
#include <Eigen/Dense>
#include <EigenTypes.h>
enum Dir { xDim, yDim, zDim};

void bound(Eigen::VectorXd field, Dir dir);
