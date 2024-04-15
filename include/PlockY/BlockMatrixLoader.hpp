#pragma once

#include "PlockY/AbstractBlockLoaderFactory.hpp"
#include "PlockY/CSVBlockLoaderFactory.hpp"
#include "PlockY/BinBlockLoaderFactory.hpp"
#include "PlockY/BlockMatrix.hpp"
#include "PlockY/Block.hpp"
#include <string>
#include <fstream>
#include <iostream>

namespace PlockY {
    template <typename Scalar>
    class BlockMatrixLoader {
    static_assert(std::is_arithmetic<Scalar>::value, "Scalar must be a numeric type");
    private: 
        std::string getFileExtension(const std::string& filePath) {
            size_t dotPos = filePath.rfind('.');
            if (dotPos == std::string::npos) {
                throw std::runtime_error("File has no extension");
            }
            return filePath.substr(dotPos + 1);
        }

        std::unique_ptr<AbstractBlockFactory<Scalar>> createFactory(const std::string& extension) {
            if (extension == "csv") {
                return std::make_unique<CsvBlockLoader<Scalar>>();;
            } else if  (extension == "bin") {
                return std::make_unique<BinBlockLoader<Scalar>>();;
                } else {
                throw std::runtime_error("Unsupported file extension");
            }
        }
        
    public:
        BlockMatrixLoader(){};

        BlockMatrix<Scalar> load(const std::string& blkFilePath) {
            BlockMatrix<Scalar> blockMatrix;
            std::ifstream file(blkFilePath);
            std::string line;

            while (std::getline(file, line)) {
                std::istringstream iss(line);
                int posRow, posCol, row, col;
                std::string blockFilePath, blockType;

                if (!(iss >> posRow >> posCol >> row >> col >> blockFilePath >> blockType)) {
                    break;  // Error
                }

                // Determine the file extension
                std::string extension = getFileExtension(blockFilePath);

                // Create the appropriate factory based on the file extension
                std::unique_ptr<AbstractBlockFactory<Scalar>> factory = createFactory(extension);
                // Use the factory to create a block based on the type
                std::unique_ptr<Block<Scalar>> block = (blockType == "Dense") ? 
                    factory->createDense(blockFilePath,row,col) : factory->createSparse(blockFilePath,row,col);
                blockMatrix.setBlock(posRow, posCol, std::move(block));
            }
            return blockMatrix;
        }
    };
}
