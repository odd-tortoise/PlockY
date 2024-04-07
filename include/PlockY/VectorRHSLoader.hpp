#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "Eigen/Dense"
#include "Plocky/VectorRHS.hpp"
#include "PlockY/VectorBlockLoaderFactory.hpp"
#include "PlockY/CSVVecBlockLoader.hpp"

namespace PlockY {
    template <typename Scalar>
    class VectorRHSLoader {
    static_assert(std::is_arithmetic<Scalar>::value, "Scalar must be a numeric type");
    
    private: 
        std::string getFileExtension(const std::string& filePath) {
            size_t dotPos = filePath.rfind('.');
            if (dotPos == std::string::npos) {
                throw std::runtime_error("File has no extension");
            }
            return filePath.substr(dotPos + 1);
        }

        std::unique_ptr<VectorBlockLoaderFactory<Scalar>> createFactory(const std::string& extension) {
            if (extension == "csv") {
                return std::make_unique<CSVVecBlockLoader<Scalar>>();;
            }else{
                throw std::runtime_error("Unsupported file extension");
            }
        }
    
      
    
    public:

    VectorRHS<Scalar> load(const std::string& filename) { //Static ?
        VectorRHS<Scalar> vectorRHS;
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
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
            std::string extension = getFileExtension(blockFilePath);

            std::cout<<pos<<size<<blockFilePath<<std::endl;

            // Create the appropriate factory based on the file extension
            std::unique_ptr<VectorBlockLoaderFactory<Scalar>> factory = createFactory(extension);

            std::unique_ptr<Eigen::VectorXd> block = factory->createBlock(blockFilePath);
            
            vectorRHS.setBlock(pos, std::move(block));
        }
        return vectorRHS;
    }
};
}