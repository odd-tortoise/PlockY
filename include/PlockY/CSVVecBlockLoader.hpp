#pragma once
#include "VectorBlockLoaderFactory.hpp"
#include <iostream>
namespace PlockY {
    template <typename Scalar>
    class CSVVecBlockLoader : public VectorBlockLoaderFactory<Scalar> {
        static_assert(std::is_arithmetic<Scalar>::value, "Scalar must be a numeric type");
    public:
        std::unique_ptr<Eigen::VectorXd> createBlock(const std::string& filename) override {
            std::ifstream file(filename);
            if (!file.is_open()) {
                throw std::runtime_error("Failed to open file: " + filename);
            }
            std::string line;
            std::vector<Scalar> values;
            while (std::getline(file, line, ',')) {
                std::istringstream iss(line);
                Scalar value;
                while (iss >> value) {
                    values.push_back(value);
                }
            }
            for (auto value : values) {
                std::cout << value << " ";
            }
            return std::make_unique<Eigen::VectorXd>(Eigen::Map<Eigen::VectorXd>(values.data(), values.size()));
        }
    };
} // namespace PlockY