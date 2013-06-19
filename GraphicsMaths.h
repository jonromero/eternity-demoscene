#if !defined(_GRAPHICSMATHS_H_)
#define _GRAPHICSMATHS_H_

/*
* Maths used for graphics
*
* Jon Vlachoyiannis
* 24/12/2005
*/

typedef struct {
	float x;
	float y;
	float z;
}Vector3d_t;

typedef struct {
	Vector3d_t points[3];
}triangle3d_t;

void Scale( Vector3d_t *vec, int num_of_vects, float scale_x, float scale_y, float scale_z);
void Translate( Vector3d_t *vec, int num_of_vects, float x_pos, float y_pos);
void Translate3d(Vector3d_t *vec_in,  Vector3d_t *vec_out, int num_of_vects, float x_pos, float y_pos, float z_pos);
void Rotate3dZ( Vector3d_t *vec_in,  Vector3d_t *vec_out, int num_of_vects, float angle);
void Rotate3dX(Vector3d_t *inPoints,Vector3d_t *outPoints,int Total, float angleRadians);
void Rotate3dY(Vector3d_t *inPoints,Vector3d_t *outPoints,int Total, float angleRadians);

#endif
