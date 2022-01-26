#ifndef _LINEAR_ALG_H_
#define _LINEAR_ALG_H_

typedef struct
{
    float x;
    float y;
    float z;
    float w;
} vec4;

typedef struct
{
	vec4 x; //each column is a vector
	vec4 y;
	vec4 z; 
	vec4 w;
} mat4;

typedef struct
{
	float x;
	float y;
	float z;
} vec3;

typedef struct
{
	vec3 x;
	vec3 y;
	vec3 z;
} mat3;

void printV(vec4 v);
vec4 scalVMult(vec4 v, float num);
vec4 addV(vec4 v1, vec4 v2);
vec4 subV(vec4 v1, vec4 v2);
float magV(vec4 v);
vec4 normV(vec4 v);
float dotV(vec4 v1, vec4 v2);
vec4 crossV(vec4 v1, vec4 v2);
void printM(mat4 m);
mat4 scalMMult(mat4 m, float num);
mat4 addM(mat4 m1, mat4 m2);
mat4 subM(mat4 m1, mat4 m2);
mat4 multM(mat4 m1, mat4 m2);
vec4 multMV(mat4 m, vec4 v);
mat4 transpose(mat4 m);
//mat4 adjunct(mat4 m);
//float determinant(mat3 m);
mat4 minor(mat4 m);
mat4 cofactor(mat4 m);	
mat4 inverse(mat4 m);

mat4 identity();
mat4 transformation(vec4 v);
mat4 translation(float xf, float yf, float zf);
mat4 scaling(float xf, float yf, float zf);
mat4 rotateX(float theta);
mat4 rotateY(float theta);
mat4 rotateZ(float theta);
mat4 look_at(float eyex, float eyey, float eyez, 
             float atx, float aty, float atz, 
             float upx, float upy, float upz);

mat4 ortho(float left, float right, float bottom, 
           float top,float near, float far);

mat4 frustum(float left, float right, float bottom, float top, float near, float far);
#endif
