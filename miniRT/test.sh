#!/bin/bash

# Clear the terminal screen
clear

# Recompile the raytracer
make
make clean

# Run the raytracer
# ./file_to_list test_short.rt
./miniRT scenes/test_1_sphere.rt #> log.txt && vim log.txt


# Display the image
#cat output.ppm
