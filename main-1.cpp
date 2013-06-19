/*
* Eternity Intro
*
* Jon Vlachoyiannis
* 8/12/2005
*/

#include <stdio.h>

#define ALLEGRO_STATICLINK  
#define USE_CONSOLE 
#include <allegro.h>

#define NUMOFSNOW	500		// number of snowflakes

typedef struct {
	int x, y;
	int layer;
}particles_t;

particles_t Snow[NUMOFSNOW];

void InitSnow()
{
	for (int i=0; i < NUMOFSNOW; i++)
	{
		Snow[i].x = rand() % 320;
		Snow[i].y = rand() % 200;
		Snow[i].layer = rand() % 3;			// number of layers
	}
}

void DrawSnow()
{
	for (int i=0; i < NUMOFSNOW; i++)
		putpixel(screen, Snow[i].x, Snow[i].y, Snow[i].layer * 2 + 20);
}

void UpdateSnow()
{
	for (int i=0; i < NUMOFSNOW; i++)
	{
		Snow[i].y += Snow[i].layer;		// higher layer moves faster
		Snow[i].layer = rand() % 3;			// number of layers

		if ( Snow[i].y > 199 )
			Snow[i].y = 0;
		
		Snow[i].x = (Snow[i].x + (2 - rand()%4)) % 320;		// move left right but always between 320
	}
}

int main()
{
	allegro_init();
	install_keyboard();

	set_color_depth(8);

	//if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 320, 200, 0, 0)<0)
	if (set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 320, 200, 0, 0)<0)
	{
		set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
		allegro_message("Failed to initialize video mode\n %s\n",allegro_error);
	}

	InitSnow();

	while ((!key[KEY_ESC])&&(!key[KEY_SPACE]))
	{

		UpdateSnow();
		clear_bitmap(screen);
		DrawSnow();
		vsync();
	}
	

	return 1;
}
END_OF_MAIN();