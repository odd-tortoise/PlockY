#pragma once
#include <string>
#include <memory>
#include "PlockY/AbstractBlockLoaderFactory.hpp"
#include "PlockY/CSVBlockLoaderFactory.hpp"

namespace PlockYHelper{
    std::string getFileExtension(const std::string& filePath);

    template <typename Scalar>
    std::unique_ptr<PlockY::AbstractBlockFactory<Scalar>> createFactory(const std::string& extension) {
        if (extension == "csv" || extension == "CSV") {
            return std::make_unique<PlockY::CsvBlockLoader<Scalar>>();;
        }else{
            throw std::runtime_error("Unsupported file extension");
        }
    }
}