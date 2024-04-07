
#pragma once
#include "PlockY/Block.hpp"
#include <Eigen/Core>

namespace PlockY {

    template<class T, template<class> class U>
    inline constexpr bool is_instance_of_v = std::false_type{};

    template<template<class> class U, class V>
    inline constexpr bool is_instance_of_v<U<V>,U> = std::true_type{};


    template<typename BlockType>
    class BlockSolverBase {
        
    public:
        using VectorType = Eigen::VectorXd;

        virtual ~BlockSolverBase() = default;
        virtual VectorType solve(const BlockType& block, const VectorType& vector) const = 0;
    };

} // namespace PlockY