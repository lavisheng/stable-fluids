#include "bound.h"

void bound(Eigen::VectorXd &field, Dir dir){
  // we will negate the velocity going in to get 0 velocity at the boundary
  // first some universal corner cases
  field(IND(0, 0, 0)) = -field(IND(1,1,1));
  field(IND(GX-1, GY-1,GZ-1)) = -field(IND(GX-2, GX-2, GX-2));
  field(IND(0, GY-1, GZ-1)) = -field(IND(1, GY-2, GZ-2));
  field(IND(0, GY-1, 0)) = -field(IND(1, GY-2, 1));
  field(IND(GX-1, GY-1, 0)) = -field(IND(GX-2, GY-2, 1));
  field(IND(0, 0, GZ-1)) = -field(IND(1, 1, GZ-2));
  switch (dir){
  case xDim:
    for(int k = 1; k < GZ - 1 ; k++){
      for(int j = 1; j < GY - 1; j++){
        field(IND(0, j, k)) = -field(IND(1, j, k));
        field(IND(GX-1,j,k)) = -field(IND(GX-2, j, k));
      }
    }
    
    break;
  case yDim:
    for(int k = 1; k < GZ -1; k++){
      for(int i = 1; i < GX - 1; i++){
        field(IND(i, 0, k)) = -field(IND(i, 1, k));
        field(IND(i, GY - 1, k)) = -field(IND(i, GY - 2, k));
      }
    }
    break;
  case zDim:
    for(int j = 1; j < GY - 1; j++){
      for(int i = 1; i < GX - 1; i++){
        field(IND(i, j, 0)) = -field(IND(i, j, 1));
        field(IND(i, j, GZ - 1)) = -field(IND(i, j, GZ-2));
      }
    }
  }
}
