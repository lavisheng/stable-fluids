#include <Eigen/Dense>

void vec2grid(GRID &g, Eigen::VectorXd vec){
  for(int k = 0; k < GZ; k++){
    for(int j = 0; j < GY; j++){
      for(int i = 0; i < GX; i++){
        g[i][j][k] = vec[i + j * GX + k * GY * GX];
      }
    }
  }
}
