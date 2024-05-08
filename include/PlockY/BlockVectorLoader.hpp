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

        template <typename BlockType>
        static BlockVector<BlockType> load(const std::string& vblkFilePath) {
        
        using MatrixType = typename BlockType::MatrixType;
        using Scalar = typename MatrixType::Scalar;
        
        static_assert(std::is_base_of<Block<MatrixType>, BlockType>::value, "BlockClass must be a subclass of Block");

        std::ifstream file(vblkFilePath);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + vblkFilePath);
        }
        if (PlockYHelper::getFileExtension(vblkFilePath) != "vblk") {
            throw std::runtime_error("Invalid file extension");
        }

        std::string line;
        std::string word;
        BlockVector<BlockType> blockVec;

        int pos,size;
        std::string blockFilePath;

        while (std::getline(file, line)) {
            std::istringstream lineStream(line);
            std::string key, equals;

            if (line[0] == '[') {
                key = line.substr(1, line.find(']') - 1);
            }

            if (key == "Blocks") {
                while (std::getline(file, line)) {
                    std::istringstream iss(line);
                    if (!(iss >> pos >> size >> blockFilePath)) {
                        break;  // Error
                    }
                    // Determine the file extension
                    std::string extension = PlockYHelper::getFileExtension(blockFilePath);
                    std::unique_ptr<AbstractBlockFactory<Scalar>> factory =  PlockYHelper::createFactory<Scalar>(extension);               
                    std::unique_ptr<BlockType> block = factory->createVector(blockFilePath, size);
                    blockVec.setBlock(pos, std::move(block));     
                }
            } else if (key == "Zero") {
                while (std::getline(file, line)) {
                    std::istringstream iss(line);
                    if (!(iss >> pos >> size)) {
                        break;  // Error
                    }
                    std::unique_ptr<BlockType> block = std::make_unique<BlockType>(MatrixType::Zero(size));
                    blockVec.setBlock(pos, std::move(block));

                }
            }
        }

        return blockVec;
        }
    
    
    };
}