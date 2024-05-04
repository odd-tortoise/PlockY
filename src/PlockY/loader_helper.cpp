#include "PlockY/loader_helper.hpp"

namespace PlockYHelper{
        std::string getFileExtension(const std::string& filePath) {
            size_t dotPos = filePath.rfind('.');
            if (dotPos == std::string::npos) {
                throw std::runtime_error("File has no extension");
            }
            return filePath.substr(dotPos + 1);
        }   
}