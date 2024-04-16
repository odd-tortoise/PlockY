
#pragma once
#include <Eigen/Core>

namespace PlockY {


/*    template<class T, template<class> class U>
    inline constexpr bool is_instance_of_v = std::false_type{};

    template<template<class> class U, class V>
    inline constexpr bool is_instance_of_v<U<V>,U> = std::true_type{};
*/
    class BlockSolverBase {
        using VectorType = Eigen::VectorXd;
        using MatrixType = Eigen::MatrixXd;     
    public:
        virtual ~BlockSolverBase() = default;
        virtual VectorType solve(const MatrixType& block, const VectorType& vector) const = 0;
    };

} // namespace PlockY