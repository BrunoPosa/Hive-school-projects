Overview

miniRT is a simple yet powerful ray tracing program built using the MLX42 library. 
The primary goal of this project is to generate computer-generated images of 3D scenes as seen from a specific angle and position. 
The scenes are defined by simple geometric objects and feature their own lighting systems.


Features

Ray Tracing: Generate images using the ray tracing protocol.

Geometric Objects: Supports planes, spheres, and cylinders with proper handling of intersections and internal geometry.

Transformations: Apply translation and rotation transformations to objects, lights, and cameras.

Lighting: Implement ambient and diffuse lighting with spot brightness and hard shadows.

Scene Management: Load scenes from .rt files and display them in a window.

Window Management: Fluid window management with proper handling of minimization, resizing, and closing operations.


Project Structure

Program Name: miniRT

Turn-in Files: All source files required to build and run the project.

Makefile Targets:

all - Build the project.

clean - Remove object files.

fclean - Remove all compiled files and binaries.

re - Rebuild the project.

bonus - Compile any additional bonus features (if applicable).

Arguments: The program takes a scene file in .rt format as an argument.


External Functions Used

Standard C library functions: open, close, read, write, printf, malloc, free, perror, strerror, exit.

Math library functions (linked with -lm): All necessary functions for geometric and lighting calculations.

MLX42 library functions: For rendering and window management.


Scene File Format (.rt)

The scene file is a plain text file with specific elements that define the scene. Each element is identified by a unique identifier and followed by its properties:

Ambient Lighting:

A <ratio> <R,G,B>
Example: A 0.2 255,255,255

Camera:

C <x,y,z> <orientation_vector> <FOV>
Example: C -50.0,0,20 0,0,1 70

Light:

L <x,y,z> <brightness_ratio> <R,G,B>
Example: L -40.0,50.0,0.0 0.6 10,0,255

Sphere:

sp <x,y,z> <diameter> <R,G,B>
Example: sp 0.0,0.0,20.6 12.6 10,0,255

Plane:

pl <x,y,z> <normal_vector> <R,G,B>
Example: pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225

Cylinder:

cy <x,y,z> <axis_vector> <diameter> <height> <R,G,B>
Example: cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255

Example Scene (.rt)

A 0.2 255,255,255

C -50,0,20 0,0,1 70

L -40,0,30 0.7 255,255,255

pl 0,0,0 0,1.0,0 255,0,225

sp 0,0,20 20 255,0,0

cy 50.0,0.0,20.6 0,0,1.0 14.2 21.42 10,0,255


Error Handling

The program must handle any misconfiguration in the .rt file gracefully. 
If an error is encountered, the program should exit and display "Error\n" followed by an explicit error message.


Usage

Compile the program using the provided Makefile.

Run the program with a scene file as an argument.

./miniRT path/to/scene.rt

Interact with the rendered window:
Press ESC to close the window and quit the program.
Click the red cross on the window's frame to close the window and quit the program.
