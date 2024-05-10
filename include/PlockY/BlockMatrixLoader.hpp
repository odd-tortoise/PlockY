#pragma once

#include "PlockY/AbstractBlockLoaderFactory.hpp"
#include "PlockY/CSVBlockLoaderFactory.hpp"
#include "PlockY/BlockMatrix.hpp"
#include "PlockY/Block.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include "PlockY/loader_helper.hpp"
#include <typeinfo>

namespace PlockY {

    class BlockMatrixLoader {  
    public:
        template <typename BlockType>
        static BlockMatrix<BlockType> load(const std::string& blkFilePath) {
        
        using MatrixType = typename BlockType::MatrixType;
        using Scalar = typename MatrixType::Scalar;
        static_assert(std::is_base_of<Block<MatrixType>, BlockType>::value, "BlockClass must be a subclass of Block");

        std::ifstream file(blkFilePath);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + blkFilePath);
        }
        if (PlockYHelper::getFileExtension(blkFilePath) != "blk") {
            throw std::runtime_error("Invalid file extension");
        }

        std::string line;
        std::string word;
        BlockMatrix<BlockType> blockMatrix;

        int posX, posY, sizeRow, sizeCol;
        int posTX, posTY;
        std::string blockFilePath;
        std::unique_ptr<BlockType> block = nullptr;
        std::string key;

        while (std::getline(file, line)) {
            std::istringstream lineStream(line);
           
            if (line[0] == '[') {
                key = line.substr(1, line.find(']') - 1);
            }
            if(line.empty()){
                continue;
            }

            if (key == "Blocks") {
                while (std::getline(file, line)) {
                    std::istringstream iss(line);
                    if (!(iss >> posX >> posY >> sizeRow >> sizeCol >> blockFilePath)) {
                        break;  // Error
                    }
                    // Determine the file extension
                    std::string extension = PlockYHelper::getFileExtension(blockFilePath);
                    auto factory = PlockYHelper::FactoryRegistry<Scalar>::getInstance().getFactory(extension);
                    if constexpr (std::is_same<BlockType, DenseBlock<Scalar>>::value) {
                        block = factory->createDense(blockFilePath, sizeRow, sizeCol);
                    } else if constexpr (std::is_same<BlockType, SparseBlock<Scalar>>::value) {
                        block = factory->createSparse(blockFilePath, sizeRow, sizeCol);
                    }
                    blockMatrix.setBlock(posX, posY, std::move(block), BlockSpec::Normal);                   
                }
            } else if (key == "Transpose") {
                while (std::getline(file, line)) {
                    std::istringstream iss(line);
                    if (!(iss >> posX >> posY >> sizeRow >> sizeCol >> posTX >> posTY)) {
                        break;  // Error
                    }
                    blockMatrix.setBlock(posX, posY, blockMatrix.getBlock(posTX, posTY), BlockSpec::Transpose);
                }
            } else if (key == "Zero") {
                while (std::getline(file, line)) {
                    std::istringstream iss(line);
                    if (!(iss >> posX >> posY >> sizeRow >> sizeCol)) {
                        break;  // Error
                    }
                    std::unique_ptr<BlockType> block = nullptr;
                    if constexpr (std::is_same<BlockType, DenseBlock<Scalar>>::value) {
                        block = std::make_unique<BlockType>(MatrixType::Zero(sizeRow, sizeCol));
                        blockMatrix.setBlock(posX, posY, std::move(block), BlockSpec::Normal);
                    } else if constexpr (std::is_same<BlockType, SparseBlock<Scalar>>::value) {
                        block = std::make_unique<BlockType>(MatrixType(sizeRow, sizeCol));
                        blockMatrix.setBlock(posX, posY, std::move(block), BlockSpec::Normal);
                    }
                }
            }
        }

        if( ! blockMatrix.isValid()){
            throw std::runtime_error("Invalid block matrix" + blkFilePath);
        }
        
        return blockMatrix;
        }
    };
}