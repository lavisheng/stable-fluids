#include "transport.h"

// rk2 to backtrack to the past point
// NOTE: yes, this is hillariously wrong. The correct rk2 implementation messes with conjugate_gradient setup and explodes into NaNs
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
void transport(Eigen::VectorXd &S1, Eigen::VectorXd S0, Velocity v, double dt){
  for(int k = 0 ; k < GZ; k++){
    for(int j = 0; j < GY; j++){
      for(int i = 0; i < GX; i++){
        Eigen::Vector3d res;
        Eigen::Vector3i p;
        p << i, j, k;
        // back track
        rk2(res, v, p, dt);
        // rk2 gets us res, which stores the velocity at back tracked location
        // need to clip the vector to ensure bounds
        res[0] = std::max(1., std::min((double)GX-2, res[0]));
        res[1] = std::max(1., std::min((double)GY -2, res[1]));
        res[2] = std::max(1., std::min((double)GZ -2, res[2]));
        // linearly interpolate it now
        S1(IND(i, j, k)) = lin_interp(res(0), res(1), res(2), S0);
      }
    }
  }
}
