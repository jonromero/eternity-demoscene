#if !defined(_SPACESHIP_H_)
#define _SPACESHIP_H_

/*
* Flame/smoke effects on spaceship
*
* Jon Vlachoyiannis
* 1/1/2006
*/

#include "Bitmap.h"
#include "GraphicsMaths.h"

typedef struct {
	int x, y;
	int color;
}flame_t;

void DrawSmoke(int x_space, int y_space, float angle, BITMAP *offscreen);
void InitFlames(int x_pos, int y_pos);
void UpdateFlames(BITMAP *offscreen, int x_pos, int y_pos);
void DrawPlane(BTMAP *bmp, int x_pos, int y_pos, float angle, float z_x, float z_y, BITMAP *offscreen);

#endif