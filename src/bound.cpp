#include "bound.h"

void bound(Eigen::VectorXd &field, Dir dir){
  // we will negate the velocity going in to get 0 velocity at the boundary
  // first some universal corner cases
  field(IND(0, 0, 0)) = 0;
  field(IND(GX-1, GY-1,GZ-1)) = 0;
  field(IND(0, GY-1, GZ-1)) = 0;
  field(IND(0, GY-1, 0)) = 0;
  field(IND(GX-1, GY-1, 0)) = 0;
  field(IND(0, 0, GZ-1)) = 0;
  switch (dir){
  case xDim:
    for(int k = 1; k < GZ - 1 ; k++){
      for(int j = 1; j < GY - 1; j++){
        field(IND(0, j, k)) = 0;
        field(IND(GX-1,j,k)) = 0;
      }
    }
    
    break;
  case yDim:
    for(int k = 1; k < GZ -1; k++){
      for(int i = 1; i < GX - 1; i++){
        field(IND(i, 0, k)) = 0;
        field(IND(i, GY - 1, k)) = 0;
      }
    }
    break;
  case zDim:
    for(int j = 1; j < GY - 1; j++){
      for(int i = 1; i < GX - 1; i++){
        field(IND(i, j, 0)) = 0;
        field(IND(i, j, GZ - 1)) = 0;
      }
    }
  }
}
