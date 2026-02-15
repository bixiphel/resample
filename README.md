Version control and repository available at https://github.com/bixiphel/resample

Bilinear interpolation algorithm implementation was written in C using provided project files. Program takes in a greyscale PGM image and a floating-point type scaling factor and creates a greyscale PGM image that is scaled according to the scaling factor. 

General Notes 
- Implementation supports scaling upwards and downwards
- Ensures a minimum size of 1x1 in the case that the specified scaling factor is too small (but still larger than 0)
- Scaling factors that are zero (0) or negative are caught and return exit code 1, indicating an error 
- Implementation includes no calls to third-party libraries or built-in functions other than libraries already specified in the source code 

Project Specific Notes
- Code was written and compiled running Ubuntu 24.04 through WSL on Windows 11
    - Some commits were pushed through a SSH connection. Such commits are registered to user "sydney"
- Compilation was done using the GNU Compiler Collection (gcc) version 13.3.0
- Bash instructions are included below, machine-specific commands may be different
- Two examplar output images are attached below. The corresponding scaling factors are **0.40** and **2.23**, and labeled in `~/proj_1/sample images` as `output1.pgm` and `output2.pgm` respectively. PNG versions of each file are also included in the same folder.
<img width="151" height="156" alt="output1" src="https://github.com/user-attachments/assets/63490a74-6865-4a0b-a53e-ffad8f977c24" />
<img width="843" height="867" alt="output2" src="https://github.com/user-attachments/assets/1a99f0fa-b978-45c5-b07d-c37c6fa11577" />

---

- Compile instruction: `gcc ReadWritePGM.c -o resample`
- Execution instruction: `./resample <input PGM> <output PGM> <scale>`
