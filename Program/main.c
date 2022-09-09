#define STBI_NO_SIMD
#define STB_IMAGE_IMPLEMENTATION
#include<math.h>
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

#define delta 100

int Exist(int i, int j, int iw, int ih){
  if(i < 0 || j < 0) return 0;
  if(i > ih - 1 || j > iw - 1) return 0;
  return 1;
}

void DFS(unsigned char* data, int i, int j, int w, int h, int num, unsigned int* component){
  int ind_j, ind_i;
  component[i*w+j] = num;
 
  ind_i = i+2;
  ind_j = j+2;
  if(Exist(ind_i , ind_j, w, h)){
    if(component[(ind_i )*w+ind_j] == 0){
      if(abs(data[(ind_i )*w+ind_j] - data[i*w+j]) < delta)
        DFS(data, ind_i , ind_j, w, h, num, component);
    }
  }
  
  ind_i = i-1;
  ind_j = j-2;
  if(Exist(ind_i , ind_j, w, h)){
    if(component[(ind_i )*w+ind_j] == 0){
      if(abs(data[(ind_i )*w+ind_j] - data[i*w+j]) < delta)
        DFS(data, ind_i , ind_j, w, h, num, component);
    }
  }
  
  ind_i = i-2;
  ind_j = j+2;
  if(Exist(ind_i , ind_j, w, h)){
    if(component[(ind_i )*w+ind_j] == 0){
      if(abs(data[(ind_i )*w+ind_j] - data[i*w+j]) < delta)
        DFS(data, ind_i , ind_j, w, h, num, component);
    }
  }
}


int main(){
  char* inputPath = "./input.png";
  char* outPath = "./output.png";
  
  int iw, ih, n;
  //=======================
  //Считывание картинки
  unsigned char *idata = stbi_load(inputPath, &iw, &ih, &n, 0);
  if (idata == NULL) {
        printf("ERROR: can't read file %s\n", inputPath );
        return 1;
  }
  //========================
  //Переход к одноканальному
  unsigned char *gray = (unsigned char *)malloc(iw * ih);
  for(int i=0; i<iw*ih; i++){
    gray[i] = (11*idata[i*n]+16*idata[i*n+1] + 5*idata[i*n+2])/32;
  }
  //==============================
  //==переход в ч-б-с картинке
  
  for(int i=0; i<iw*ih; i++){
    if(gray[i] < 95) { 
      gray[i] = 0;
    }
    
    if(gray[i] > 94 && gray[i] < 166) {
      gray[i] = 120;
    }
    
    if(gray[i] > 165) {
      gray[i] = 255;
    }
  }
  
  //==============================
  // ==========DFS========== 
  int color = 0;
  unsigned int*component = (unsigned int*)calloc(iw*ih, sizeof(unsigned int));
  for(int i=0; i<ih*iw; i++){
    if(component[i] == 0){
      color++;
      DFS(gray, i/iw, i%iw, iw, ih, color, component);
    }
  }
  //=========================================
  
  unsigned char* odata = (unsigned char *)malloc(iw * ih * n*sizeof(unsigned char));
  int coef = 0;
  for(int i=0; i<iw*ih; i++){ 
    coef = component[i]%80 + component[i]%50;
    odata[i*n] = 4*coef-70;
    odata[i*n+1] = 3*coef - 20;
    odata[i*n+2] = 6*coef + 80;
    if(n == 4) odata[i*n+3] = 255;
  }
  
  stbi_write_png(outPath, iw-2, ih-2, n, odata, iw*n);
  stbi_image_free(idata);
  stbi_image_free(odata);
  free(gray);
  free(component);
  return 0;
}
