#!/bin/bash

# Clear the terminal screen
clear

# Recompile the raytracer
make re
make clean

# Run the raytracer
# ./file_to_list test_short.rt
./file_to_list scenes/test_1_sphere.rt

# Display the image
#cat output.ppm
