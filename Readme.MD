# PlockY


## TODO 


- capire come gestire la parte di solver

- doxygen

- pyBinding alla fine o mano a mano?

- file .blk vanno bene?

- fare una vera cartella di test e muovere l'attale test in example

- specializzare la classe sparse con asimmetriche etc? 

- eigen as git submodule, aggiugnere le cose per doxygen check al CMake

- stati assert per il check del tipo va bene come è inserito ?

- verificare la giusta implementazione della abs. factory e se ha senso in questo modo

- singletons

- finire i parser dei file, capire come fare quello della sparse, la densa sembra ok con quello di Eigen

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

## Commenti sparsi sulle varie classi

### Block

Block is a template -> header only.

Block class and makes it pure virtual, which means Block is an abstract base class and cannot be instantiated on its own.
However, even though the destructor is pure virtual, you still need to provide an implementation for it. This is because when a derived class is destroyed, it first calls its own destructor, then the destructor of its base class. If the base class destructor is not defined, you'll get a linker error.

#### Sparse Block


#### Dense Block


## Loader

per ora facciamo con dei csv, densi specificano valore per valore (ma va?!) mentre gli sparsi sono (riga, col, valore)