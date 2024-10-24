#!/bin/bash

# Clear the terminal screen
clear

# Recompile the raytracer
make re

# Run the raytracer
./ray_tracer

# Display the image
cat output.ppm