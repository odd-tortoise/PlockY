#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <vector>
#include <iostream>
#include "PlockY/Regrouper.hpp"  // Assuming the MatrixConcatenator is defined in this header file

int main() {
    // Create some dense matrices
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> denseMatrix1 = Eigen::Matrix<double, 3, 3>::Random();
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> denseMatrix2 = Eigen::Matrix<double, 3, 3>::Random();

    // Print the original dense matrices
    std::cout << "Dense matrix 1:\n" << denseMatrix1 << "\n\n";
    std::cout << "Dense matrix 2:\n" << denseMatrix2 << "\n\n";

    // Concatenate the dense matrices horizontally
    std::vector<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>> denseMatrices = {denseMatrix1, denseMatrix2};
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> denseResultHor = PlockY::MatrixConcatenator<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>>::concatenateHorizontally(denseMatrices);
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> denseResultVer = PlockY::MatrixConcatenator<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>>::concatenateVertically(denseMatrices);
    // Print the result of the dense matrix concatenation
    std::cout << "Concatenated dense matrices hor:\n" << denseResultHor << "\n\n";
    std::cout << "Concatenated dense matrices ver:\n" << denseResultVer << "\n\n";


    // Create some sparse matrices
    Eigen::SparseMatrix<double> sparseMatrix1(3, 3);
    Eigen::SparseMatrix<double> sparseMatrix2(3, 3);

    sparseMatrix1.insert(0, 0) = 1.0;
    sparseMatrix1.insert(1, 2) = 2.0;
    sparseMatrix2.insert(2, 0) = 3.0;
    sparseMatrix2.insert(1, 1) = 4.0;
    sparseMatrix2.insert(1, 2) = 5.0;
    sparseMatrix1.insert(2, 1) = 6.0;
    

    // Print the original sparse matrices
    std::cout << "Sparse matrix 1:\n" << Eigen::MatrixXd(sparseMatrix1) << "\n\n";
    std::cout << "Sparse matrix 2:\n" << Eigen::MatrixXd(sparseMatrix2) << "\n\n";

    // Concatenate the sparse matrices vertically
    std::vector<Eigen::SparseMatrix<double>> sparseMatrices = {sparseMatrix1, sparseMatrix2};
    Eigen::SparseMatrix<double> sparseResultHor = PlockY::MatrixConcatenator<Eigen::SparseMatrix<double>>::concatenateHorizontally(sparseMatrices);
    Eigen::SparseMatrix<double> sparseResultVer = PlockY::MatrixConcatenator<Eigen::SparseMatrix<double>>::concatenateVertically(sparseMatrices);

    // Print the result of the sparse matrix concatenation
    std::cout << "Concatenated sparse matrices hor:\n" << Eigen::MatrixXd(sparseResultHor) << "\n\n";
    std::cout << "Concatenated sparse matrices ver:\n" << Eigen::MatrixXd(sparseResultVer) << "\n\n";

    return 0;
}
/*
int main() {
    /*
    // Create two sparse matrices
    Eigen::SparseMatrix<double> A(2, 3);
    A.insert(0, 0) = 1.0;
    A.insert(1, 2) = 2.0;

    Eigen::SparseMatrix<double> B(2, 2);
    B.insert(0, 0) = 3.0;
    B.insert(1, 1) = 4.0;

    // Concatenate matrices horizontally
    Eigen::SparseMatrix<double> C(A.rows(), A.cols() + B.cols());
    C.reserve(A.nonZeros() + B.nonZeros());

    for (int k = 0; k < A.outerSize(); ++k) {
        for (Eigen::SparseMatrix<double>::InnerIterator it(A, k); it; ++it) {
            C.insert(it.row(), it.col()) = it.value();
        }
    }

    // Fill C with the non-zero values of B
    for (int k = 0; k < B.outerSize(); ++k) {
        for (Eigen::SparseMatrix<double>::InnerIterator it(B, k); it; ++it) {
            C.insert(it.row(), A.cols() + it.col()) = it.value();
        }
    }

    // Print the concatenated matrix
        // Print the concatenated matrix
    Eigen::MatrixXd denseC = Eigen::MatrixXd(C);
    std::cout << "Concatenated HOR matrix C:\n" << denseC << std::endl;


    Eigen::SparseMatrix<double> D(2, 2);
    D.insert(0, 0) = -1.0;
    D.insert(1, 1) = 2.0;

        // Concatenate matrices vertically
    Eigen::SparseMatrix<double> F(B.rows() + D.rows(), D.cols());
    F.reserve(B.nonZeros() + D.nonZeros());

    // Fill C with the non-zero values of A
    for (int k = 0; k < B.outerSize(); ++k) {
        for (Eigen::SparseMatrix<double>::InnerIterator it(B, k); it; ++it) {
            F.insert(it.row(), it.col()) = it.value();
        }
    }

    // Fill C with the non-zero values of B
    for (int k = 0; k < D.outerSize(); ++k) {
        for (Eigen::SparseMatrix<double>::InnerIterator it(D, k); it; ++it) {
            F.insert(B.rows() + it.row(), it.col()) = it.value();
        }
    }

    // Print the concatenated matrix
    denseC = Eigen::MatrixXd(F);
    std::cout << "Concatenated VER matrix C:\n" << denseC << std::endl;
    

   Eigen::SparseMatrix<double> A(2, 3);
    A.insert(0, 0) = 1.0;
    A.insert(1, 2) = 2.0;

    Eigen::SparseMatrix<double> B(2, 2);
    B.insert(0, 0) = 3.0;
    B.insert(1, 1) = 4.0;

    Eigen::SparseMatrix<double> D(1, 3);
    D.insert(0, 1) = 5.0;

    // Concatenate matrices horizontally
    std::vector<Eigen::SparseMatrix<double>> matricesHor = {A, B};
    Eigen::SparseMatrix<double> C = concatenateHorizontally(matricesHor);

    // Print the horizontally concatenated matrix
    Eigen::MatrixXd denseC = Eigen::MatrixXd(C);
    std::cout << "Concatenated HOR matrix C:\n" << denseC << std::endl;

    // Concatenate matrices vertically
    std::vector<Eigen::SparseMatrix<double>> matricesVer = {A, D};
    Eigen::SparseMatrix<double> E = concatenateVertically(matricesVer);

    // Print the vertically concatenated matrix
    Eigen::MatrixXd denseE = Eigen::MatrixXd(E);
    std::cout << "Concatenated VER matrix E:\n" << denseE << std::endl;

    return 0;

    return 0;
}

*/