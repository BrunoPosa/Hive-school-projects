#!/bin/bash

# Define paths and variables
MLX42_DIR="./MLX42"
MLX42_REPO="https://github.com/codam-coding-college/MLX42.git"

# Check if MLX42 directory exists
if [ ! -d "$MLX42_DIR" ]; then
    echo "MLX42 library not found. Cloning and building it..."
    git clone "$MLX42_REPO"
    cd MLX42 || exit
    cmake -B build
    cmake --build build -j4
    cd ..
else
    echo "MLX42 library already exists. Skipping download."
fi
