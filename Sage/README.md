## Introduction

Sage Lite is a simple graphics framework to generate rect and shapes...


### Requirements
This framework requires the following application or framework to be installed:
1. Visual Studio 2022
2. CMake


### Instruction
As this project depend on a generated solution by CMAKE, it require the following files to be generated.

1. Make a directory at the root folder, name it build and navigate into it.
```batch
mkdir build
cd build
```
2. Generate the solution file using the `CMakeLists.txt` at the root folder. 
3.   Note that the visual studio version is required in the following format:
```
Visual Studio 2019 - Version 16
Visual Studio 2022 - Version 17
```
To generate solution through CMakeLists use the following command in the newly created build folder:
```batch
REM The format are as follows
REM cmake -G "Visual Studio [Version Number] [Year]"
cmake -G "Visual Studio 17 2022" ..
```
This generate a sln file targeting VS 2022 using the CMakeList at the root folder.

Once generated , you may edit the project by opening the generated solution file in VS 2022.


### Batch Files

You can directly generate the solutions through the batch file provided for:
1. Visual Studio 2022
2. Visual Studio 2019
