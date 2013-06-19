#if !defined(_BITMAP_EFFECT_H_)
#define _BITMAP_EFFECT_H_

/*
* Bitmap effects
*
* Jon Vlachoyiannis
* 1/1/2006
*/
#include "Bitmap.h"
#include <allegro.h>

void DrawBitmap(BTMAP *bmp, int x_pos, int y_pos, float *angle, float *zx, float z_y, int *isCircled, int *isNormal, BITMAP *offscreen);
void NormalBitmap(BTMAP *bmp, int x_pos, int y_pos, float *angle, float *zx, float z_y, int *isNormal, BITMAP *offscreen);

#endif