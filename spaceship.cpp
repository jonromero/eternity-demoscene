/*
* Flame/smoke effects on spaceship
*
* Jon Vlachoyiannis
* 1/1/2006
*/

#include <allegro.h>
#include "spaceship.h"

#define NUMOFFLAMES	1000			

flame_t	Flames[NUMOFFLAMES];

void DrawSmoke(int x_space, int y_space, float angle, BITMAP *offscreen)
{
	int i,j;
	int x_layer1 = x_space + 44,
		y_layer1 = y_space + 10;

	for ( i = x_space + 40; i < x_layer1; i++ )							// grey
		for ( j = y_space + 20; j > y_layer1; j--)
			putpixel(offscreen, i-rand()%5, j, 20);	

	for ( i = x_space + 45; i < x_layer1+5; i++ )						//yellow
		for ( j = y_space + 20; j > y_layer1 ; j--)
			putpixel(offscreen, i-rand()%5, j, makecol(255,255,0));	
	
	for ( i = x_space + 50; i < x_layer1+15; i++ )					//flame
		for ( j = y_space + 20; j > y_layer1 ; j--)			
			putpixel(offscreen, i-rand()%5, j, 40);	
}

void InitFlames(int x_pos, int y_pos)
{
	for ( int i = 0; i < NUMOFFLAMES; i++ )
	{
		Flames[i].x = x_pos + 50 + rand()%5;
		Flames[i].y = y_pos + 14 + (-2 + rand()%5);
		Flames[i].color = rand() % 3;	

	}
}

void UpdateFlames(BITMAP *offscreen, int x_pos, int y_pos)
{
	for ( int i = 0; i < NUMOFFLAMES; i++ )
	{
		Flames[i].x += rand()%8;
		Flames[i].y += (-2 + rand()%5);
		//Flames[i].color--;

		if ( rand()%5 == 1 )						// don't destroy every flame
			if ( Flames[i].x > (x_pos + 60) )
			{
				Flames[i].x = x_pos + 50 - rand()%15;
				Flames[i].y = y_pos + 14 + (-2 + rand()%5);
			}

		putpixel(offscreen, Flames[i].x, Flames[i].y, Flames[i].color * 2 + 20);	
	}
}


void DrawPlane(BTMAP *bmp, int x_pos, int y_pos, float angle, float z_x, float z_y, BITMAP *offscreen)
{
	int x, y;
	int fx_pos = x_pos,
		fy_pos = y_pos;

	/*
	* Rotate X
	*/ 
	for( y = 0; y < bmp->height; y++ )
	{
		for( x = 0; x < bmp->width; x++ )
		{			
//			fx_pos = (x * cos(angle) + y * sin(angle))/sin(z_x);
//			fy_pos = (y * cos(angle) - x * sin(angle))/sin(z_y);

			putpixel(offscreen, x+x_pos, y+y_pos, bmp->data[y*bmp->width +x]);
		}
	}
}


