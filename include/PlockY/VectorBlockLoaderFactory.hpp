#pragma once

namespace PlockY {

    template <typename Scalar>
    class VectorBlockLoaderFactory {
        static_assert(std::is_arithmetic<Scalar>::value, "Scalar must be a numeric type");
    public:
        virtual std::unique_ptr<Eigen::VectorXd> createBlock(const std::string& filename) = 0;
    };
}