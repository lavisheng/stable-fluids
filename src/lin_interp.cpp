#include "lin_interp.h"
// thank you to wikipedia for the method for trilinear interpolation
double lin_interp(double x, double y, double z, Eigen::VectorXd F){
  int xlower = (int)(x);
  int ylower = (int)(y);
  int zlower = (int)(z);

  double xdelta = x - (double)xlower;
  double ydelta = y - (double)ylower;
  double zdelta = z - (double)zlower;

  // get values at each corner for trilinear interpolation
  double c000 = F(IND(xlower, ylower, zlower));
  double c100 = F(IND(xlower + 1, ylower, zlower));
  double c010 = F(IND(xlower, ylower+1, zlower));
  double c001 = F(IND(xlower, ylower, zlower+1));
  double c110 = F(IND(xlower+1, ylower+1, zlower));
  double c101 = F(IND(xlower+1, ylower, zlower+1));
  double c011 = F(IND(xlower, ylower+1, zlower+1));
  double c111 = F(IND(xlower+1, ylower+1, zlower+1));

  double c00 = c00 * (1 - xdelta) + c100 * xdelta;
  double c01 = c001 * (1- xdelta) + c101 * xdelta;
  double c10 = c010 * (1 - xdelta) + c110 * xdelta;
  double c11 = c011 * (1-xdelta) + c111 * xdelta;

  double c0 = c00 * (1-ydelta) + c10 * ydelta;
  double c1 = c01 * (1 - ydelta) + c11 * ydelta;
  return c0 * (1 - zdelta) + c1 * zdelta;
}
