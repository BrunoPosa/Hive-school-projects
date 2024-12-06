# MiniRT - Raytracing Image Generator
*This project was a group project. Co-creator:* [Sheree Morphett](https://github.com/ShereeMorphett)

## Description

MiniRT is a raytracing program written in C that generates images representing scenes with simple geometric objects and their own lighting systems. The goal of this project is to familiarize developers with the Raytracing protocol and basic Computer Graphics concepts.
The program takes a scene description file with the ".rt" extension as its first argument, which defines various elements in the scene, such as ambient lighting, cameras, lights, spheres, planes, and cylinders. The images are displayed in a window using the miniLibX graphics library, and the program supports resizing and fluid window management.

 <img src="imgs/teapot.png" width="48%" align="center"> <img src="imgs/coloured_lights.png" width="48%" align="center">

 
## Implementation

### Soft Skills

This project was a team effort, and successful completion required effective GitHub management and issue solving. We effectively utilized GitHub to collaborate on the code, manage tasks, and track progress. Our communication skills played a crucial role in coordinating efforts and ensuring a smooth development process.

### Technical Skills

The implementation of MiniRT involved a variety of technical skills:

- **C Programming:** The entire project was implemented in the C programming language, adhering to the Norm guidelines provided.
- **Memory Management:** Careful memory allocation and deallocation were crucial to avoid memory leaks and unexpected program behavior.
- **MiniLibX:** We used the MiniLibX library to manage the window and display the generated images.
- **Raytracing Algorithm:** The core of the project involved implementing the raytracing algorithm to calculate intersections, shadows, and ambient lighting.
- **Parsing:** We developed a parser to read and interpret the scene description file in the ".rt" format.
- **Mathematics:** Mathematical calculations were essential for handling rotations, translations, and geometric properties of objects.

#### Bonus
- **Diffuse Reflections:** Materials can be reflective and their surroundings can be visible on their surface.
- **Blinn-Phong Reflection Model:** We implemented the Phong reflection model for specular reflections.
- **Textures & Normalmappoing:** We handle the application of pictures as well as adding apparent physical textures to different objects.
- **Procedurally Generated Textures:** A prodecurally generated checkerboard or brick-wall textutue can be applied.
- **3D-Meshes from `.obj` Files:** Object files as you generate them in eg. Blender can be rendered monochromatically as well.

  <img src="imgs/complex_cone.png" width ="48%" align="right"> <img src="imgs/colour_disruption.png" width ="48%" align="center">

<br>

### Prerequisites

Before you start, ensure you have the following:

- `gcc` (GNU Compiler Collection)
- `make`
- A compatible C library

The provided repo comes with the Minilibx library for both Linux and OSx systems. Unfortunately, the school library does not come for Windows systems.

### Installation

Clone this repository to your local machine:

```bash
git clone https://github.com/dorianjagusch/miniRT.git
cd miniRT
```

To compile MiniRT run the provided Makefile:

```bash
make
```

This will generate the "miniRT" and "miniRT_bonus" executable, ready to be used.

<img src="imgs/textured_sphere.png" width = "48%" align="left">  <img src="imgs/multicolour_sphere.png" width="48%" align="center">

<br> 

## Usage

To use MiniRT, simply run the compiled executable with a scene description file as its argument:

```bash
./miniRT <scene.rt>
```
```bash
./miniRT_bonus <scene.rt>
```

Exemplary scenes can be found in the testfiles directory. Use `./miniRT testfiles/<scene.rt>` to check them out.

## Future steps
 - Anti-aliasing
 - Add transparency of objects
 - Allow different materials
 - Global illumination
 - Camera movement
 - Move the rendering to the GPU


 <img src="imgs/specular_spheres.png" width = "100%" align="left">
