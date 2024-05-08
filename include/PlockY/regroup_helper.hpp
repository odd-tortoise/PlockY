#pragma once
#include <Eigen/Dense>

namespace PlockYHelper {

    template <typename Scalar>
    using DenseScalarMat = Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>;
    template <typename Scalar>
    using SparseScalarMat = Eigen::SparseMatrix<Scalar>;

    // Concatenate matrices horizontally with variadic templates
    template <typename Scalar>
    void concatenate(DenseScalarMat<Scalar>& res, const DenseScalarMat<Scalar>& A) {
        res = A;
    }

    template <typename Scalar,typename... Args>
    void concatenate(DenseScalarMat<Scalar>& res, const DenseScalarMat<Scalar>& A, const DenseScalarMat<Scalar>& B, Args&&... args) {
        DenseScalarMat<Scalar> temp = DenseScalarMat<Scalar>::Zero(A.rows(), A.cols() + B.cols());
        temp << A, B;
        concatenate<Scalar>(res, temp, std::forward<Args>(args)...);
    }

    // Concatenate hor VECTOR of Eignen matrices or vectors
    template <typename Scalar>
    DenseScalarMat<Scalar> concatenateVec(const std::vector<DenseScalarMat<Scalar>>& matrices) {
        DenseScalarMat<Scalar> res = DenseScalarMat<Scalar>::Zero(matrices[0].rows(), 0);
        for (const auto& matrix : matrices) {
            DenseScalarMat<Scalar> temp = DenseScalarMat<Scalar>::Zero(matrix.rows(), res.cols() + matrix.cols());
            temp << res, matrix;
            res = temp;
        }
        return res;
    }

    template <typename Scalar>
    DenseScalarMat<Scalar> concatenateVecVertical(const std::vector<DenseScalarMat<Scalar>>& matrices) {
        DenseScalarMat<Scalar> res = DenseScalarMat<Scalar>::Zero(0, matrices[0].cols());
        for (const auto& matrix : matrices) {
            DenseScalarMat<Scalar> temp = DenseScalarMat<Scalar>::Zero(res.rows() + matrix.rows(), matrix.cols());
            temp.topRows(res.rows()) = res;
            temp.bottomRows(matrix.rows()) = matrix;
            res = temp;
        }
        return res;
    }


    template <typename Scalar>
    DenseScalarMat<Scalar> concatenateVecOfVec(const std::vector<std::vector<DenseScalarMat<Scalar>>>& matrices) {
        DenseScalarMat<Scalar> res = DenseScalarMat<Scalar>::Zero(0, matrices[0][0].cols());
        std::vector<DenseScalarMat<Scalar>> tempVec;
        for (const auto& row : matrices) {
            DenseScalarMat<Scalar> temp = DenseScalarMat<Scalar>::Zero(row[0].rows(), 0);
            temp = concatenateVec<Scalar>(row);
            tempVec.push_back(temp);
        }
        return concatenateVecVertical<Scalar>(tempVec);
    }

    template <typename Scalar>
    DenseScalarMat<Scalar> concatenateVecOfVec2(const std::vector<std::vector<Eigen::MatrixXd>>& matrices) {
        int totalRows = 0;
        int totalCols = 0;

        // Calculate total rows and columns
        for (const auto& row : matrices) {
            totalRows += row[0].rows();
            totalCols = std::max(totalCols, static_cast<int>(static_cast<Eigen::Index>(row.size()) * row[0].cols()));
        }
        

        // Resize the result matrix
        DenseScalarMat<Scalar> res(totalRows, totalCols);

        int rowIndex = 0;
        int colIndex = 0;

        // Fill the result matrix
        for (const auto& row : matrices) {
            colIndex = 0;
            for (const auto& matrix : row) {
                res.block(rowIndex, colIndex, matrix.rows(), matrix.cols()) = matrix;
                colIndex += matrix.cols();
            }
            rowIndex += row[0].rows();
        }

        return res;
    }

}