/*
* Eternity Intro
*
* Jon Vlachoyiannis
* 8/12/2005
*/

#include <stdio.h>
#include <string.h>

#define ALLEGRO_STATICLINK  
#define USE_CONSOLE 
#include <allegro.h>

#include "spaceship.h"
#include "bitmap_effect.h"

#define NUMOFSNOW	5000			// number of snowflakes 
#define FONT_FILENAME	"triad-font.pcx"

typedef struct {
	int x;
	int y;
}Vector2d_t;

const Vector2d_t IStar[9] = 
{ 
	{ 15, 15 },
	{ 20, 5  },
	{ 25, 15 },
	{ 35, 20 },
	{ 25, 25 },
	{ 20, 35 },
	{ 15, 25 },
	{ 5,  20 },	
	{ 15, 15 }	
};

typedef struct {
	int x, y;
	int layer;	
}particles_t;

typedef struct {
	Vector2d_t Star[9];
	int x, y;
	float layer;
}flake_t;

particles_t Snow[NUMOFSNOW];
flake_t		Flakes[NUMOFSNOW];

MIDI *music;
BITMAP *offscreen;				// double buffering
BITMAP *fonts;
int font_width = 32,
	font_height = 32;
PALETTE fonts_pal;
int str_x = 320,
	str_y = 0;

int num_of_flakes = NUMOFSNOW;
/*
* Scaling
*/
void Scale( Vector2d_t *vec, int num_of_vects, float scale_x, float scale_y)
{
	int i;
	for (i = 0; i < num_of_vects; i++)
	{
		vec[i].x = vec[i].x * scale_x;	
		vec[i].y = vec[i].y * scale_y;		
	}	
} 

/*
* Translation
*/
void Translate( Vector2d_t *vec, int num_of_vects, float x_pos, float y_pos)
{
	int i;
	for (i = 0; i < num_of_vects; i++)
	{
		vec[i].x = vec[i].x + x_pos;	
		vec[i].y = vec[i].y + y_pos;		
	}	
} 

/*
* Translation
*/
void Translate2d( Vector2d_t *vec_in,  Vector2d_t *vec_out, int num_of_vects, float x_pos, float y_pos)
{
	int i;
	for (i = 0; i < num_of_vects; i++)
	{
		vec_out[i].x = vec_in[i].x + x_pos;	
		vec_out[i].y = vec_in[i].y + y_pos;		
	}	
} 

/*
* Rotate Z
*/ 
void RotateZ2d( Vector2d_t *vec_in,  Vector2d_t *vec_out, int num_of_vects, float angle)
{
	int i;
	for (i = 0; i < num_of_vects; i++)
	{
		vec_out[i].x = vec_in[i].x * cos(angle) - vec_in[i].y * sin(angle);
		vec_out[i].y = vec_in[i].y * cos(angle) + vec_in[i].x * sin(angle);		
	}	
} 


void InitSnow()
{
	for (int i=0; i < NUMOFSNOW; i++)
	{
		Snow[i].x = rand() % 320;
		Snow[i].y = rand() % 200;
		Snow[i].layer = rand() % 3;			// number of layers	
		
		for (int j=0; j < 9; j++)	
		{
			Flakes[i].Star[j].x = IStar[j].x;
			Flakes[i].Star[j].y = IStar[j].y;			
		}		
		
		Flakes[i].layer = (rand() % 4)/2 +0.2;	// layer-speed-scale
		
		Scale(Flakes[i].Star, 9, Flakes[i].layer, Flakes[i].layer);				
		Translate(Flakes[i].Star, 9, rand() % 320, rand()%200);								
	}
}

void InitFonts()
{
	fonts = load_bitmap(FONT_FILENAME, fonts_pal);
	//set_palette(fonts_pal);
}

void InitMusic()
{
	music = load_midi("med.mid");
	if (!music)
	{
		set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
		allegro_message("Failed to initialize music\n %s\n",allegro_error);
	}
}


void DrawSnow()
{
	for (int i=0; i < NUMOFSNOW; i++)
		putpixel(offscreen, Snow[i].x, Snow[i].y, Snow[i].layer * 2 + 20);
	
	for (int j=0; j < NUMOFSNOW/500; j++)	
		for (int i=0; i < 8; i++)
				//rectfill(offscreen, Flakes[j].Star[i].x, Flakes[j].Star[i].y , Flakes[j].Star[i+1].x , Flakes[j].Star[i+1].y, 255);
				line(offscreen, Flakes[j].Star[i].x, Flakes[j].Star[i].y , Flakes[j].Star[i+1].x , Flakes[j].Star[i+1].y, 255);
}

/* 
* figure out the character mapping for the letter.
* Credits and greets go to Barzoule for this mapping approach
* Hacked to work with pcx from Bitmap Font Builder ( texture size 512 )
* Jon Vlachoyiannis 
*/
void DrawChar(const char letter, int x, int y)
{
    int i, j;
	int letter_found;
	char *chrmap[] = {  " !\"#$%&'()*+,-./",
						"0123456789:;<=>?",
						"@ABCDEFGHIJKLMNO",
						"PQRSTUVWXYZ[\\]^_",
						"`abcdefghijklmno",
						"pqrstuvwxyz{|}**"
						};	
    
    // character map, as seen on triad-font.pcx.  
	letter_found = 0;
    for ( i = 0; i < 8; i++ )
	{

		for ( j = 0; j < strlen(chrmap[i]); j++ )
		{
			if ( (chrmap[i][j] == letter) )
				letter_found = 1;

			if ( letter_found )
				break;

		}

		if ( letter_found )
			break;
	}
		
 
    // Copy character from font_bmp to screen. (if we found a valid one)
    if (j<strlen(chrmap[i]))
      if ((x+font_width)>0 && x<320)     
      {
		  // verify that the x position is visible
        masked_blit(fonts, offscreen, j*font_width, i*font_height, x, y, font_width, font_height);
	  }
}

void DrawString(const char *string, int x, int y)
{  
    for (int i=0;i<strlen(string);i++)
        DrawChar(string[i], x+i*font_width, y);
}

const char  *RenderString(int str_num)
{
	const char *strings[] = { 
								{"Happy" },
								{"2006!!!"},
								{"This is"},
								{"my"},
								{"first"},
								{"intro !!!"},
								{"Evrything"},
								{"is done"},
								{"in"},
								{"realtime"},
								{"No"},
								{"OpenGL"},			
								{"No"},
								{"DirectX"},
								{"Just"},
								{"Maths"},
								{":)))"},
								{"Jon Vl."},
								{"Greetings"},
								{"to : "},
								{"Branca"},
								{"de Neve"},
								{"Polaris"},
								{"N.Dragons"},
								{"Inachus"},
								{"Neted"},
								{"Silence"},
								{"Koukos"},
								{"Jenny"},
								{"Spiros"},
								{"Friends"},
								{"AWMN"},
								{"and"},
								{"the"},
								{"greek"},
								{"denoscene"},
								{"Cya"},
								{"Around!!!"},
								{"Thnx"},
								{"4watching"},
								{"darksun @"},
								{"gmail.com"},
								{NULL}					// EOT
							};

	//DrawString("Happy", str_x--, 30 + 20 * sin(str_y++));			
	//DrawString("2006!", str_x, 80 + 20 * cos(str_y));			

	if (strings[str_num] == NULL )
		return NULL;

	DrawString(strings[str_num++], str_x--, 30 + 20 * sin(str_y++));			
	DrawString(strings[str_num], str_x, 80 + 20 * cos(str_y));	
}

/*
* By manipulating the layer (and also color)
* I can get via getpixel if a snow flake is stopped :)
* I could use a fall member, but then I should loop through the whole array
*/
void UpdateSnow()
{
	for (int i=0; i < NUMOFSNOW; i++)
	{
		if ( Snow[i].layer != 4 && rand()%2)	// cut down snow speed		
		{	
			Snow[i].y += Snow[i].layer+1;		// higher layer moves faster

			if ( (getpixel(offscreen, Snow[i].x, Snow[i].y+1) == 28) && rand()%3 == 1 )		// if the pixel's color (layer*2+20) below is 28
			{															
				//if ( Snow[i].y > 194 )			// so no snow flakes standout
				{
					Snow[i].y = Snow[i].y-1;										 
					Snow[i].layer = 4;				// stop the Snow (layer=4)
					num_of_flakes--;
				}
			}

			if ( Snow[i].y > 199 )			// if snow reaches bottom, pile up!
			{
				if ( rand()%10 != 1 )		// not every flake show stays down (perfect effect!!!) (Make this a huge %XX and see)
					Snow[i].y = 0;
				else
				{
					Snow[i].y = 199;
					Snow[i].layer = 4;			// layer 4 means that this one is stopped
					num_of_flakes--;
				}
			}
			
			Snow[i].x = (Snow[i].x + (2 - rand()%4)) % 320;		// move left right but always between 320			
		}	

		if ( Flakes[i].Star[i].y > 199 )
		{
			for (int j=0; j < 9; j++)	
			{
				Flakes[i].Star[j].x = IStar[j].x;
				Flakes[i].Star[j].y = IStar[j].y;				
			}

			Scale(Flakes[i].Star, 9, Flakes[i].layer, Flakes[i].layer);				
			Translate(Flakes[i].Star, 9, rand() % 320, 0);			
		}
		else
			Translate( Flakes[i].Star, 9, 0, Flakes[i].layer+1);
		
	}
}

int main()
{
	int x_plane_pos = 200,
		y_plane_pos = 80;
	int x_pos = 320/2,
		y_pos = 200/2;
	BTMAP plane;
	BTMAP bitmap;
	int SpaceFinished = 1;
	int isNormal = 0;
	int isCircled = 0;
	float z_x = 15.5;
	float z_y = 15.0;
	float x_angle = 1;
	int i = 0;


	allegro_init();
	install_keyboard();
	   
	if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, "") != 0) 
	{
      allegro_message("Error initialising sound system\n%s\n", allegro_error);
      return 1;
	}

	set_color_depth(8);

	if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 320, 200, 0, 0)<0)
	//if (set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 320, 200, 0, 0)<0)
	{
		set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
		allegro_message("Failed to initialize video mode\n %s\n",allegro_error);
	}

	offscreen = create_bitmap(320, 200);

	InitMusic();
	play_midi(music, true);

	InitFonts();
	InitSnow();
	InitFlames(x_pos, y_pos);	

	if (LoadBitmap("plane.bmp", &plane) < 0 )
	{
		set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
		allegro_message("plane.bmp not found\n");
		return 1;
	}

	if (LoadBitmap("jonsmall.bmp", &bitmap)<0)
	{
		set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
		allegro_message("Error while loading bitmap");
		return 1;		
	}
		
	while ((!key[KEY_ESC])&&(!key[KEY_SPACE]))
	{
		if (key[KEY_UP])	x_angle += 0.5;  
        if (key[KEY_DOWN])	x_angle -= 0.5; 
        if (key[KEY_A]) x_pos += 0.5; 			
		if (key[KEY_D]) x_pos -= 0.5; 			
		if (key[KEY_W]) y_pos += 0.5; 			
		if (key[KEY_S]) y_pos -= 0.5; 			
		if (key[KEY_G]) z_x -= 0.5; 			
		if (key[KEY_H]) z_x += 0.5; 			
		if (key[KEY_B]) z_y -= 0.5; 			
		if (key[KEY_N]) z_y += 0.5; 					
	
		if (!SpaceFinished)
			UpdateSnow();		
		
		clear_bitmap(offscreen);				
		
		if (!SpaceFinished)
			DrawSnow();

		if ( num_of_flakes <= 0 )
		{
			UpdateFlames(offscreen, x_plane_pos, y_plane_pos);						
			DrawSmoke(x_plane_pos-15, y_plane_pos, 0, offscreen);
		
			if ( z_x != 0 && z_y != 0 )
				DrawPlane(&plane, x_plane_pos, y_plane_pos, x_angle, 0, 0, offscreen);
			
			if ( RenderString(i) == NULL )
			{
				num_of_flakes = 1;
				//	return 1;
			}
			
			if ( str_x <= 0)
			{	
				str_x = 320;
				i+=2;
			}
			y_plane_pos += 1 - rand()%3;
			x_plane_pos--;

			if (x_plane_pos <= 0)
			{
				//num_of_flakes = 1;
				SpaceFinished = 1;
				x_plane_pos = 320;
			}
		}					

		if (SpaceFinished)
		{
			if ( z_x != 0 && z_y != 0 )
			{
				x_angle = x_angle + 0.05;

				if ( isNormal == 0 )
					DrawBitmap(&bitmap, x_pos, y_pos, &x_angle, &z_x, z_y, &isCircled, &isNormal, offscreen);
				else
					NormalBitmap(&bitmap, x_pos, y_pos, &x_angle, &z_x, z_y, &isNormal, offscreen);
			}
		}
			
		// Do the Double buffering
		vsync();
		blit(offscreen, screen, 0, 0, 0, 0, 320, 200);		
	}	
	
	//destroy_bitmap(offscreen);
	destroy_midi(music);
	free(plane.data);
	free(bitmap.data);

	return 1;
}
END_OF_MAIN();