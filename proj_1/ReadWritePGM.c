/********************************************************
***IMPORTANT NOTE***
If you have problems with the provided sample code,
part of the reason might be due to the function "fopen".
Please try changing "r/w" to "rb/wb" or the other way
when you use this function.
*********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <malloc.h>  
#include <memory.h>

#define max(x, y) ((x>y) ? (x):(y))
#define min(x, y) ((x<y) ? (x):(y))

int xdim;
int ydim;
int maxraw;
unsigned char *image;

void ReadPGM(FILE*);
void WritePGM(FILE*);

float SCALE;

int main(int argc, char **argv)
{
  FILE *fp;

  if (argc != 4){
    printf("Usage: MyProgram <input_ppm> <output_ppm> <scale> \n");
    printf("       <input_ppm>: PGM file \n");
    printf("       <output_ppm>: PGM file \n");
    printf("       <scale>: Scaling factor \n");
    exit(0);              
  }

  SCALE = atof(argv[3]);
  printf("Scaling factor: %f\n", SCALE);

  /* begin reading PGM.... */
  printf("begin reading PGM.... \n");
  if ((fp=fopen(argv[1], "rb"))==NULL){
    printf("read error...\n");
    exit(0);
  }
  ReadPGM(fp);

  // your application here 

  // Checks if the scaling factor is valid in case scaling factor is too small or negative
  if(SCALE <= 0.0F) {
    printf("Scaling factor must be a nonzero positive floating value.\n");
    exit(1);
  }

  // Calculate dimensions of the new image and allocate space in memory. Also ensures a minimum size instead of seg faulting 
  int mdim = max(1, (int) (xdim * SCALE + 0.5f));    // The scaled x-axis
  int ndim = max(1, (int) (ydim * SCALE + 0.5f));    // The scaled y-axis
  unsigned char *new_image = (unsigned char*) malloc(mdim * ndim);    // Instantiated scaled image buffer 

  // Loop over every pixel in the output image and calculate the new intensities based on the input image
  for(int n = 0; n < ndim; n++) {
    for(int m = 0; m < mdim; m++) {
      // Determine where scaled pixels map back to the source image's pixels
      float src_x = m / SCALE;
      float src_y = n / SCALE;

      // Find neighboring pixels' locations 
      int x0 = (int) src_x;
      int x1 = (int) min(x0 + 1, xdim - 1);
      int y0 = (int) src_y;
      int y1 = (int) min(y0 + 1, ydim - 1);

      // Define weights for the horizontal and vertical directions
      float w_x = src_x - x0;
      float w_y = src_y - y0;
  
      // Find the intensities of the neighboring pixels
      unsigned char p00 = image[y0*xdim + x0];
      unsigned char p10 = image[y0*xdim + x1];
      unsigned char p01 = image[y1*xdim + x0];
      unsigned char p11 = image[y1*xdim + x1];

      // Calculate the intensity of the pixel in the scaled image using bilinear interpolation  
      float value = p00 * (1 - w_x) * (1 - w_y) + p10 * (w_x)*(1 - w_y) + p01 * (1 - w_x) * (w_y) + p11 * (w_x) * (w_y);
      
      // Write to the output image's buffer
      new_image[n * mdim + m] = (unsigned char)(value + 0.5F); 
    }
  }

  // Replace original image buffer with output image's buffer (to avoid changing other functions below)
  free(image);
  image = new_image;
  xdim = mdim;
  ydim = ndim; 

  /* Begin writing PGM.... */
  printf("Begin writing PGM.... \n");
  if ((fp=fopen(argv[2], "wb")) == NULL){
     printf("write pgm error....\n");
     exit(0);
   }
  WritePGM(fp);

  free(image);

  return (1);
}

void ReadPGM(FILE* fp)
{
    int c;
    int i,j;
    int val;
    unsigned char *line;
    char buf[1024];


    while ((c=fgetc(fp)) == '#')
        fgets(buf, 1024, fp);
     ungetc(c, fp);
     if (fscanf(fp, "P%d\n", &c) != 1) {
       printf ("read error ....");
       exit(0);
     }
     if (c != 5 && c != 2) {
       printf ("read error ....");
       exit(0);
     }

     if (c==5) {
       while ((c=fgetc(fp)) == '#')
         fgets(buf, 1024, fp);
       ungetc(c, fp);
       if (fscanf(fp, "%d%d%d",&xdim, &ydim, &maxraw) != 3) {
         printf("failed to read width/height/max\n");
         exit(0);
       }
       printf("Width=%d, Height=%d \nMaximum=%d\n",xdim,ydim,maxraw);

       image = (unsigned char*)malloc(sizeof(unsigned char)*xdim*ydim);
       getc(fp);

       line = (unsigned char *)malloc(sizeof(unsigned char)*xdim);
       for (j=0; j<ydim; j++) {
          fread(line, 1, xdim, fp);
          for (i=0; i<xdim; i++) {
            image[j*xdim+i] = line[i];
         }
       }
       free(line);

     }

     else if (c==2) {
       while ((c=fgetc(fp)) == '#')
         fgets(buf, 1024, fp);
       ungetc(c, fp);
       if (fscanf(fp, "%d%d%d", &xdim, &ydim, &maxraw) != 3) {
         printf("failed to read width/height/max\n");
         exit(0);
       }
       printf("Width=%d, Height=%d \nMaximum=%d,\n",xdim,ydim,maxraw);

       image = (unsigned char*)malloc(sizeof(unsigned char)*xdim*ydim);
       getc(fp);

       for (j=0; j<ydim; j++)
         for (i=0; i<xdim; i++) {
            fscanf(fp, "%d", &val);
            image[j*xdim+i] = val;
         }

     }

     fclose(fp);
}


void WritePGM(FILE* fp)
{
  int i,j;
  

  fprintf(fp, "P5\n%d %d\n%d\n", xdim, ydim, 255);
  for (j=0; j<ydim; j++)
    for (i=0; i<xdim; i++) {
      fputc(image[j*xdim+i], fp);
    }

  fclose(fp);
  
}
