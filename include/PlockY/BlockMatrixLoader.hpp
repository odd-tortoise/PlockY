#pragma once

#include "PlockY/BlockLoaderFactory.hpp"
#include "PlockY/BlockMatrix.hpp"
#include "PlockY/CsvBlockLoader.hpp"
#include "PlockY/Block.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <variant>

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
            } else {
                throw std::runtime_error("Unsupported file extension");
            }
        }
    using BlockPtr = std::variant<std::shared_ptr<DenseBlock<Scalar>>, std::shared_ptr<SparseBlock<Scalar>>>;
    
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

                BlockPtr block;
                
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