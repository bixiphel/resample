Bilinear interpolation algorithm implementation was written in C using provided project files. Program takes in a greyscale PGM image and a floating-point type scaling factor and creates a greyscale PGM image that is scaled according to the scaling factor. 

General Notes 
- Implementation supports scaling upwards and downwards
- Ensures a minimum size of 1x1 in the case that the specified scaling factor is too small (but still larger than 0)
- Scaling factors that are zero (0) or negative are caught and return exit code 1, indicating an error 
- Implementation includes no calls to third-party libraries or built-in functions other than libraries already specified in the source code

Project Specific Notes
- Two examplar output images are attached below. The corresponding scaling factors are 0.70 and 1.23 respectively.  

All source code was written and compiled on Ubuntu 24.04, system-specific compilation and execution instructions may vary; Linux-based instructions are provided below.
 
Compile instruction: gcc ReadWritePGM.c -o resample
Execution instruction: ./resample <input PGM> <output PGM> <scale>
