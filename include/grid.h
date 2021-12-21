#ifndef GRID_
#define GRID_
#include <EigenTypes.h>
#include <Eigen/Dense>
#define GX 20.
#define GY 20.
#define GZ 20.
#define GRIDSIZE ((int)(GX * GY * GZ))
#define dx 1
#define dy 1
#define dz 1
inline int IND(int i,int j, int k) {return i + j * GX + k * GX * GY; }
typedef struct Velocity_{
  // 3 grids for each component
  // purposefully avoiding dealing with tensors
  Eigen::VectorXd u1;
  Eigen::VectorXd u2;
  Eigen::VectorXd u3;
  void operator()(Eigen::Vector3d out, Eigen::Vector3i p){
    int index = IND(p(0), p(1), p(2));
    out << u1(index), u2(index), u3(index);
  }
} Velocity;




#endif
