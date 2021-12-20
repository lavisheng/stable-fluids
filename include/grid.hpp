#include <array>
#include <EigenTypes.h>
#include <Eigen/Dense>
#define GX 1
#define GY 1
#define GZ 1
#define dx 1
#define dy 1
#define dz 1
#define GRID std::array<std::array<std::array<double, GZ>, GY>, GX>
typedef struct Velocity_{
  // 3 grids for each component
  // purposefully avoiding dealing with tensors
  GRID u1; // x component
  GRID u2; // y component
  GRID u3; // z component
  void operator()(Eigen::Vector3d out, Eigen::Vector3i p){
    out << u1[p(0)][p(1)][p(2)], u2[p(0)][p(1)][p(2)], u3[p(0)][p(1)][p(2)];
  }
} Velocity;

typedef GRID Pressure;