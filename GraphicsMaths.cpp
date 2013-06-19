/*
* Maths used for graphics
*
* Jon Vlachoyiannis
* 24/12/2005
*/

#include <math.h>
#include "GraphicsMaths.h"

/*
* Scaling
*/
void Scale( Vector3d_t *vec, int num_of_vects, float scale_x, float scale_y, float scale_z)
{
	int i;
	for (i = 0; i < num_of_vects; i++)
	{
		vec[i].x = vec[i].x * scale_x;	
		vec[i].y = vec[i].y * scale_y;	
		vec[i].z = vec[i].z * scale_z;			
	}	
} 

/*
* Translation
*/
void Translate( Vector3d_t *vec, int num_of_vects, float x_pos, float y_pos)
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
void Translate3d(Vector3d_t *vec_in,  Vector3d_t *vec_out, int num_of_vects, float x_pos, float y_pos, float z_pos)
{
	int i;
	for (i = 0; i < num_of_vects; i++)
	{
		vec_out[i].x = vec_in[i].x + x_pos;	
		vec_out[i].y = vec_in[i].y + y_pos;		
		vec_out[i].z = vec_in[i].z + z_pos;		
	}	
} 

/*
* Rotate Z
*/ 
void Rotate3dZ( Vector3d_t *vec_in,  Vector3d_t *vec_out, int num_of_vects, float angle)
{
	int i;
	for (i = 0; i < num_of_vects; i++)
	{
		vec_out[i].x = vec_in[i].x * cos(angle) - vec_in[i].y * sin(angle);
		vec_out[i].y = vec_in[i].y * cos(angle) + vec_in[i].x * sin(angle);		
		vec_out[i].z = vec_in[i].z;
	}	
} 

/*
* Rotate X
*/ 
void Rotate3dX(Vector3d_t *vec_in, Vector3d_t *vec_out, int num_of_vects, float angle)
{
    int i;    
    for (i = 0; i < num_of_vects; i++)
    {
		vec_out[i].x = vec_in[i].x;
		vec_out[i].y = vec_in[i].y * cos(angle) - vec_in[i].z * sin(angle);
        vec_out[i].z = vec_in[i].z * cos(angle) + vec_in[i].y * sin(angle);
    }
}

/*
* Rotate Y
*/ 
void Rotate3dY(Vector3d_t *vec_in,Vector3d_t *vec_out,int num_of_vects, float angle)
{
    int i;    
    for (i =0; i < num_of_vects; i++)
    {
        vec_out[i].x = vec_in[i].x * cos(angle) + vec_in[i].z * sin(angle);
		vec_out[i].y = vec_in[i].y;
        vec_out[i].z = vec_in[i].z * cos(angle) - vec_in[i].x * sin(angle);
    }
}


