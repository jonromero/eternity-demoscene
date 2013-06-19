/*
* Bitmap functions
* Published under GPL 2.0 
*
* Original code written by David Brackeen     
* http://www.brackeen.com/home/vga/         
*
* Code changes by Jon Vlachoyiannis
* 29/12/2005
*/

#include <stdio.h>
#include <stdlib.h>
#include "Bitmap.h"

/*
* TODO : Rewrite to read the whole bitmap once-shot
*/
int LoadBitmap(const char *filename, BTMAP *b)
{
	FILE *fp;
	long index;
	short int num_colors;
	int x;

	/* open the file */
	if ((fp = fopen(filename,"rb")) == NULL)
	{
		//printf("Error opening file %s.\n",file);
		return -1;
	}

	/* check to see if it is a valid bitmap file */
	if (fgetc(fp)!='B' || fgetc(fp)!='M')
	{
		fclose(fp);
		//printf("%s is not a bitmap file.\n",file);
		return -2;
	}

	/* read in the width and height of the image, and the
		 number of colors used; ignore the rest */
	fskip(fp,16);
	fread(&b->width, sizeof(short int), 1, fp);
	fskip(fp,2);
	fread(&b->height,sizeof(short int), 1, fp);
	fskip(fp,22);
	fread(&num_colors,sizeof(short int), 1, fp);
	fskip(fp,6);

	/* assume we are working with an 8-bit file */
	if (num_colors==0) num_colors=256;


	/* try to allocate memory */
	if ((b->data = (char *) malloc((short int)(b->width*b->height))) == NULL)
	{
		fclose(fp);
		//printf("Error allocating memory for file %s.\n",file);
		return -3;
	}

	/* Ignore the palette information for now.
		 See palette.c for code to read the palette info. */
	fskip(fp,num_colors*4);

	/* read the bitmap */
	for(index=(b->height-1)*b->width;index>=0;index-=b->width)
		for(x=0;x<b->width;x++)
		b->data[(short int)index+x]=(char)fgetc(fp);

	fclose(fp);

	return 1;
}



void fskip(FILE *fp, int num_bytes)
{
   int i;
   for (i=0; i<num_bytes; i++)
      fgetc(fp);
}

