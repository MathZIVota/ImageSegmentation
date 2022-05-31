//#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"



int main() {
  char *inputPath = "input.png";
  char *outputPath = "output.png";
  int iw, ih, n, k, i, flag;
  
  unsigned char *odata;
  unsigned char *idata;
  unsigned char *image_ton;
  unsigned char *new_image;
  
  idata = stbi_load(inputPath, &iw, &ih, &n, 0);
  if (idata == NULL) {
    printf("ERROR: can't read file %s\n", inputPath);
    return 1;
    }

  image_ton = (unsigned char *)malloc(ih * iw * sizeof(unsigned char));
  k = 0;
  for (i = 0; i < ih * iw * n; i = i + n) {
    image_ton[k] = 11 / 32 * idata[i] + 16 / 32 * idata[i + 1] + 5 / 32 * idata[i + 2];
    k++;
    }
  
  new_image = (unsigned char*)malloc(ih*iw*sizeof(unsigned char));

  

  odata = (unsigned char *)malloc(iw * ih * n);
  if (odata == NULL) {
    printf("ERROR: can't write file %s\n", outputPath);
    return 1;
    }


  printf("%d, %d, %d\n",iw,ih,n);

  for (i = 0; i < ih * iw; i++) {
    odata[i*n]=idata[i*n]+100;
    odata[i*n+1]=idata[i*n+1]-100;
    odata[i*n+2]=idata[i*n+2];
    if(n==4) odata[i*n+3]=idata[i*n+3];
    }

  // записываем картинку
  stbi_write_png(outputPath, iw, ih, n, odata, 0);
  free(image_ton);
  free(odata);
  stbi_image_free(idata);
  return 0;
}