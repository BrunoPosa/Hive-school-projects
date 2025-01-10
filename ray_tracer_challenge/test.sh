#!/bin/bash

# Clear the terminal screen
clear

# Recompile the raytracer
make re
make clean

# Run the raytracer
./ray_tracer

# Display the image
#cat output.ppm