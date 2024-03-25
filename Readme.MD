# PlockY


## TODO 

- finire di implementare BlockMatrix e decidere come strutturare il file che si occupa di gestire i blocchi della matrice

- scirvere il dataloader (abstract factory direi)

- capire come gestire la parte di solver

- doxygen

- pyBinding alla fine o mano a mano?

- file .blk ?


## Build

1) Generate the build files: Open a terminal, navigate to your project directory, create a new directory named build (if it doesn't exist already), navigate into it, and run ```cmake ..```
to generate the build files.

2) Build the project: Still in the build directory, run ```cmake --build .``` to build your project. This will compile all your source files and test files into executables.

3) Run the test: After building the project, you should have an executable named test_MyClass in your build directory. You can run it with ```./test_MyClass``` (on Unix-based systems) or test_MyClass.exe (on Windows).


## .blk file

Example Block File (.blk): file format for storing information related to blocks.
Format:

```
<X> <Y> <Width> <Height> <Path> <Description>

0 0  1 1  block_1.blabla "Small Block"
2 2  3 3  block_2.blabla "Large Block"
```

## CLASS DIAGRAM - DEPRECATED - vecchio da aggiornate
``` mermaid 
classDiagram
   
```

## Commenti sparsi sulle varie classi

### Block

Block is a template -> header only.

Block class and makes it pure virtual, which means Block is an abstract base class and cannot be instantiated on its own.
However, even though the destructor is pure virtual, you still need to provide an implementation for it. This is because when a derived class is destroyed, it first calls its own destructor, then the destructor of its base class. If the base class destructor is not defined, you'll get a linker error.

#### Sparse Block


#### Dense Block

