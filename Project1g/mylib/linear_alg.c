#include "linear_alg.h"
#include <stdio.h>
#include <math.h>


void printV(vec4 v)
{
	printf("[%10.4f %10.4f %10.4f %10.4f ]\n", v.x, v.y, v.z, v.w);
}

vec4 scalVMult(vec4 v, float num)
{
	vec4 new;
	new.x = num * v.x;
	new.y = num * v.y;
	new.z = num * v.z;
	new.w = num * v.w;
	return new;
}

vec4 addV(vec4 v1, vec4 v2)
{
	vec4 new;
	new.x = v1.x + v2.x;
	new.y = v1.y + v2.y;
	new.z = v1.z + v2.z;
	new.w = v1.w + v2.w;
	return new;
}

vec4 subV(vec4 v1, vec4 v2)
{
	vec4 new;
	new.x = v1.x - v2.x;
	new.y = v1.y - v2.y;
	new.z = v1.z - v2.z;
	new.w = v1.w - v2.w;
	return new;
}

float magV(vec4 v)
{
	float mag = 0.0;
	float square = 0.0;
	square = (v.x*v.x) + (v.y*v.y) + (v.z*v.z) + (v.w*v.w);
	mag = sqrt(square);
	return mag;
}

vec4 normV(vec4 v)
{
	vec4 new;
	if(magV(v) == 0)
	{
	printf("Error, the magnitude of the vector is 0, displaying vector with error:\n");
	return v;
	}
	else
		new = scalVMult(v, (1/(magV(v))));
	return new; 
}

float dotV(vec4 v1, vec4 v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w);
}

vec4 crossV(vec4 v1, vec4 v2)
{
	vec4 new;
	new.x = (v1.y * v2.z) - (v1.z * v2.y);
	new.y = (v1.z * v2.x) - (v1.x * v2.z);
	new.z = (v1.x * v2.y) - (v1.y * v2.x);
	new.w = 0;
	return new;
}


void printM(mat4 m)
{
	printf("[%10.4f %10.4f %10.4f %10.4f ]\n",m.x.x, m.y.x, m.z.x, m.w.x);
	printf("[%10.4f %10.4f %10.4f %10.4f ]\n",m.x.y, m.y.y, m.z.y, m.w.y);
	printf("[%10.4f %10.4f %10.4f %10.4f ]\n",m.x.z, m.y.z, m.z.z, m.w.z);
	printf("[%10.4f %10.4f %10.4f %10.4f ]\n",m.x.w, m.y.w, m.z.w, m.w.w);
}

mat4 scalMMult(mat4 m, float num)
{
	mat4 new;
	new.x = scalVMult(m.x, num);
	new.y = scalVMult(m.y, num);
	new.z = scalVMult(m.z, num);
	new.w = scalVMult(m.w, num);
	return new;
}

mat4 addM(mat4 m1, mat4 m2)
{
	mat4 new;
	new.x.x = m1.x.x + m2.x.x;
	new.x.y = m1.x.y + m2.x.y;
	new.x.z = m1.x.z + m2.x.z;
	new.x.w = m1.x.w + m2.x.w;
	
	new.y.x = m1.y.x + m2.y.x;
	new.y.y = m1.y.y + m2.y.y;
	new.y.z = m1.y.z + m2.y.z;
	new.y.w = m1.y.w + m2.y.w;
	
	new.z.x = m1.z.x + m2.z.x;
	new.z.y = m1.z.y + m2.z.y;
	new.z.z = m1.z.z + m2.z.z;
	new.z.w = m1.z.w + m2.z.w;
	
	new.w.x = m1.w.x + m2.w.x;
	new.w.y = m1.w.y + m2.w.y;
	new.w.z = m1.w.z + m2.w.z;
	new.w.w = m1.w.w + m2.w.w;
	
	return new;
}

mat4 subM(mat4 m1, mat4 m2)
{
	mat4 new;
	new.x.x = m1.x.x - m2.x.x;
	new.x.y = m1.x.y - m2.x.y;
	new.x.z = m1.x.z - m2.x.z;
	new.x.w = m1.x.w - m2.x.w;
	
	new.y.x = m1.y.x - m2.y.x;
	new.y.y = m1.y.y - m2.y.y;
	new.y.z = m1.y.z - m2.y.z;
	new.y.w = m1.y.w - m2.y.w;
	
	new.z.x = m1.z.x - m2.z.x;
	new.z.y = m1.z.y - m2.z.y;
	new.z.z = m1.z.z - m2.z.z;
	new.z.w = m1.z.w - m2.z.w;
	
	new.w.x = m1.w.x - m2.w.x;
	new.w.y = m1.w.y - m2.w.y;
	new.w.z = m1.w.z - m2.w.z;
	new.w.w = m1.w.w - m2.w.w;
	
	return new;
}

mat4 multM(mat4 m1, mat4 m2)
{
	mat4 new;
	new.x.x = (m1.x.x*m2.x.x) + (m1.y.x*m2.x.y) + (m1.z.x*m2.x.z) + (m1.w.x*m2.x.w);
	new.x.y = (m1.x.y*m2.x.x) + (m1.y.y*m2.x.y) + (m1.z.y*m2.x.z) + (m1.w.y*m2.x.w);
	new.x.z = (m1.x.z*m2.x.x) + (m1.y.z*m2.x.y) + (m1.z.z*m2.x.z) + (m1.w.z*m2.x.w);
	new.x.w = (m1.x.w*m2.x.x) + (m1.y.w*m2.x.y) + (m1.z.w*m2.x.z) + (m1.w.w*m2.x.w);
	
	new.y.x = (m1.x.x*m2.y.x) + (m1.y.x*m2.y.y) + (m1.z.x*m2.y.z) + (m1.w.x*m2.y.w);
	new.y.y = (m1.x.y*m2.y.x) + (m1.y.y*m2.y.y) + (m1.z.y*m2.y.z) + (m1.w.y*m2.y.w);
	new.y.z = (m1.x.z*m2.y.x) + (m1.y.z*m2.y.y) + (m1.z.z*m2.y.z) + (m1.w.z*m2.y.w);
	new.y.w = (m1.x.w*m2.y.x) + (m1.y.w*m2.y.y) + (m1.z.w*m2.y.z) + (m1.w.w*m2.y.w);
	
	new.z.x = (m1.x.x*m2.z.x) + (m1.y.x*m2.z.y) + (m1.z.x*m2.z.z) + (m1.w.x*m2.z.w);
	new.z.y = (m1.x.y*m2.z.x) + (m1.y.y*m2.z.y) + (m1.z.y*m2.z.z) + (m1.w.y*m2.z.w);
	new.z.z = (m1.x.z*m2.z.x) + (m1.y.z*m2.z.y) + (m1.z.z*m2.z.z) + (m1.w.z*m2.z.w);
	new.z.w = (m1.x.w*m2.z.x) + (m1.y.w*m2.z.y) + (m1.z.w*m2.z.z) + (m1.w.w*m2.z.w);
	
	new.w.x = (m1.x.x*m2.w.x) + (m1.y.x*m2.w.y) + (m1.z.x*m2.w.z) + (m1.w.x*m2.w.w);
	new.w.y = (m1.x.y*m2.w.x) + (m1.y.y*m2.w.y) + (m1.z.y*m2.w.z) + (m1.w.y*m2.w.w);
	new.w.z = (m1.x.z*m2.w.x) + (m1.y.z*m2.w.y) + (m1.z.z*m2.w.z) + (m1.w.z*m2.w.w);
	new.w.w = (m1.x.w*m2.w.x) + (m1.y.w*m2.w.y) + (m1.z.w*m2.w.z) + (m1.w.w*m2.w.w);
	
	return new;
}

vec4 multMV(mat4 m, vec4 v)
{
	vec4 new;
	new.x = (m.x.x*v.x) + (m.y.x*v.y) + (m.z.x*v.z) + (m.w.x*v.w);
	new.y = (m.x.y*v.x) + (m.y.y*v.y) + (m.z.y*v.z) + (m.w.y*v.w);
	new.z = (m.x.z*v.x) + (m.y.z*v.y) + (m.z.z*v.z) + (m.w.z*v.w);
	new.w = (m.x.w*v.x) + (m.y.w*v.y) + (m.z.w*v.z) + (m.w.w*v.w);
	return new;
}

mat4 transpose(mat4 m)
{
	mat4 new;
	new.x.x = m.x.x;
	new.x.y = m.y.x; 
	new.x.z = m.z.x;
	new.x.w = m.w.x;
	
	new.y.x = m.x.y;
	new.y.y = m.y.y;
	new.y.z = m.z.y;
	new.y.w = m.w.y;
	
	new.z.x = m.x.z;
	new.z.y = m.y.z;
	new.z.z = m.z.z;
	new.z.w = m.w.z;
	
	new.w.x = m.x.w;
	new.w.y = m.y.w;
	new.w.z = m.z.w;
	new.w.w = m.w.w;
	
	return new;
}
/*
mat4 adjunct(mat4 m)
{
	mat4 new;
	
	mat3 xx = {{m.y.y, m.y.z, m.y.w},{m.z.y, m.z.z, m.z.w},{m.w.y, m.w.z, m.w.w}};
	new.x.x = determinant(xx);
	//printf("xx%.4f\n", new.x.x);
	mat3 yx = {{m.x.y, m.x.z, m.x.w},{m.z.y, m.z.z, m.z.w},{m.w.y, m.w.z, m.w.w}};
	new.y.x = (-1)*determinant(yx);
	//printf("yx%.4f\n", new.y.x);
	mat3 zx = {{m.x.y, m.x.z, m.x.w},{m.y.y, m.y.z, m.y.w},{m.w.y, m.w.z, m.w.w}};
	new.z.x = determinant(zx);
	//printf("zx%.4f\n", new.z.x);
	mat3 wx = {{m.x.y, m.x.z, m.x.w},{m.y.y, m.y.z, m.y.w},{m.z.y, m.z.z, m.z.w}};
	new.w.x = (-1)*determinant(wx);
	//printf("wx%.4f\n", new.w.x);
	
	mat3 xy = {{m.y.x, m.y.z, m.y.w},{m.z.x, m.z.z, m.z.w},{m.w.x, m.w.z, m.w.w}};
	new.x.y = (-1)*determinant(xy);
	//printf("xy%.4f\n", new.x.y);
	mat3 yy = {{m.x.x, m.x.z, m.x.w},{m.z.x, m.z.z, m.z.w},{m.w.x, m.w.z, m.w.w}};
	new.y.y = determinant(yy);
	mat3 zy = {{m.x.x, m.x.z, m.x.w},{m.y.x, m.y.z, m.y.w},{m.w.x, m.w.z, m.w.w}};
	new.z.y = (-1)*determinant(zy);
	mat3 wy = {{m.x.x, m.x.z, m.x.w},{m.y.x, m.y.z, m.y.w},{m.z.x, m.z.z, m.z.w}};
	new.w.y = determinant(wy);
	
	mat3 xz = {{m.y.x, m.y.y, m.y.w},{m.z.x, m.z.y, m.z.w},{m.w.x, m.w.y, m.w.w}};
	new.x.z = determinant(xz);
	//printf("xz%.4f\n", new.x.z);
	mat3 yz = {{m.x.x, m.x.y, m.x.w},{m.z.x, m.z.y, m.z.w},{m.w.x, m.w.y, m.w.w}};
	new.y.z = (-1)*determinant(yz);
	mat3 zz = {{m.x.x, m.x.y, m.x.w},{m.y.x, m.y.y, m.y.w},{m.w.x, m.w.y, m.w.w}};
	new.z.z = determinant(zz);
	mat3 wz = {{m.x.x, m.x.y, m.x.w},{m.y.x, m.y.y, m.y.w},{m.z.x, m.z.y, m.z.w}};
	new.w.z = (-1)*determinant(wz);
	
	mat3 xw = {{m.y.x, m.y.y, m.y.z},{m.z.x, m.z.y, m.z.z},{m.w.x, m.w.y, m.w.z}};
	new.x.w = (-1)*determinant(xw);
	//printf("xw%.4f\n", new.x.w);
	mat3 yw = {{m.x.x, m.x.y, m.x.z},{m.z.x, m.z.y, m.z.z},{m.w.x, m.w.y, m.w.z}};
	new.y.w = determinant(yw);
	mat3 zw = {{m.x.x, m.x.y, m.x.z},{m.y.x, m.y.y, m.y.z},{m.w.x, m.w.y, m.w.z}};
	new.z.w = (-1)*determinant(zw);
	mat3 ww = {{m.x.x, m.x.y, m.x.z},{m.y.x, m.y.y, m.y.z},{m.z.x, m.z.y, m.z.z}};
	new.w.w = determinant(ww);
	
	return new;
}

float determinant(mat3 m)
{
	float d = (m.x.x*((m.y.y*m.z.z) - (m.y.z*m.z.y)) - m.y.x*((m.x.y*m.z.z) - (m.z.y*m.x.z)) + m.z.x*((m.x.y*m.y.z) - (m.y.y*m.x.z)));
	//printf("det%.4f\n", d);
	return d;
}
*/

mat4 minor(mat4 m)
{
	mat4 new;
	
	new.x.x = (m.y.y*m.z.z*m.w.w) + (m.z.y*m.w.z*m.y.w) + (m.w.y*m.y.z*m.z.w) - (m.y.w*m.z.z*m.w.y) - (m.z.w*m.w.z*m.y.y) - (m.w.w*m.y.z*m.z.y);
	new.x.y = (m.y.x*m.z.z*m.w.w) + (m.z.x*m.w.z*m.y.w) + (m.w.x*m.y.z*m.z.w) - (m.y.w*m.z.z*m.w.x) - (m.z.w*m.w.z*m.y.x) - (m.w.w*m.y.z*m.z.x);
	new.x.z = (m.y.x*m.z.y*m.w.w) + (m.z.x*m.w.y*m.y.w) + (m.w.x*m.y.y*m.z.w) - (m.y.w*m.z.y*m.w.x) - (m.z.w*m.w.y*m.y.x) - (m.w.w*m.y.y*m.z.x);
	new.x.w = (m.y.x*m.z.y*m.w.z) + (m.z.x*m.w.y*m.y.z) + (m.w.x*m.y.y*m.z.z) - (m.y.z*m.z.y*m.w.x) - (m.z.z*m.w.y*m.y.x) - (m.w.z*m.y.y*m.z.x);
	
	new.y.x = (m.x.y*m.z.z*m.w.w) + (m.z.y*m.w.z*m.x.w) + (m.w.y*m.x.z*m.z.w) - (m.x.w*m.z.z*m.w.y) - (m.z.w*m.w.z*m.x.y) - (m.w.w*m.x.z*m.z.y);
	new.y.y = (m.x.x*m.z.z*m.w.w) + (m.z.x*m.w.z*m.x.w) + (m.w.x*m.x.z*m.z.w) - (m.x.w*m.z.z*m.w.x) - (m.z.w*m.w.z*m.x.x) - (m.w.w*m.x.z*m.z.x);
	new.y.z = (m.x.x*m.z.y*m.w.w) + (m.z.x*m.w.y*m.x.w) + (m.w.x*m.x.y*m.z.w) - (m.x.w*m.z.y*m.w.x) - (m.z.w*m.w.y*m.x.x) - (m.w.w*m.x.y*m.z.x);
	new.y.w = (m.x.x*m.z.y*m.w.z) + (m.z.x*m.w.y*m.x.z) + (m.w.x*m.x.y*m.z.z) - (m.x.z*m.z.y*m.w.x) - (m.z.z*m.w.y*m.x.x) - (m.w.z*m.x.y*m.z.x);
	
	new.z.x = (m.x.y*m.y.z*m.w.w) + (m.y.y*m.w.z*m.x.w) + (m.w.y*m.x.z*m.y.w) - (m.x.w*m.y.z*m.w.y) - (m.y.w*m.w.z*m.x.y) - (m.w.w*m.x.z*m.y.y);
	new.z.y = (m.x.x*m.y.z*m.w.w) + (m.y.x*m.w.z*m.x.w) + (m.w.x*m.x.z*m.y.w) - (m.x.w*m.y.z*m.w.x) - (m.y.w*m.w.z*m.x.x) - (m.w.w*m.x.z*m.y.x);
	new.z.z = (m.x.x*m.y.y*m.w.w) + (m.y.x*m.w.y*m.x.w) + (m.w.x*m.x.y*m.y.w) - (m.x.w*m.y.y*m.w.x) - (m.y.w*m.w.y*m.x.x) - (m.w.w*m.x.y*m.y.x);
	new.z.w = (m.x.x*m.y.y*m.w.z) + (m.y.x*m.w.y*m.x.z) + (m.w.x*m.x.y*m.y.z) - (m.x.z*m.y.y*m.w.x) - (m.y.z*m.w.y*m.x.x) - (m.w.z*m.x.y*m.y.x);
	
	new.w.x = (m.x.y*m.y.z*m.z.w) + (m.y.y*m.z.z*m.x.w) + (m.z.y*m.x.z*m.y.w) - (m.x.w*m.y.z*m.z.y) - (m.y.w*m.z.z*m.x.y) - (m.z.w*m.x.z*m.y.y);
	new.w.y = (m.x.x*m.y.z*m.z.w) + (m.y.x*m.z.z*m.x.w) + (m.z.x*m.x.z*m.y.w) - (m.x.w*m.y.z*m.z.x) - (m.y.w*m.z.z*m.x.x) - (m.z.w*m.x.z*m.y.x);
	new.w.z = (m.x.x*m.y.y*m.z.w) + (m.y.x*m.z.y*m.x.w) + (m.z.x*m.x.y*m.y.w) - (m.x.w*m.y.y*m.z.x) - (m.y.w*m.z.y*m.x.x) - (m.z.w*m.x.y*m.y.x);
	new.w.w = (m.x.x*m.y.y*m.z.z) + (m.y.x*m.z.y*m.x.z) + (m.z.x*m.x.y*m.y.z) - (m.x.z*m.y.y*m.z.x) - (m.y.z*m.z.y*m.x.x) - (m.z.z*m.x.y*m.y.x);
	
	return new;
}

mat4 cofactor(mat4 m)
{
	mat4 new;
	
	new.x.x = m.x.x;
	new.x.y = (-1)*m.x.y;
	new.x.z = m.x.z;
	new.x.w = (-1)*m.x.w;
	
	new.y.x = (-1)*m.y.x;
	new.y.y = m.y.y;
	new.y.z = (-1)*m.y.z;
	new.y.w = m.y.w;
	
	new.z.x = m.z.x;
	new.z.y = (-1)*m.z.y;
	new.z.z = m.z.z;
	new.z.w = (-1)*m.z.w;
	
	new.w.x = (-1)*m.w.x;
	new.w.y = m.w.y;
	new.w.z = (-1)*m.w.z;
	new.w.w = m.w.w;
	
	return new;
}

mat4 inverse(mat4 m)
{
	mat4 minr = minor(m);
	mat4 cof = cofactor(minr);
	mat4 trcof = transpose(cof);
	float det4 = m.x.x*minr.x.x - m.y.x*minr.y.x + m.z.x*minr.z.x - m.w.x*minr.w.x;
	//printf("det4%.4f\n", det4);
	mat4 inv = scalMMult(trcof, (1/det4));
	
	return inv;
}

// new lab04

mat4 identity()
{
	mat4 new;
	
	new.x.x = 1;
	new.x.y = 0;
	new.x.z = 0;
	new.x.w = 0;
	
	new.y.x = 0;
	new.y.y = 1;
	new.y.z = 0;
	new.y.w = 0;
	
	new.z.x = 0;
	new.z.y = 0;
	new.z.z = 1;
	new.z.w = 0;
	
	new.w.x = 0;
	new.w.y = 0;
	new.w.z = 0;
	new.w.w = 1;
	
	return new;
}

mat4 transformation(vec4 v)
{
	mat4 new;
	
	//vector v times the affine transformation matrix
	
	return new;
}

mat4 translation(float xf, float yf, float zf)
{
	mat4 new;

	//first p = v + new_p
	// can be thought of as an affine matrix times the vector
	// we want to return that 4x4 matrix
	// identity matrix with x y z at the last column
	
	new.x.x = 1;
	new.x.y = 0;
	new.x.z = 0;
	new.x.w = 0;
	
	new.y.x = 0;
	new.y.y = 1;
	new.y.z = 0;
	new.y.w = 0;
	
	new.z.x = 0;
	new.z.y = 0;
	new.z.z = 1;
	new.z.w = 0;
	
	new.w.x = xf;
	new.w.y = yf;
	new.w.z = zf;
	new.w.w = 1;

	return new;
}

mat4 scaling(float xf, float yf, float zf)
{
	mat4 new;
	
	//return identity matrix with x y z replacing the first ones, and 1 and the end
	new.x.x = xf;
	new.x.y = 0;
	new.x.z = 0;
	new.x.w = 0;
	
	new.y.x = 0;
	new.y.y = yf;
	new.y.z = 0;
	new.y.w = 0;
	
	new.z.x = 0;
	new.z.y = 0;
	new.z.z = zf;
	new.z.w = 0;
	
	new.w.x = 0;
	new.w.y = 0;
	new.w.z = 0;
	new.w.w = 1;
	
	return new;
}

mat4 rotateZ(float theta)
{
	float rads = theta * M_PI/180;
	mat4 new;
	
	new.x.x = cos(rads);
	new.x.y = sin(rads);
	new.x.z = 0;
	new.x.w = 0;
	
	new.y.x = -1*sin(rads);
	new.y.y = cos(rads);
	new.y.z = 0;
	new.y.w = 0;
	
	new.z.x = 0;
	new.z.y = 0;
	new.z.z = 1;
	new.z.w = 0;
	
	new.w.x = 0;
	new.w.y = 0;
	new.w.z = 0;
	new.w.w = 1;
	
	return new;	
}

mat4 rotateX(float theta)
{
	float rads = theta * M_PI/180;
	mat4 new;
	
	new.x.x = 1;
	new.x.y = 0;
	new.x.z = 0;
	new.x.w = 0;
	
	new.y.x = 0;
	new.y.y = cos(rads);
	new.y.z = sin(rads);
	new.y.w = 0;
	
	new.z.x = 0;
	new.z.y = -1*sin(rads);
	new.z.z = cos(rads);
	new.z.w = 0;
	
	new.w.x = 0;
	new.w.y = 0;
	new.w.z = 0;
	new.w.w = 1;
	
	return new;
}

mat4 rotateY(float theta)
{
	float rads = theta * M_PI/180;
	mat4 new;
	
	new.x.x = cos(rads);
	new.x.y = 0;
	new.x.z = -1*sin(rads);
	new.x.w = 0;
	
	new.y.x = 0;
	new.y.y = 1;
	new.y.z = 0;
	new.y.w = 0;
	
	new.z.x = sin(rads);
	new.z.y = 0;
	new.z.z = cos(rads);
	new.z.w = 0;
	
	new.w.x = 0;
	new.w.y = 0;
	new.w.z = 0;
	new.w.w = 1;
	
	return new;
}
mat4 look_at(float eyex, float eyey, float eyez, float atx, float aty, float atz, float upx, float upy, float upz)
{
    mat4 new;
    mat4 new1;

    vec4 vup = {upx, upy, upz, 0.0};

    vec4 vpn = {eyex - atx, eyey- aty, eyez - atz, 0};
    vec4 n = scalVMult(vpn, 1.0/magV(vpn));

    vec4 cross1 = crossV(vup, n);
    vec4 u = scalVMult(cross1, 1.0/magV(cross1));

    vec4 cross2 = crossV(n, u);
    vec4 v = scalVMult(cross2, 1.0/magV(cross2));

    //float d = magnitudeVec(vpn);

    new.x.x = u.x;
    new.x.y = v.x;
    new.x.z = n.x;
    new.x.w = 0.0;

    new.y.x = u.y;
    new.y.y = v.y;
    new.y.z = n.y;
    new.y.w = 0.0;

    new.z.x = u.z;
    new.z.y = v.z;
    new.z.z = n.z;
    new.z.w = 0.0;

    new.w.x = 0.0;
    new.w.y = 0.0;
    new.w.z = 0.0;
    new.w.w = 1.0;

    new1 = translation(-eyex, -eyey, -eyez);
    new1= multM(new, new1);

    return new1;
}

mat4 ortho(float left, float right, float bottom, float top,float near, float far){
    mat4 N;

    N.x.x = 2.0/(right - left);
    N.x.y = 0.0;
    N.x.z = 0.0;
    N.x.w = 0.0;
    
    N.y.x = 0.0;
    N.y.y = 2.0/(top - bottom);
    N.y.z = 0.0;
    N.y.w = 0.0;
    
    N.z.x = 0.0;
    N.z.y = 0.0;
    N.z.z = 2.0/(near - far);
    N.z.w = 0.0;

    N.w.x = -((right + left)/(right - left));
    N.w.y = -((top + bottom)/(top - bottom));
    N.w.z = -((near + far)/(near - far));
    N.w.w = 1.0;

    return N;
}
mat4 frustum(float left, float right, float bottom, float top, float near, float far)
{
    mat4 new;

    new.x.x = (-2.0*near)/(right-left);
    new.x.y = 0.0;
    new.x.z = 0.0;
    new.x.w = 0.0;

    new.y.x = 0.0;
    new.y.y = (-2.0*near)/(top-bottom);
    new.y.z = 0.0;
    new.y.w = 0.0;

    new.z.x = (right+left)/(right-left);
    new.z.y = (top+bottom)/(top-bottom);
    new.z.z = (near+far)/(far-near);
    new.z.w = -1.0;

    new.w.x = 0.0;
    new.w.y = 0.0;
    new.w.z = -(2.0*near*far)/(far-near);
    new.w.w = 0.0;

    return new;
}