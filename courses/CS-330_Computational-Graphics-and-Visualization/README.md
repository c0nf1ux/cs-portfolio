# CS-330: Computational Graphics and Visualization

## Course Overview

This repository contains coursework for **CS-330: Computational Graphics and Visualization** at Southern New Hampshire University (SNHU). The course provides a comprehensive introduction to 3D graphics programming using modern OpenGL, focusing on real-time rendering techniques, shader programming, and interactive 3D scene development.

## Course Description

CS-330 explores the fundamental concepts of computer graphics and visualization, covering the complete graphics pipeline from 3D model space to 2D screen rendering. Students learn to create interactive 3D applications using industry-standard tools and techniques, implementing advanced features such as texture mapping, lighting models, camera controls, and shader programming.

## Topics Covered

- **OpenGL Graphics Pipeline**: Understanding the modern programmable rendering pipeline
- **3D Graphics Programming**: Creating and manipulating 3D objects in virtual space
- **Texture Mapping**: Applying 2D images to 3D surfaces for realistic rendering
- **Lighting Systems**: Implementing Phong lighting model with ambient, diffuse, and specular components
- **Camera Systems**: Developing interactive camera controls for scene navigation
- **Shader Programming**: Writing custom vertex and fragment shaders in GLSL
- **3D Transformations**: Translation, rotation, scaling, and matrix operations
- **Mesh Generation**: Building complex 3D shapes from primitive geometries
- **Material Properties**: Defining surface characteristics for realistic rendering

## Languages & Tools

### Programming Languages
- **C++**: Primary development language for graphics applications
- **GLSL** (OpenGL Shading Language): Shader programming for vertex and fragment processing

### Graphics Libraries & Frameworks
- **OpenGL 4.6**: Core graphics API for rendering
- **GLEW** (OpenGL Extension Wrangler): Managing OpenGL extensions
- **GLFW**: Window creation and input handling
- **GLM** (OpenGL Mathematics): Math library for graphics transformations
- **stb_image**: Image loading library for texture mapping

### Development Environment
- **Visual Studio**: IDE for C++ development and debugging
- **Windows Platform**: Primary development platform

## Projects & Assignments

### Final Project Submission (7-1_FinalProject_Submission)
The capstone project featuring a complete 3D scene with advanced rendering techniques:

**Project Structure:**
```
7-1_FinalProject_Submission/
├── Source/
│   ├── MainCode.cpp           # Application entry point and OpenGL initialization
│   ├── SceneManager.cpp/.h    # Scene creation and rendering management
│   └── ViewManager.cpp/.h     # Camera and viewport management
├── 3DShapes/
│   └── ShapeMeshes.cpp/.h     # Primitive shape generation (cylinders, spheres, etc.)
├── Utilities/
│   ├── ShaderManager.cpp/.h   # GLSL shader loading and management
│   ├── camera.h               # Camera class for scene navigation
│   ├── shaders/
│   │   ├── vertexShader.glsl  # Vertex transformation shader
│   │   └── fragmentShader.glsl # Lighting and texture fragment shader
│   └── stb_image.h            # Image loading library
└── Debug/
    └── *.glsl                 # Compiled shader files
```

**Key Features:**
- Multiple 3D primitive shapes (cylinders, spheres, boxes, planes, etc.)
- Multi-light system supporting up to 4 light sources
- Phong lighting model with ambient, diffuse, and specular components
- Texture mapping with UV coordinate generation
- Interactive camera controls (WASD movement, mouse look)
- Material system with customizable properties (ambient, diffuse, specular, shininess)

### Milestone Projects
- **2-2_Assignment**: Early 3D shape creation and basic rendering
- **5-2 Project**: Camera implementation and scene navigation
- **6-2_Assignment**: Advanced lighting techniques
- **7-1_FinalProject_Lighting**: Multi-light source implementation
- **7-1 Final Project Milestone Texture Mapping**: Texture application to 3D objects

### Design Documentation
- **3D Scene Proposal**: Initial project concept and planning
- **3D Scene Design Decisions**: Final design rationale and implementation choices
- **8-2 CS330 Final Module**: Course reflection and learning outcomes

### Libraries
The `libraries/` directory contains all necessary OpenGL libraries and dependencies:
- **CS330Content/Libraries/**: GLEW, GLFW, GLM, and GLAD libraries
- Pre-compiled binaries and headers for Windows development

## Project Highlights

### Final 3D Scene Implementation

The final project demonstrates mastery of the following concepts:

1. **Advanced Mesh Generation**
   - Custom shape creation using vertex arrays and element buffers
   - Procedural generation of complex geometries
   - Efficient vertex data organization with position, normal, and texture coordinates

2. **Sophisticated Lighting System**
   - Multiple concurrent light sources (up to 4 lights)
   - Phong reflection model implementation
   - Per-fragment lighting calculations in GLSL
   - Adjustable light properties (position, color, intensity, focal strength)

3. **Texture Mapping Pipeline**
   - UV coordinate generation for primitive shapes
   - Image loading and texture binding
   - Texture sampling in fragment shader
   - Material/texture blending

4. **Interactive Camera Controls**
   - First-person camera navigation
   - Smooth movement with WASD keys
   - Mouse-based view rotation
   - Perspective and orthographic projection modes

5. **Shader Programming**
   - Custom GLSL vertex shader for transformations
   - Fragment shader with lighting calculations
   - Uniform variable management
   - Material and light structure definitions

## Key Concepts

### 3D Transformations
- **Model Matrix**: Object positioning, rotation, and scaling in world space
- **View Matrix**: Camera transformation for scene viewing
- **Projection Matrix**: Perspective or orthographic projection to 2D viewport
- **MVP Pipeline**: Model-View-Projection transformation chain

### Shader Programming
- **Vertex Shader**: Transforms vertices from object space to clip space
- **Fragment Shader**: Calculates per-pixel colors with lighting and textures
- **Uniform Variables**: Passing data from CPU to GPU
- **Attribute Variables**: Per-vertex data (position, normal, UV)

### Rendering Pipeline
1. Vertex specification and buffer setup
2. Vertex shader transformation
3. Primitive assembly and rasterization
4. Fragment shader color calculation
5. Depth testing and frame buffer output

## Semester & Year

**Fall 2025** (November - December 2025)
- Course Duration: 8-week accelerated term
- Final Project Submission: December 14, 2025

## Portfolio Version

A refined, portfolio-ready version of the final project is available at:

**~/cs-portfolio/projects/CS330-Portfolio/**

This version includes:
- Cleaned and optimized codebase
- Professional documentation
- Enhanced visual presentation
- Detailed design decisions document

## Learning Outcomes

Upon completion of this course, the following competencies were developed:

- Proficiency in modern OpenGL graphics programming
- Understanding of the 3D graphics rendering pipeline
- Ability to implement real-time lighting and shading algorithms
- Competence in GLSL shader development
- Skills in 3D scene composition and design
- Knowledge of graphics optimization techniques
- Experience with professional graphics development workflows

## Additional Resources

- **Screenshots**: Multiple progress screenshots documenting development iterations
- **Code Archives**: Zipped submissions for each milestone (2-2, 6-2, 7-1)
- **Discussion Posts**: Module discussions on graphics concepts and techniques

---

**Course Instructor**: Brian Battersby, SNHU Computer Science
**Student**: Heath Davis
**Institution**: Southern New Hampshire University
**Course Code**: CS-330
