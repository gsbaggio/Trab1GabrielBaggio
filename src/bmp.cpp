// essa classe aqui serve pra carregar os arquivos .bmp, peguei de exemplo o que o pozzer deu pra nós pra nao fazer do zero

#include "Bmp.h"
#include <string.h>
#include <algorithm>
#include "gl_canvas2d.h"
#include <iostream>

Bmp::Bmp(const char *fileName)
{
   width = height = 0;
   data = NULL;
   if( fileName != NULL && strlen(fileName) > 0 )
   {
      load(fileName);
   }
   else
   {
      printf("Error: Invalid BMP filename");
   }
}

uchar* Bmp::getImage()
{
   return data;
}

void Bmp::setImage(uchar* img)
{
   this->data = img;
}

int Bmp::getWidth(void)
{
   return width;
}

void Bmp::setWidth(int w)
{
   this->width = w;
}

int Bmp::getHeight(void)
{
   return height;
}

void Bmp::setHeight(int h)
{
   this->height = h;
}

void Bmp::convertBGRtoRGB()
{
   unsigned char tmp;
   if( data != NULL )
   {
      for(int y=0; y<height; y++)
      for(int x=0; x<width*3; x+=3)
      {
         int pos = y * width * 3 + x;
         tmp = data[pos];
         data[pos] = data[pos+2];
         data[pos+2] = tmp;
      }
   }
}

void Bmp::load(const char *fileName)
{
   FILE *fp = fopen(fileName, "rb");
   if( fp == NULL )
   {
      printf("\nErro ao abrir arquivo %s para leitura", fileName);
      return;
   }

   printf("\n\nCarregando arquivo %s", fileName);

   fread(&header.type,      sizeof(unsigned short int), 1, fp);
   fread(&header.size,      sizeof(unsigned int),       1, fp);
   fread(&header.reserved1, sizeof(unsigned short int), 1, fp);
   fread(&header.reserved2, sizeof(unsigned short int), 1, fp);
   fread(&header.offset,    sizeof(unsigned int),       1, fp);

   fread(&info.size,        sizeof(unsigned int),       1, fp);
   fread(&info.width,       sizeof(int),                1, fp);
   fread(&info.height,      sizeof(int),                1, fp);
   fread(&info.planes,      sizeof(unsigned short int), 1, fp);
   fread(&info.bits,        sizeof(unsigned short int), 1, fp);
   fread(&info.compression, sizeof(unsigned int),       1, fp);
   fread(&info.imagesize,   sizeof(unsigned int),       1, fp);
   fread(&info.xresolution, sizeof(int),                1, fp);
   fread(&info.yresolution, sizeof(int),                1, fp);
   fread(&info.ncolours,    sizeof(unsigned int),       1, fp);
   fread(&info.impcolours,  sizeof(unsigned int),       1, fp);

   width  = info.width;
   height = info.height;
   bits   = info.bits;

   bytesPerLine = (3 * (width + 1) / 4) * 4;
   imagesize    = bytesPerLine * height;
   int delta    = bytesPerLine - (3 * width);

   printf("\nImagem: %dx%d - Bits: %d", width, height, bits);
   printf("\nbytesPerLine: %d", bytesPerLine);
   printf("\nbytesPerLine: %d", width * 3);
   printf("\ndelta: %d", delta);
   printf("\nimagesize: %d %d", imagesize, info.imagesize);

   if( header.type != 19778 ) {
      printf("\nError: Arquivo BMP invalido");
      getchar();
      exit(0);
   }

   if( info.compression != 0 )
   {
      printf("\nError: Formato BMP comprimido nao suportado");
      getchar();
      return;
   }
   if( bits != 24 )
   {
      printf("\nError: Formato BMP com %d bits/pixel nao suportado", bits);
      getchar();
      return;
   }

   if( info.planes != 1 )
   {
      printf("\nError: Numero de Planes nao suportado: %d", info.planes);
      getchar();
      return;
   }

   data = new unsigned char[3 * width * height];
   for(int i = 0; i < height; i++){
      int pos = i * bytesPerLine;
      fseek(fp, header.offset + pos, SEEK_SET);
      fread(data + width * 3 * i, sizeof(unsigned char), width * 3, fp);
   }

   fclose(fp);
}