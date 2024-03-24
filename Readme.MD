# Project Title

A brief description of what this project does and who it's for.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Build

1) Generate the build files: Open a terminal, navigate to your project directory, create a new directory named build (if it doesn't exist already), navigate into it, and run 
```
cmake ..
```
to generate the build files.
2) Build the project: Still in the build directory, run

```
cmake --build .
```

to build your project. This will compile all your source files and test files into executables.
3) Run the test: After building the project, you should have an executable named test_MyClass in your build directory. You can run it with ```./test_MyClass``` (on Unix-based systems) or test_MyClass.exe (on Windows).

## CLASS DIAGRAM
``` mermaid 
classDiagram
    MatrixLoader <|-- CsvMatrixLoader
    MatrixLoader <|-- BinaryMatrixLoader
    MatrixLoader <|-- BlockMatrixLoader
    MatrixLoader : +loadMatrix(filePath string)
    CsvMatrixLoader : +loadMatrix(filePath string)
    BinaryMatrixLoader : +loadMatrix(filePath string)
    BlockMatrixLoader : +loadMatrix(filePath string)
    BlockMatrixLoader : -loadBlockData(filePath string)
    Matrix <|-- EigenMatrix
    Matrix <|-- BlockMatrix
    Matrix : -Eigen Matrix
    Matrix : -BlockMatrix
    Matrix : +solveSystem()
    Matrix : +transpose()
    Matrix : +determinant()
    Matrix : +inverse()
    EigenMatrix : -Eigen Matrix
    EigenMatrix : +solveSystem()
    EigenMatrix : +transpose()
    EigenMatrix : +determinant()
    EigenMatrix : +inverse()
    BlockMatrix : -BlockMatrix
    BlockMatrix : +blockTranspose()
    BlockMatrix : +blockInverse()
    BlockMatrix : +blockDeterminant()
    BlockMatrix : +loadFromFile()
    BlockMatrix : +saveToFile()
```

## Block

Block is a template -> header only