#pragma once
#include <string>
#include <memory>
#include "PlockY/AbstractBlockLoaderFactory.hpp"
#include "PlockY/CSVBlockLoaderFactory.hpp"

namespace PlockYHelper{
    std::string getFileExtension(const std::string& filePath);

    template <typename Scalar>
    class FactoryRegistry {
        public:
            static FactoryRegistry& getInstance() {
                static FactoryRegistry instance;
                return instance;
            }

            std::shared_ptr<PlockY::AbstractBlockFactory<Scalar>> getFactory(const std::string& identifier) {
                std::string lower_extension;
                std::transform(identifier.begin(), identifier.end(), std::back_inserter(lower_extension), ::tolower);
                auto it = factories_.find(lower_extension);
                if (it != factories_.end()) {
                    return it->second;
                }else{
                    registerFactory(lower_extension);
                    return factories_[lower_extension];
                }
            }

        private:
            void registerFactory(const std::string& extension) {
                if (extension == "csv") {
                    factories_[extension] = std::make_shared<PlockY::CsvBlockLoader<Scalar>>();
                }else{
                    throw std::runtime_error("Unsupported file extension");
                }
            }
            std::unordered_map<std::string, std::shared_ptr<PlockY::AbstractBlockFactory<Scalar>> > factories_;

            FactoryRegistry() = default;
            FactoryRegistry(const FactoryRegistry&) = delete;
            FactoryRegistry& operator=(const FactoryRegistry&) = delete;
        };

}