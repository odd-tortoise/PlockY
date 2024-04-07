# PlockY


## TODO 

- branch parser: implementare i vari loader
- branch CRTP: capire se ha senso o meno usare il CRTP per i BLocchi o i solver? 
- branch solver: capire qual è il modo ottimale per implementare la risuluzione dei singoli blocchi. Come differenziare correttemente tra dense e sparse. Il solver genereale si occuperà di "spostare" i blocchi fare lo splitting, che design? Strategy?.


- vario: doxygen, pybind, rifinire alcuni metodi , capire se vogliamo salvere le coordinate "vere" dei blocchi, aggiungere una classe VectorBlock similmente a Block?

## Build

1) Generate the build files: Open a terminal, navigate to your project directory, create a new directory named build (if it doesn't exist already), navigate into it, and run ```cmake ..```
to generate the build files.

2) Build the project: Still in the build directory, run ```cmake --build .``` to build your project. This will compile all your source files and test files into executables.

3) Run the test: After building the project, you should have an executable named test_MyClass in your build directory. You can run it with ```./test_MyClass``` (on Unix-based systems) or test_MyClass.exe (on Windows).


## .blk file

Example Block File (.blk): file format for storing information related to matrices blocks.
Format:

```
<X> <Y> <Width> <Height> <Path> <Description>

0 0  1 1  block_1.blabla "Small Block"
2 2  3 3  block_2.blabla "Large Block"
```

## .vblk file

Example Vector Block File (.cblk): file format for storing information related to vectors blocks.
Format:

```
<X> <Size> <Path>

0 2  block_1.blabla
2 3  block_2.blabla
```
