#include "grid.hpp"
#include <Eigen/Sparse>
#include "ind.hpp"

// admittedly i do not actually know if this is the laplacian
// it might be the diffusion op instead lol
void assemble_laplacian(Eigen::SparseMatrixd &A);
