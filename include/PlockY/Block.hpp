#pragma once

#include <Eigen/Dense>
#include <Eigen/Sparse>

namespace PlockY{
    template <typename Scalar>
    class Block {
        public:
            Block();
            virtual ~Block() = 0;

            Block(int rows_, int cols_) : rows(rows_), cols(cols_) {}

            // Get dimensions
            int getRows() const { return rows; }
            int getCols() const { return cols; }

            // Pure virtual methods for operations that all blocks must support
            virtual Scalar get(int row, int col) const = 0;
            virtual void set(int row, int col, const Scalar& value) = 0;

        private:
            int rows;
            int cols;
    };

    template <typename scalar>
    Block<scalar>::~Block() {}

    // Block class and makes it pure virtual,
    // which means Block is an abstract base class and cannot be instantiated on its own.
    // However, even though the destructor is pure virtual, you still need to provide an implementation for it. This is because when a derived class is destroyed, it first calls its own destructor, then the destructor of its base class. If the base class destructor is not defined, you'll get a linker error.
}