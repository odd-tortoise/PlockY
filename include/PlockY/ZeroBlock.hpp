#pragma once
#include <memory>
#include <type_traits>
#include "PlockY/Block.hpp"

namespace PlockY {
    template<class BlockClass>
    class ZeroBlock : public BlockClass {
    public:
        ZeroBlock() : BlockClass() {
            static_assert(std::is_base_of<Block<typename BlockClass::MatrixType>, BlockClass>::value, "BlockClass must be a subclass of Block");
        }
        virtual ~ZeroBlock() = default;  

        // devo restiture una copia della matrice trasposta, non posso fare overridin
        typename BlockClass::MatrixType getMatrix() const {  
            return block->getMatrix().transpose();
        }

        void print() const {
            if (BlockClass::getType() == BlockTypeEnum::Dense) {
                std::cout << block->getMatrix().transpose() << std::endl;
            } else if (BlockClass::getType() == BlockTypeEnum::Sparse) {
                std::cout<<"sto usando il print  sparse Trasposto"<<std::endl;
            }
        }
    };
} // namespace PlocKy