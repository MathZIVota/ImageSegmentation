//#include <iostream>

#include "stb_image.h"
#include "stb_image_write.h"

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int main() {

  // строка, путь к файлу
  char *inputPath = "input.png";
  char *outputPath = "output.png";
  int iw, ih, n = 3, k, i;
  // char *pixel;
  unsigned char *odata;
  unsigned char *idata;
  unsigned char *MyImage;

  idata = stbi_load(inputPath, &iw, &ih, &n, 3);
  if (idata == NULL) {
    printf("ERROR: can't read file %s\n", inputPath);
    return 1;
  }

  MyImage = (unsigned char *)malloc(ih * iw * sizeof(unsigned char));
  k = 0;
  for (i = 0; i < ih * iw * n; i = i + n) {
    MyImage[k] =
        11 / 32 * idata[i] + 16 / 32 * idata[i + 1] + 5 / 32 * idata[i + 2];
    k++;
  }

  odata = (unsigned char *)malloc(iw * ih * n);

  // записываем картинку
  stbi_write_png(outputPath, iw, ih, n, odata, 0);

  stbi_image_free(idata);
  stbi_image_free(odata);
  return 0;
}