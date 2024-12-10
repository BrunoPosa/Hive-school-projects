#!/bin/bash

# Clear the terminal screen
clear

# Recompile the raytracer
make re
make clean

# Run the raytracer
# ./file_to_list test_short.rt
./miniRT scenes/2_just_shadows.rt #> log.txt && vim log.txt


# Display the image
#cat output.ppm
