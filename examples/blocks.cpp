#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Sparse>

#include "PlockY/DenseBlock.hpp"
#include "PlockY/SparseBlock.hpp"
#include "PlockY/VecBlock.hpp"

int main() {

    // Example usage of DenseBlock
    Eigen::MatrixXd dense(2, 2);
    dense << 10, 20,
            30, 40;
    PlockY::DenseBlock<double> denseBlock(2, 2);
    denseBlock.setMatrix(dense);

    denseBlock.print();


    // Example usage of SparseBlock
    Eigen::SparseMatrix<double> sparse(4, 4);
    sparse.insert(2, 2) = 30;
    sparse.insert(3, 3) = 40;
    PlockY::SparseBlock<double> sparseBlock(4, 4);
    sparseBlock.setMatrix(sparse);


    // Example usage of VecBlock
    Eigen::VectorXd vec(6);
    vec << 50, 60, 0,0,0,2;
    PlockY::VecBlock<double> vecBlock(6);
    vecBlock.setMatrix(vec);

    vecBlock.print();
    
    return 0;
}
