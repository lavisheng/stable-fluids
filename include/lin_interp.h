#ifndef LIN_INTERP_
#define LIN_INTERP_
#include "grid.h"
#include <Eigen/Dense>

/**
 * Trillinear interpolation based off of the weights found on wikipedia
 * In:
 * x,y,z - x,y,z coordinates of the point
 * F - field to interpolate
 * out: linear interpolated value
 */
double lin_interp(double x, double y, double z, Eigen::VectorXd F);
#endif
