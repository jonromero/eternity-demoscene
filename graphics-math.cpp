/*
* Maths for 2d and 3d  (GPL 2.0)
* 
* Jon Vlachoyiannis
* 16/12/2005
* Parts from Allegro.cc / Hugi Magazine (31)
*/

#define PI				3.1415926535897932384626433832795
#define floatcos(x)     cos((x) * PI / 128.0)
#define floatsin(x)     sin((x) * PI / 128.0)
#define floattan(x)     tan((x) * PI / 128.0)

typedef struct {          		 /* transformation matrix (floating point) */
   float v[3][3];                /* scaling and rotation */
   float t[3];                   /* translation */
}Matrix_t;
                                   
Matrix_t IMatrix = 
{
   {
      /* 3x3 identity */
      { 1.0, 0.0, 0.0 },
      { 0.0, 1.0, 0.0 },
      { 0.0, 0.0, 1.0 },
   },

   /* zero translation */
   { 0.0, 0.0, 0.0 }
};

typedef struct {
	float x;
	float y;
}Vector2d_t;

typedef struct {
	float x;
	float y;
}Vector3d_t;

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
* Scaling
*/
void Scale2d( Vector2d_t *vec_in,  Vector2d_t *vec_out, int num_of_vects, float scale_x, float scale_y)
{
	int i;
	for (i = 0; i < num_of_vects; i++)
	{
		vec_out[i].x = vec_in[i].x * scale_x;	
		vec_out[i].y = vec_in[i].y * scale_y;		
	}	
} 

/*
* Rotate XY
*/ 
void RotateXY2d( Vector2d_t *vec_in,  Vector2d_t *vec_out, int num_of_vects, float angle)
{
	int i;
	for (i = 0; i < num_of_vects; i++)
	{
		vec_out[i].x = vec_in[i].x * floatcos(angle) - vec_in[i].y * floatsin(angle);
		vec_out[i].y = vec_in[i].y * floatcos(angle) + vec_in[i].x * floatsin(angle);		
	}	
} 

/*
* Return Normal of a 3d vector
*/
float VectorNormal( Vector3d_t *vector )
{
     return sqrt( vector->x * vector->x +
                  vector->y * vector->y +
                  vector->z * vector->z );
}

/* 
* Create Translation Matrix
*/
void SetTranslationMatrix(Matrix_t *m, float x, float y, float z)
{
   *m = identity_matrix_f;

   m->t[0] = x;
   m->t[1] = y;
   m->t[2] = z;
}

/* 
* Create Scale Matrix
*/
void SetScaleMatrix(Matrix_t *m, float x, float y, float z)
{
   *m = identity_matrix_f;

   m->v[0][0] = x;
   m->v[1][1] = y;
   m->v[2][2] = z;
}

/* 
* Create Rotate X Matrix
*/
void SetRotateXMatrix(Matrix *m, float r)
{
   float c = floatcos(r);
   float s = floatsin(r);

   *m = identity_matrix_f;

   m->v[1][1] = c;
   m->v[1][2] = -s;

   m->v[2][1] = s;
   m->v[2][2] = c;
}


/*
* Create Rotate Y Matrix
*/
void SetRotateYMatrix(Matrix *m, float r)
{
   float c = floatcos(r);
   float s = floatsin(r);

   *m = identity_matrix_f;

   m->v[0][0] = c;
   m->v[0][2] = s;

   m->v[2][0] = -s;
   m->v[2][2] = c;
}

/*
* Create Rotate Z Matrix
*/
void SetRotateZMatrix(Matrix *m, float r)
{
   float c = floatcos(r);
   float s = floatsin(r);

   *m = identity_matrix_f;

   m->v[0][0] = c;
   m->v[0][1] = -s;

   m->v[1][0] = s;
   m->v[1][1] = c;
}

/*
* Matrix Multiply ( matResult = matA * matB )
*/
void MultiplyMatrix(float matResult[4][4], float matA[4][4], float matB[4][4])
{
	int i, j, k;
	
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			matResult[i][j] = 0;
			for (k = 0; k < 4; k++)
				matResult[i][j] += matA[i][k]*matB[k][j];			
		}
	}
}

/*
* vec_out = vec_in * mat
*/
void MultiplyVectors(Vector3d_t *vec_in, Vector3d_t *vec_out, int total, float mat[4][4])
{
	int i;
	
	for (i = 0; i < total; i++)
	{
		vec_out[i].x = vec_in[i].x * mat[0][0] + vec_in[i].y * mat[1][0] + vec_in[i].z * mat[2][0] + mat[3][0];
		vec_out[i].y = vec_in[i].x * mat[0][1] + vec_in[i].y * mat[1][1] + vec_in[i].z * mat[2][1] + mat[3][1];	
		vec_out[i].z = vec_in[i].x * mat[0][2] + vec_in[i].y * mat[1][2] + vec_in[i].z * mat[2][2] + mat[3][2];
	}	
}
