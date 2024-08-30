#pragma once // pragma once is nice but is not (yet) standard. 
//              however its an extension supported by most compilers

#include "PlockY/BlockMatrix.hpp"
#include "PlockY/BlockVector.hpp"
#include "PlockY/Step.hpp"
#include "PlockY/CSVBlockLoaderFactory.hpp"
#include "PlockY/MTXBlockLoaderFactory.hpp"
#include "PlockY/BlockMatrixLoader.hpp"
#include "PlockY/BlockVectorLoader.hpp"
#include "PlockY/Strategy.hpp"
#include "PlockY/Solver.hpp"

typedef PlockY::DenseBlock<double> denseBlockD;
typedef PlockY::SparseBlock<double> sparseBlockD;