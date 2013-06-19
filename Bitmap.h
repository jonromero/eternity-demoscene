#if !defined(_BITMAP_H_)
#define _BITMAP_H_

/*
* Bitmap functions
* Published under GPL 2.0 
*
* Jon Vlachoyiannis
* 25/12/2005
*/

#include <stdio.h>

typedef struct tagBTMAP              /* the structure for a bitmap. */
{
  short int width;
  short int height;
  char *data;
} BTMAP;

int LoadBitmap(const char *filename, BTMAP *b);
void fskip(FILE *fp, int num_bytes);

#endif