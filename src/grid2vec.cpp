#include <Eigen/Dense>

void grid2vec(Eigen::VectorXd &vec, GRID g){
  vec.resize(GX*GY*GZ);
  for(int i = 0; i < GX; i++){
    for(int j = 0; j < GY; j++){
      for(int k = 0; k < GZ; k++){
        vec[i * j + GX + k * GY * GX] = g[i][j][k];
      }
    }
  }
}
