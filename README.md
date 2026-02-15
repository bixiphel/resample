Bilinear interpolation algorithm implementation was written in C using provided project files. Program takes in a greyscale PGM image and a floating-point type scaling factor and creates a greyscale PGM image that is scaled according to the scaling factor. 

General Notes 
- Implementation supports scaling upwards and downwards
- Ensures a minimum size of 1x1 in the case that the specified scaling factor is too small (but still larger than 0)
- Scaling factors that are zero (0) or negative are caught and return exit code 1, indicating an error 
- Implementation includes no calls to third-party libraries or built-in functions other than libraries already specified in the source code

Project Specific Notes
- Two examplar output images are attached below. The corresponding scaling factors are 0.40 and 2.23, and labeled in `~/proj_1/sample images` as `output1.pgm` and `output2.pgm` respectively. 
<img width="151" height="156" alt="output1" src="https://github.com/user-attachments/assets/63490a74-6865-4a0b-a53e-ffad8f977c24" />
<img width="843" height="867" alt="output2" src="https://github.com/user-attachments/assets/1a99f0fa-b978-45c5-b07d-c37c6fa11577" />


All source code was written and compiled on Ubuntu 24.04, system-specific compilation and execution instructions may vary; Linux-based instructions are provided below.
 
Compile instruction: gcc ReadWritePGM.c -o resample
Execution instruction: ./resample <input PGM> <output PGM> <scale>
