#!/bin/bash

# Clear the terminal screen
clear

# Recompile the raytracer
make re
make clean

# Run the raytracer
# ./file_to_list test_short.txt
./file_to_list test_short.txt

# Display the image
#cat output.ppm
