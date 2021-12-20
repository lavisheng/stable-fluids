#include "transport.hpp"
// takes in the center
double lin_interp(double x, double y, double z, GRID F){
  int xlower = (int)(x);
  int ylower = (int)(y);
  int zlower = (int)(z);

  double xdelta = (x) - (double)xlower;
  double ydelta = (y) - (double)ylower;
  double zdelta = (z) - (double)zlower;

  // get values at each corner for trilinear interpolation
  double c000 = F[xlower][ylower][zlower];
  double c100 = F[xlower + 1][ylower][zlower];
  double c010 = F[xlower][ylower+1][zlower];
  double c001 = F[xlower][ylower][zlower+1];
  double c110 = F[xlower+1][ylower+1][zlower];
  double c101 = F[xlower+1][ylower][zlower+1];
  double c011 = F[xlower][ylower+1][zlower+1];
  double c111 = F[xlower+1][ylower+1][zlower+1];

  double c00 = c00 * (1 - xdelta) + c100 * xdelta;
  double c01 = c001 * (1- xdelta) + c101 * xdelta;
  double c10 = c010 * (1 - xdelta) + c110 * xdelta;
  double c11 = c011 * (1-xdelta) + c111 * xdelta;

  double c0 = c00 * (1-ydelta) + c10 * ydelta;
  double c1 = c01 * (1 - ydelta) + c11 * ydelta;
  return c0 * (1 - zdelta) + c1 * zdelta;
}
// rk2 to backtrack to the past point
void rk2(Eigen::Vector3d &resultant, Velocity v, Eigen::Vector3i point, double dt){
  Eigen::Vector3d k1, k2;
  v(k1, point);
  k1 = (point.cast<double>()+0.5 * Eigen::Vector3d::Ones()) - dt / 2. * k1;
  // cast to int, round down to get the right grid
  Eigen::Vector3i point2 = k1.cast<int>();
  v(k2, point2);
  // reverse direction since we are going backwards
  k2 *= -1;
  resultant = (point.cast<double>() + 0.5 * Eigen::Vector3d::Ones()) + 0.5 * dt* (k1 + k2);
}
void transport(GRID &S1, GRID S0, Velocity v, double dt){
  for(int x = 0 ; x < GX; x++){
    for(int y = 0; y < GY; y++){
      for(int z = 0; z < GZ; z++){
        Eigen::Vector3d res;
        Eigen::Vector3i p;
        p << x, y, z;
        // back track
        rk2(res, v, p, dt);
        // rk2 gets us res, which stores the velocity at back tracked location
        // need to clip the vector 
        double resx, resy, resz;
        resx = res[0];
        res[0] = std::max(1., std::min((double)GX, resx));
        res[1] = std::max(1., std::min((double)GY, resy));
        res[2] = std::max(1., std::min((double)GZ, resz));
        // linearly interpolate it now
        S1[x][y][z] = lin_interp(res(0), res(1), res(2), S0);
      }
    }
  }
}
