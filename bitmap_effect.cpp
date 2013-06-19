/*
* Bitmap effects
*
* Jon Vlachoyiannis
* 1/1/2006
*/

#include <math.h>
#include "bitmap_effect.h"

void DrawBitmap(BTMAP *bmp, int x_pos, int y_pos, float *angle, float *zx, float z_y, int *isCircled, int *isNormal, BITMAP *offscreen)
{
	int x, y;
	float z_x = *zx;
	float fx_pos = 0,
		  fy_pos = 0;

	/*
	* Effect
	*/ 
	for( y = 0; y<bmp->height; y++ )
	{
		for( x = 0; x<bmp->width; x++ )
		{						
			//if ( rand()%3 != 1)
			//	fx_pos = ((x-bmp->width/2) * cos(*angle) + (y-bmp->height/2) * sin(*angle))/sin(z_x);
			//else
				fx_pos = 30+x;//((x-bmp->width/2) * cos(*angle) + (y-bmp->height/2) * cos(*angle))/sin(z_x);

			if ( (int)fx_pos == x_pos && *isCircled )
			{
				*isCircled = 0;
				*isNormal = 1;
			}
			
			fy_pos = ((y-bmp->height/2) * cos(*angle) - (x-bmp->width/2) * sin(*angle))/sin(z_y);
			//fy_pos = (y- (x-bmp->width/2) * sin(angle))/sin(z_y);
			putpixel(offscreen, (fx_pos+x_pos), (fy_pos+y_pos), bmp->data[y*bmp->width +x]);
		}
	}	

	if ( *zx < 15.5 )
		*zx = *zx + 36;
	
	if ( *angle > 36 )
	{
		*angle = 1;
		*isCircled = 1;
	}			

}

void NormalBitmap(BTMAP *bmp, int x_pos, int y_pos, float *angle, float *zx, float z_y, int *isNormal, BITMAP *offscreen)
{
	int x, y;
	float fx_pos = 0,
		  fy_pos = 0;

	float z_x = *zx;

	/*
	* Effect
	*/ 
	for( y = 0; y<bmp->height; y++ )
	{
		for( x = 0; x<bmp->width;x++ )
		{					
			fx_pos = 2.5*((x-bmp->width/2) * cos(*angle) + (y-bmp->height/2) * sin(*angle))/sin(-z_x);
			fy_pos = 2.5*((y-bmp->height/2) * cos(*angle) - (x-bmp->width/2) * sin(*angle))/sin(-z_y);
			putpixel(offscreen, (fx_pos+x_pos), (fy_pos+y_pos), bmp->data[y*bmp->width +x]);
		}
	}
	
	if ( *angle > 36 )
	{
		*angle = 1;
		*isNormal = 0;
	}			
		
	if (*zx > -20 )
		*zx = *zx - 6;	
}

 
