#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Sparse>

#include "PlockY/DenseBlock.hpp"
#include "PlockY/SparseBlock.hpp"
#include "PlockY/VecBlock.hpp"
#include "PlockY/TransposeOf.hpp" // Add this line

int main() {

    // Example usage of DenseBlock
    Eigen::MatrixXd dense(2, 2);
    dense << 10, 20,
            30, 40;
    PlockY::DenseBlock<double> denseBlock(2, 2);
    denseBlock.setMatrix(dense);
    std::cout<<"Dense block:"<<std::endl;
    std::cout<<denseBlock.getMatrix()<<std::endl;

    auto denseBlockPtr = std::make_shared<PlockY::DenseBlock<double>>(denseBlock);
    // Example usage of TransposeOf
    auto transposedBlock = std::make_shared<PlockY::TransposeOf<PlockY::DenseBlock<double>>>(denseBlockPtr);
    std::cout << "Transposed block:" << std::endl;
    std::cout<< transposedBlock->getMatrix()<<std::endl;
    transposedBlock->print();
    
    // Example usage of SparseBlock
    Eigen::SparseMatrix<double> sparse(4, 4);
    sparse.insert(2, 2) = 30;
    sparse.insert(3, 3) = 40;
    sparse.insert(2, 3) = 50;
    sparse.insert(3, 1) = 60;
    PlockY::SparseBlock<double> sparseBlock(4, 4);
    sparseBlock.setMatrix(sparse);
    sparseBlock.print();

    auto sparseBlockPtr = std::make_shared<PlockY::SparseBlock<double>>(sparseBlock);
    // Example usage of TransposeOf
    auto transposedSparseBlock = std::make_shared<PlockY::TransposeOf<PlockY::SparseBlock<double>>>(sparseBlockPtr);
    std::cout << "Transposed sparse block:" << std::endl;
    auto mat = transposedSparseBlock->getMatrix();
    PlockY::SparseBlock<double> sparseBlockT(4, 4);
    sparseBlockT.setMatrix(mat);
    sparseBlockT.print();
    transposedSparseBlock->print();


    // Example usage of VecBlock
    Eigen::VectorXd vec(6);
    vec << 50, 60, 0,0,0,2;
    PlockY::VecBlock<double> vecBlock(6);
    vecBlock.setMatrix(vec);

    vecBlock.print();

    return 0;
}
