# PlockY

## Overview

PlockY is a header-only C++ library designed for constructing and solving block matrix systems using iterative splitting algorithms. These algorithms efficiently address large-scale linear systems by leveraging their block structure, decomposing the original problem into smaller, more manageable subproblems that can be solved iteratively. 

## Features

- **Eigen Integration:** Uses the Eigen library for optimized linear algebra operations, benefiting from its state-of-the-art C++ template capabilities for matrix and vector computations.
- **CMake Support:** Facilitates easy integration into projects through CMake, ensuring compatibility across various platforms.
- **Customizable Splitting Schemes:** Allows users to define splitting strategies that optimally decompose and solve matrix systems tailored to specific problem domains.
- **File Handling:** Provides tools to load matrix and vector blocks from custom file formats (.blk and .vblk), supporting flexible data management and integration.
- **Testing:** Includes unit and integration tests for robustness.
- **Continuous Integration:** Automated testing via GitHub Actions across multiple platforms.
- **Profiling:** Use of gperftools for performance analysis to identify bottlenecks and optimize the code.

## Building the Library

To build PlockY, follow these steps:

1. **Clone the Repository:**

   ```bash
   git clone https://github.com/odd-tortoise/PlockY.git
   cd PlockY
   ```

2. **Create Build Directory:**

   ```bash
   mkdir build
   cd build
   ```

3. **Generate Build Files:**

   Run CMake to generate the necessary build files. You can customize the build process with various options:

   ```bash
   cmake .. -DBUILD_TESTS=ON -DBUILD_DOCS=OFF
   ```

   - **BUILD_TESTS:** Enables/disables building of tests (ON by default).
   - **BUILD_DOCS:** Enables/disables building of documentation (ON by default).
   - **BUILD_BENCHMARKS:** Enables/disables building of benchmarks (ON by default).

4. **Build the Project:**

   ```bash
   cmake --build .
   ```

5. **Run Tests:**

   To verify the build, run the tests:

   ```bash
   ctest -V
   ```

## .blk and .vblk Files

PlockY uses custom file formats (.blk and .vblk) to manage matrix and vector data blocks:

- **.blk Files:** Describe block matrices, specifying block positions, sizes, and file paths. They also allow for special blocks like zero and transpose blocks.
- **.vblk Files:** Define vector blocks with similar functionality, including size and file path specifications.

### Example .blk File Format:

```plaintext
[Blocks]
0 0 3 3 ../data/blockA.csv
0 1 3 3 ../data/blockB.csv

[Transpose]
1 0 0 1

[Zero]
1 1 3 3
```

## Solving the System

To solve block matrix systems, PlockY provides a flexible approach through the **Strategy** and **Solver** classes:

1. **Define a Splitting Strategy:** Use the `Step` and `Strategy` classes to specify how the matrix blocks should be split and solved.
2. **Initialize the Solver:** Create a solver instance with parameters such as tolerance, maximum iterations, and relaxation factor.
3. **Execute the Solving Process:** Call the `solve` method to iteratively solve the system based on the defined strategy.

Example of usage can be found in the examples folder.

## Dependencies

PlockY relies on several key dependencies:

- **Eigen:** For matrix and vector operations.
- **Catch2:** For unit testing.

## Validation

The library's validation involved benchmark tests comparing PlockY’s iterative splitting schemes against standard monolithic solutions using Matlab for reference. The benchmarks are included in the corresponding folder.

## Future Work

Future developments will focus on expanding file format support, optimizing solver performance, enhancing modularity, and improving documentation through Doxygen and other tools.

