#include "include.h"

/*A parte de carregamento de imagem .bmp foi retirada de um tutorial da internet. A fonte e os créditos constam
abaixo: */
/*
* ---------------- www.spacesimulator.net --------------
*   ---- Space simulators and 3d engine tutorials ----
*
* (c) Copyright 2002 Damiano Vitulli <info@spacesimulator.net>
* ALL RIGHTS RESERVED
* Tutorial 3: 3d engine - Texture mapping with OpenGL!
* Include File: texture.cpp
*/
/*
Linux port by Panteleakis Ioannis
mail: pioann@csd.auth.gr
*/

int num_texture=-1;
/**********************************************************
*
* FUNCTION LoadBitmap(char *)
*
* This function loads a bitmap file and return the OpenGL reference ID to use that texture
*
*********************************************************/
int LoadBitmap(char *filename)
{
  FILE * file;
  char temp;
  long i;

  BITMAPINFOHEADER infoheader;

  num_texture++; // The counter of the current texture is increased

  if( (file = fopen(filename, "rb"))==NULL) return (-1); // Open the file for reading

  fseek(file, 18, SEEK_CUR);  /* start reading width & height */
  fread(&infoheader.biWidth, sizeof(int), 1, file);

  fread(&infoheader.biHeight, sizeof(int), 1, file);

  fread(&infoheader.biPlanes, sizeof(short int), 1, file);
  if (infoheader.biPlanes != 1) {
    printf("Planes from %s is not 1: %u\n", filename, infoheader.biPlanes);
    return 0;
  }

  // read the bpp
  fread(&infoheader.biBitCount, sizeof(unsigned short int), 1, file);
  if (infoheader.biBitCount != 24) {
    printf("Bpp from %s is not 24: %d\n", filename, infoheader.biBitCount);
    return 0;
  }

  fseek(file, 24, SEEK_CUR);

  // read the data.
  infoheader.data = (char *) malloc(infoheader.biWidth * infoheader.biHeight * 3);
  if (infoheader.data == NULL) {
    printf("Error allocating memory for color-corrected image data\n");
    return 0;
  }

  if ((i = fread(infoheader.data, infoheader.biWidth * infoheader.biHeight * 3, 1, file)) != 1) {
    printf("Error reading image data from %s.\n", filename);
    return 0;
  }

  for (i=0; i<(infoheader.biWidth * infoheader.biHeight * 3); i+=3) { // reverse all of the colors. (bgr -> rgb)
    temp = infoheader.data[i];
    infoheader.data[i] = infoheader.data[i+2];
    infoheader.data[i+2] = temp;
  }


  fclose(file); // Closes the file stream


  glBindTexture(GL_TEXTURE_2D, num_texture); // Bind the ID texture specified by the 2nd parameter

  // The next commands sets the texture parameters
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // If the u,v coordinates overflow the range 0,1 the image is repeated
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // The magnification function ("linear" produces better results)
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST); //The minifying function

  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); // We don't combine the color with the original surface color, use only the texture map.

  // Finally we define the 2d texture
  glTexImage2D(GL_TEXTURE_2D, 0, 3, infoheader.biWidth, infoheader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, infoheader.data);

  // And create 2d mipmaps for the minifying function
  gluBuild2DMipmaps(GL_TEXTURE_2D, 3, infoheader.biWidth, infoheader.biHeight, GL_RGB, GL_UNSIGNED_BYTE, infoheader.data);

  free(infoheader.data); // Free the memory we used to load the texture

  return (num_texture); // Returns the current texture OpenGL ID
}

/*As texturas dos objetos foram retiradas desses links: https://www.solarsystemscope.com/textures/
http://planetpixelemporium.com*/

void loadTexture(){
  // Habilita o uso de texturas
  glEnable (GL_TEXTURE_2D );
  glEnable(GL_COLOR_MATERIAL);
  glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );
  glGenTextures (11, textura);
  glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
  //carregar texturas
  textura[0] = LoadBitmap("./textura/sol.bmp");
  textura[1] = LoadBitmap("./textura/terra.bmp");
  textura[2] = LoadBitmap("./textura/lua.bmp");
  textura[3] = LoadBitmap("./textura/marte.bmp");
  textura[4] = LoadBitmap("./textura/jupiter.bmp");
  textura[5] = LoadBitmap("./textura/saturno.bmp");
  textura[6] = LoadBitmap("./textura/mercurio.bmp");
  textura[7] = LoadBitmap("./textura/venus.bmp");
  textura[8] = LoadBitmap("./textura/urano.bmp");
  textura[9] = LoadBitmap("./textura/netuno.bmp");
  textura[10] = LoadBitmap("./textura/plutao.bmp");
  textura[11] = LoadBitmap("./textura/anelsaturno.bmp");
  textura[12] = LoadBitmap("./textura/titansaturno.bmp");
  textura[13] = LoadBitmap("./textura/iojupiter.bmp");
  textura[14] = LoadBitmap("./textura/luaurano.bmp");
  textura[15] = LoadBitmap("./textura/tritaonetuno.bmp");
  textura[16] = LoadBitmap("./textura/caronte.bmp");
  textura[17] = LoadBitmap("./textura/luamarte.bmp");
}
