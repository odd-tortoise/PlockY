#pragma once
#include <memory>
#include <type_traits>
#include "PlockY/Block.hpp"

namespace PlockY {
    template<class BlockClass>
    class TransposeOf : public BlockClass {
    private:

    public:
        TransposeOf(std::shared_ptr<BlockClass> block) : block(block) {
            static_assert(std::is_base_of<Block<typename BlockClass::MatrixType>, BlockClass>::value, "BlockClass must be a subclass of Block");
        }
        virtual ~TransposeOf() = default;  

        // devo restiture una copia della matrice trasposta, non posso fare overriding
        const typename BlockClass::MatrixType& getMatrix() const {
            std::cout<<"sto usando il getMatrix Trasposto"<<std::endl;
            return block->getMatrix();
        }

        void print() const {
            if (BlockClass::getType() == BlockTypeEnum::Dense) {
                std::cout << block->getMatrix().transpose() << std::endl;
            } else if (BlockClass::getType() == BlockTypeEnum::Sparse) {
                std::cout<<"sto usando il print sparse Trasposto"<<std::endl;
            }
        }  
    private:
        std::shared_ptr<BlockClass> block;
    };
} // namespace PlocKy