#pragma once

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <iostream>

namespace PlockY {
  enum class BlockType { Dense, Sparse };

  template <typename Derived, typename Scalar>
    class Block
    {
    public:
        // Constructor non dovrebbe essere private? 
        Block(int rows, int cols) : rows(rows), cols(cols) {}

        // Implement operations for blocks
        Scalar get(int row, int col) const { return static_cast<const Derived*>(this)->getImpl(row, col); }
        void set(int row, int col, const Scalar& value) { static_cast<Derived*>(this)->setImpl(row, col, value); }

        int getRows() const { return rows; }
        int getCols() const { return cols; }

        virtual BlockType getType() const = 0;

        /*
         method declaration in the base class, you don't need to use static_cast. The method is declared as a pure virtual function, which means it doesn't have an implementation in the base class and must be overridden by any non-abstract derived class.*/


    private:
        int rows;
        int cols;
    };
}

/* The `get` and `set` methods in your `Block` class are using the Curiously Recurring Template Pattern (CRTP) to delegate the actual implementation to the derived class.

Here's how they work:

1. `get(int row, int col)`: This method is used to get the value at the specified row and column in the block. It works by casting `this` to a pointer to the derived class (`Derived*`) and then calling the `getImpl` method on the derived class. The `getImpl` method is expected to be implemented by the derived class and should return the value at the specified row and column.

2. `set(int row, int col, const Scalar& value)`: This method is used to set the value at the specified row and column in the block. It works by casting `this` to a pointer to the derived class (`Derived*`) and then calling the `setImpl` method on the derived class. The `setImpl` method is expected to be implemented by the derived class and should set the value at the specified row and column.

In both methods, `static_cast<Derived*>(this)` is used to cast `this` to a `Derived*`. This is safe because of the CRTP: the `Block` class is designed to be used as a base class for `Derived`, so `this` is guaranteed to actually be a `Derived*`.k*/