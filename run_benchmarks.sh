#!/bin/bash

# Directory where the benchmark executables are located
BENCHMARKS_DIR="./build/benchmarks"

# Custom list of executables
EXECUTABLES=("test0" "test1")

# Check if the benchmarks directory exists
if [ ! -d "$BENCHMARKS_DIR" ]; then
    echo "Benchmarks directory does not exist: $BENCHMARKS_DIR"
    exit 1
fi

# Navigate to the benchmarks directory
cd "$BENCHMARKS_DIR"

# Loop through the custom list of executables
for executableName in "${EXECUTABLES[@]}"; do
    # Check if the executable file exists
    if [ ! -f "$executableName" ]; then
        echo "Executable does not exist: $executableName"
        continue
    fi

    # Extract the name of the benchmark, assuming no './' prefix needed as we're using a custom list
    benchmark_name=$executableName
    
    # Create a directory for the benchmark if it doesn't exist
    mkdir -p "$benchmark_name"
    
    # Additional commands to execute the benchmark and handle its output would go here
    ./"$benchmark_name" > "$benchmark_name/output.txt" 2>&1
    echo "Executed benchmark: $benchmark_name"
done

echo "All specified benchmarks executed."
cd..
cd..