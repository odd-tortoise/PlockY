#pragma once

#include "PlockY/AbstractBlockLoaderFactory.hpp"
#include "PlockY/CSVBlockLoaderFactory.hpp"
#include "PlockY/BlockMatrix.hpp"
#include "PlockY/Block.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include "PlockY/loader_helper.hpp"

namespace PlockY {
    class BlockMatrixLoader {
    public:
        template <typename Scalar>
        static BlockMatrix<Scalar> load(const std::string& blkFilePath) {
        static_assert(std::is_arithmetic<Scalar>::value, "Scalar must be a numeric type");
        
        BlockMatrix<Scalar> blockMatrix;
       
        std::ifstream file(blkFilePath);
        if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + blkFilePath);
        }
        std::string line;

        while (std::getline(file, line)) {
            std::istringstream iss(line);
            int posRow, posCol, row, col;
            std::string blockFilePath, blockType;

            if (!(iss >> posRow >> posCol >> row >> col >> blockFilePath >> blockType)) {
                break;  // Error
            }

            // Determine the file extension
            std::string extension = PlockYHelper::getFileExtension(blockFilePath);

            // Create the appropriate factory based on the file extension
            std::unique_ptr<AbstractBlockFactory<Scalar>> factory =  PlockYHelper::createFactory<Scalar>(extension);
            // Use the factory to create a block based on the type
            std::unique_ptr<Block<Scalar>> block = nullptr;

            if (blockType == "Dense")
                block = factory->createDense(blockFilePath,row,col);
            else
                block = factory->createSparse(blockFilePath,row,col);
                
            blockMatrix.setBlock(posRow, posCol, std::move(block));

        }
        return blockMatrix;
        }
    };
}