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
        const typename BlockClass::MatrixType& getMatrix() override{
            std::cout<<"sto usando il getMatrix Trasposto"<<std::endl;
            computeTranspose();
            return transpose;
        }

        void print() const {
            if (BlockClass::getType() == BlockTypeEnum::Dense) {
                std::cout << block->getMatrix().transpose() << std::endl;
            } else if (BlockClass::getType() == BlockTypeEnum::Sparse) {
                std::cout<<"sto usando il print sparse Trasposto"<<std::endl;
            }
        }  
    private:
        void computeTranspose() {
            this->transpose = block->getMatrix().transpose().eval();
        }
        std::shared_ptr<BlockClass> block;
        typename BlockClass::MatrixType transpose;
    };
} // namespace PlocKy