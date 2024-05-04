#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "Eigen/Dense"
#include <memory>
#include <numeric>
#include "PlockY/loader_helper.hpp"
#include "PlockY/BlockVector.hpp"
#include <iostream>

namespace PlockY {
    class BlockVectorLoader {
    public:
        template <typename Scalar>
        static BlockVector<Scalar> load(const std::string& vblkFilePath) { 
        static_assert(std::is_arithmetic<Scalar>::value, "Scalar must be a numeric type");
        
        BlockVector<Scalar> blockVector;
        
        std::ifstream file(vblkFilePath);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + vblkFilePath);
        }
        std::string line;

        while (std::getline(file, line)) {
            std::istringstream iss(line);
            int pos, size;
            std::string blockFilePath;

            if (!(iss >> pos >> size >> blockFilePath)) {
                break;  // Error
            }
            
            // Determine the file extension
            std::string extension = PlockYHelper::getFileExtension(blockFilePath);
            // Create the appropriate factory based on the file extension
            std::unique_ptr<AbstractBlockFactory<Scalar>> factory =  PlockYHelper::createFactory<Scalar>(extension);

            std::unique_ptr<VecBlock<Scalar>> block = factory->createVector(blockFilePath,size);
            
            blockVector.setBlock(pos, std::move(block));
        }
        return blockVector;
        }
    };
}