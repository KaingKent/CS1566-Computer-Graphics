/*
 * Project 3
 *
 * 
 */

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../mylib/initShader.h"
#include "../mylib/linear_alg.h"

#define BUFFER_OFFSET(offset) ((GLvoid *)(offset))

int num_vertices = 62430;
#define triangles 3000

vec4 circle[3678];
vec4 color[3678];

vec4 vertices[62430];
vec4 colors[62430];

float sphere1_degree = 0.0;
float sphere2_degree = 0.0;
float sphere3_degree = 0.0;
float sphere4_degree = 0.0;
float sphere5_degree = 0.0;
float sphere6_degree = 0.0;
float sphere7_degree = 0.0;
float sphere8_degree = 0.0;
float sphere9_degree = 0.0;
float sphere10_degree = 0.0;
float sphere11_degree = 0.0;
float sphere12_degree = 0.0;
float sphere13_degree = 0.0;
float sphere14_degree = 0.0;
float sphere15_degree = 0.0;
float sphere16_degree = 0.0;

mat4 sphere1_ctm = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
mat4 sphere2_ctm = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
mat4 sphere3_ctm = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
mat4 sphere4_ctm = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
mat4 sphere5_ctm = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
mat4 sphere6_ctm = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
mat4 sphere7_ctm = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
mat4 sphere8_ctm = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
mat4 sphere9_ctm = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
mat4 sphere10_ctm = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
mat4 sphere11_ctm = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
mat4 sphere12_ctm = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
mat4 sphere13_ctm = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
mat4 sphere14_ctm = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
mat4 sphere15_ctm = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
mat4 sphere16_ctm = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
mat4 floor_ctm = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

mat4 bulb_ctm = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

GLuint ctm_location;
mat4 ctm = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

GLuint is_shadow_location;

GLuint shininess_location;
float shininess = 5;

GLuint a_constant_location;
GLuint a_linear_location;
GLuint a_quadratic_location;

float a_constant = 1.2;
float a_linear = 0.1;
float a_quadratic = 0;

GLuint use_texture_location;
GLuint use_bulb_location;

GLuint model_view_location;
mat4 model_view = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

GLuint projection_location;
mat4 projection = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

GLuint light_position_location;

vec4 light_position = {0, 1, 0, 1};

typedef struct
{
	GLfloat x;
	GLfloat y;
} vec2;

vec2 tex_coords[3672 * 16];

void create_sphere(){
	int offset = 0;
	vec4 initial = {1, 0.0, 0.0, 1.0};
	vec4 initial2 = {1, 0.0, 0.0, 1.0};
	vec4 origin = {0.0, 0.0, 0.0, 1.0};

	for (int j = 0; j < 8; j++)
	{

		for (int i = 0; i < 36; i++)
		{
			vec4 p3 = matVecMult(rotateY(i * 10), matVecMult(rotateY(10), matVecMult(rotateZ(10), initial)));
			vec4 p2 = matVecMult(rotateY(i * 10), matVecMult(rotateY(10), initial));
			vec4 p1 = matVecMult(rotateY(i * 10), initial);
			vec4 p4 = matVecMult(rotateY(i * 10), matVecMult(rotateZ(10), initial));

			circle[offset] = p1;
			circle[offset + 1] = p2;
			circle[offset + 2] = p3;

			color[offset] = vecSub(circle[offset], origin);
			color[offset + 1] = vecSub(circle[offset + 1], origin);
			color[offset + 2] = vecSub(circle[offset + 2], origin);

			circle[offset + 3] = p1;
			circle[offset + 4] = p3;
			circle[offset + 5] = p4;

			color[offset + 3] = vecSub(circle[offset + 3], origin);
			color[offset + 4] = vecSub(circle[offset + 4], origin);
			color[offset + 5] = vecSub(circle[offset + 5], origin);

			vec4 p3a = matVecMult(rotateY(i * 10), matVecMult(rotateY(-10), matVecMult(rotateZ(-10), initial2)));
			vec4 p2a = matVecMult(rotateY(i * 10), matVecMult(rotateY(-10), initial2));
			vec4 p1a = matVecMult(rotateY(i * 10), initial2);
			vec4 p4a = matVecMult(rotateY(i * 10), matVecMult(rotateZ(-10), initial2));

			circle[offset + 6] = p1a;
			circle[offset + 7] = p2a;
			circle[offset + 8] = p3a;

			color[offset + 6] = vecSub(circle[offset + 6], origin);
			color[offset + 7] = vecSub(circle[offset + 7], origin);
			color[offset + 8] = vecSub(circle[offset + 8], origin);

			circle[offset + 9] = p1a;
			circle[offset + 10] = p3a;
			circle[offset + 11] = p4a;

			color[offset + 9] = vecSub(circle[offset + 9], origin);
			color[offset + 10] = vecSub(circle[offset + 10], origin);
			color[offset + 11] = vecSub(circle[offset + 11], origin);

			offset += 12;
		}

		initial = matVecMult(rotateZ(10), initial);
		initial2 = matVecMult(rotateZ(-10), initial2);
	}

	vec4 top = {0.0, 1, 0.0, 1.0};
	vec4 bot = {0.0, -1, 0.0, 1.0};
	for (int i = 0; i < 36; i++)
	{
		vec4 p1 = matVecMult(rotateY(i * 10), initial);
		vec4 p2 = matVecMult(rotateY(i * 10), matVecMult(rotateY(10), initial));

		circle[offset] = top;
		circle[offset + 1] = p1;
		circle[offset + 2] = p2;

		vec4 v1 = vecSub(circle[offset + 1], circle[offset]);
		vec4 v2 = vecSub(circle[offset + 2], circle[offset + 1]);
		vec4 cross = crossProduct(v1, v2);
		vec4 norm = normalize(cross);

		color[offset] = norm;
		color[offset + 1] = norm;
		color[offset + 2] = norm;

		vec4 p3 = matVecMult(rotateY(i * 10), initial2);
		vec4 p4 = matVecMult(rotateY(i * 10), matVecMult(rotateY(-10), initial2));

		circle[offset + 3] = bot;
		circle[offset + 4] = p3;
		circle[offset + 5] = p4;

		vec4 v3 = vecSub(circle[offset + 4], circle[offset + 3]);
		vec4 v4 = vecSub(circle[offset + 5], circle[offset + 4]);
		vec4 cross1 = crossProduct(v3, v4);
		vec4 norm1 = normalize(cross1);

		color[offset + 3] = norm1;
		color[offset + 4] = norm1;
		color[offset + 5] = norm1;

		offset += 6;
	}
}

float findS(float x, int num)
{
	float s = 0;
	float scale = x / 0.05;
	if (num == 1)
	{
		s = 0.115 * scale + 0.125;
	}
	if (num == 2)
	{
		s = 0.115 * scale + 0.375;
	}
	if (num == 3)
	{
		s = 0.115 * scale + 0.625;
	}
	if (num == 4)
	{
		s = 0.115 * scale + 0.875;
	}
	if (num == 5)
	{
		s = 0.115 * scale + 0.125;
	}
	if (num == 6)
	{
		s = 0.115 * scale + 0.375;
	}
	if (num == 7)
	{
		s = 0.115 * scale + 0.625;
	}
	if (num == 8)
	{
		s = 0.115 * scale + 0.875;
	}
	if (num == 9)
	{
		s = 0.115 * scale + 0.125;
	}
	if (num == 10)
	{
		s = 0.115 * scale + 0.375;
	}
	if (num == 11)
	{
		s = 0.115 * scale + 0.625;
	}
	if (num == 12)
	{
		s = 0.115 * scale + 0.875;
	}
	if (num == 13)
	{
		s = 0.115 * scale + 0.125;
	}
	if (num == 14)
	{
		s = 0.115 * scale + 0.375;
	}
	if (num == 15)
	{
		s = 0.115 * scale + 0.625;
	}
	if (num == 16)
	{
		s = 0.115 * scale + 0.875;
	}

	return s;
}

float findT(float y, int num)
{
	float t = 0;
	float scale = y / 0.05;
	if (num == 1)
	{
		t = 0.115 * scale + 0.125;
	}
	if (num == 2)
	{
		t = 0.115 * scale + 0.125;
	}
	if (num == 3)
	{
		t = 0.115 * scale + 0.125;
	}
	if (num == 4)
	{
		t = 0.115 * scale + 0.125;
	}
	if (num == 5)
	{
		t = 0.115 * scale + 0.375;
	}
	if (num == 6)
	{
		t = 0.115 * scale + 0.375;
	}
	if (num == 7)
	{
		t = 0.115 * scale + 0.375;
	}
	if (num == 8)
	{
		t = 0.115 * scale + 0.375;
	}
	if (num == 9)
	{
		t = 0.115 * scale + 0.626;
	}
	if (num == 10)
	{
		t = 0.115 * scale + 0.626;
	}
	if (num == 11)
	{
		t = 0.115 * scale + 0.626;
	}
	if (num == 12)
	{
		t = 0.115 * scale + 0.626;
	}
	if (num == 13)
	{
		t = 0.11375 * scale + 0.87625;
	}
	if (num == 14)
	{
		t = 0.11375 * scale + 0.87625;
	}
	if (num == 15)
	{
		t = 0.11375 * scale + 0.87625;
	}
	if (num == 16)
	{
		t = 0.11375 * scale + 0.87625;
	}

	return t;
}

void make_vertices()
{
	mat4 scale = scaling(0.05, 0.05, 0.05);

	mat4 trans1 = translation(-0.15, 0.051, -0.15);
	mat4 trans2 = translation(-0.05, 0.051, -0.15);
	mat4 trans3 = translation(0.05, 0.051, -0.15);
	mat4 trans4 = translation(0.15, 0.051, -0.15);
	mat4 trans5 = translation(-0.15, 0.051, -0.05);
	mat4 trans6 = translation(-0.05, 0.051, -0.05);
	mat4 trans7 = translation(0.05, 0.051, -0.05);
	mat4 trans8 = translation(0.15, 0.051, -0.05);
	mat4 trans9 = translation(-0.15, 0.051, 0.05);
	mat4 trans10 = translation(-0.05, 0.051, 0.05);
	mat4 trans11 = translation(0.05, 0.051, 0.05);
	mat4 trans12 = translation(0.15, 0.051, 0.05);
	mat4 trans13 = translation(-0.15, 0.051, 0.15);
	mat4 trans14 = translation(-0.05, 0.051, 0.15);
	mat4 trans15 = translation(0.05, 0.051, 0.15);
	mat4 trans16 = translation(0.15, 0.051, 0.15);

	int v_index = 0;
	int tex = 0;

	for (int i = 0; i < 3672; i++)
	{
		vertices[v_index] = matVecMult(scale, circle[i]);
		colors[v_index] = color[i];
		v_index++;
	}

	for (int l = tex; l < tex + 3672; l++)
	{

		float s = findS(vertices[l].x, 1);
		float t = findT(vertices[l].y, 1);
		tex_coords[l].x = s;
		tex_coords[l].y = t;
	}
	tex += 3672;
	for (int i = v_index - 3672; i < v_index; i++)
	{
		vertices[i] = matVecMult(trans1, vertices[i]);
	}

	//2
	for (int i = 0; i < 3672; i++)
	{
		vertices[v_index] = matVecMult(scale, circle[i]);
		colors[v_index] = color[i];
		v_index++;
	}
	for (int l = tex; l < tex + 3672; l++)
	{
		float s = findS(vertices[l].x, 2);
		float t = findT(vertices[l].y, 2);
		tex_coords[l].x = s;
		tex_coords[l].y = t;
	}
	tex += 3672;
	for (int i = v_index - 3672; i < v_index; i++)
	{
		vertices[i] = matVecMult(trans2, vertices[i]);
	}
	//3
	for (int i = 0; i < 3672; i++)
	{
		vertices[v_index] = matVecMult(scale, circle[i]);
		colors[v_index] = color[i];
		v_index++;
	}
	for (int l = tex; l < tex + 3672; l++)
	{
		float s = findS(vertices[l].x, 3);
		float t = findT(vertices[l].y, 3);
		tex_coords[l].x = s;
		tex_coords[l].y = t;
	}
	tex += 3672;
	for (int i = v_index - 3672; i < v_index; i++)
	{
		vertices[i] = matVecMult(trans3, vertices[i]);
	}

	//4
	for (int i = 0; i < 3672; i++)
	{
		vertices[v_index] = matVecMult(scale, circle[i]);
		colors[v_index] = color[i];
		v_index++;
	}
	for (int l = tex; l < tex + 3672; l++)
	{
		float s = findS(vertices[l].x, 4);
		float t = findT(vertices[l].y, 4);
		tex_coords[l].x = s;
		tex_coords[l].y = t;
	}
	tex += 3672;
	for (int i = v_index - 3672; i < v_index; i++)
	{
		vertices[i] = matVecMult(trans4, vertices[i]);
	}

	//5
	for (int i = 0; i < 3672; i++)
	{
		vertices[v_index] = matVecMult(scale, circle[i]);
		colors[v_index] = color[i];
		v_index++;
	}
	for (int l = tex; l < tex + 3672; l++)
	{
		float s = findS(vertices[l].x, 5);
		float t = findT(vertices[l].y, 5);
		tex_coords[l].x = s;
		tex_coords[l].y = t;
	}
	tex += 3672;
	for (int i = v_index - 3672; i < v_index; i++)
	{
		vertices[i] = matVecMult(trans5, vertices[i]);
	}

	//6
	for (int i = 0; i < 3672; i++)
	{
		vertices[v_index] = matVecMult(scale, circle[i]);
		colors[v_index] = color[i];
		v_index++;
	}
	for (int l = tex; l < tex + 3672; l++)
	{
		float s = findS(vertices[l].x, 6);
		float t = findT(vertices[l].y, 6);
		tex_coords[l].x = s;
		tex_coords[l].y = t;
	}
	tex += 3672;
	for (int i = v_index - 3672; i < v_index; i++)
	{
		vertices[i] = matVecMult(trans6, vertices[i]);
	}

	//7
	for (int i = 0; i < 3672; i++)
	{
		vertices[v_index] = matVecMult(scale, circle[i]);
		colors[v_index] = color[i];
		v_index++;
	}
	for (int l = tex; l < tex + 3672; l++)
	{
		float s = findS(vertices[l].x, 7);
		float t = findT(vertices[l].y, 7);
		tex_coords[l].x = s;
		tex_coords[l].y = t;
	}
	tex += 3672;
	for (int i = v_index - 3672; i < v_index; i++)
	{
		vertices[i] = matVecMult(trans7, vertices[i]);
	}

	//8
	for (int i = 0; i < 3672; i++)
	{
		vertices[v_index] = matVecMult(scale, circle[i]);
		colors[v_index] = color[i];
		v_index++;
	}
	for (int l = tex; l < tex + 3672; l++)
	{
		float s = findS(vertices[l].x, 8);
		float t = findT(vertices[l].y, 8);
		tex_coords[l].x = s;
		tex_coords[l].y = t;
	}
	tex += 3672;
	for (int i = v_index - 3672; i < v_index; i++)
	{
		vertices[i] = matVecMult(trans8, vertices[i]);
	}

	//9
	for (int i = 0; i < 3672; i++)
	{
		vertices[v_index] = matVecMult(scale, circle[i]);
		colors[v_index] = color[i];
		v_index++;
	}
	for (int l = tex; l < tex + 3672; l++)
	{
		float s = findS(vertices[l].x, 9);
		float t = findT(vertices[l].y, 9);
		tex_coords[l].x = s;
		tex_coords[l].y = t;
	}
	tex += 3672;
	for (int i = v_index - 3672; i < v_index; i++)
	{
		vertices[i] = matVecMult(trans9, vertices[i]);
	}
	//10
	for (int i = 0; i < 3672; i++)
	{
		vertices[v_index] = matVecMult(scale, circle[i]);
		colors[v_index] = color[i];
		v_index++;
	}
	for (int l = tex; l < tex + 3672; l++)
	{
		float s = findS(vertices[l].x, 10);
		float t = findT(vertices[l].y, 10);
		tex_coords[l].x = s;
		tex_coords[l].y = t;
	}
	tex += 3672;
	for (int i = v_index - 3672; i < v_index; i++)
	{
		vertices[i] = matVecMult(trans10, vertices[i]);
	}

	//11
	for (int i = 0; i < 3672; i++)
	{
		vertices[v_index] = matVecMult(scale, circle[i]);
		colors[v_index] = color[i];
		v_index++;
	}
	for (int l = tex; l < tex + 3672; l++)
	{
		float s = findS(vertices[l].x, 11);
		float t = findT(vertices[l].y, 11);
		tex_coords[l].x = s;
		tex_coords[l].y = t;
	}
	tex += 3672;
	for (int i = v_index - 3672; i < v_index; i++)
	{
		vertices[i] = matVecMult(trans11, vertices[i]);
	}

	//12
	for (int i = 0; i < 3672; i++)
	{
		vertices[v_index] = matVecMult(scale, circle[i]);
		colors[v_index] = color[i];
		v_index++;
	}
	for (int l = tex; l < tex + 3672; l++)
	{
		float s = findS(vertices[l].x, 12);
		float t = findT(vertices[l].y, 12);
		tex_coords[l].x = s;
		tex_coords[l].y = t;
	}
	tex += 3672;
	for (int i = v_index - 3672; i < v_index; i++)
	{
		vertices[i] = matVecMult(trans12, vertices[i]);
	}

	//13
	for (int i = 0; i < 3672; i++)
	{
		vertices[v_index] = matVecMult(scale, circle[i]);
		colors[v_index] = color[i];
		v_index++;
	}
	for (int l = tex; l < tex + 3672; l++)
	{
		float s = findS(vertices[l].x, 13);
		float t = findT(vertices[l].y, 13);
		tex_coords[l].x = s;
		tex_coords[l].y = t;
	}
	tex += 3672;
	for (int i = v_index - 3672; i < v_index; i++)
	{
		vertices[i] = matVecMult(trans13, vertices[i]);
	}

	//14
	for (int i = 0; i < 3672; i++)
	{
		vertices[v_index] = matVecMult(scale, circle[i]);
		colors[v_index] = color[i];
		v_index++;
	}
	for (int l = tex; l < tex + 3672; l++)
	{
		float s = findS(vertices[l].x, 14);
		float t = findT(vertices[l].y, 14);
		tex_coords[l].x = s;
		tex_coords[l].y = t;
	}
	tex += 3672;
	for (int i = v_index - 3672; i < v_index; i++)
	{
		vertices[i] = matVecMult(trans14, vertices[i]);
	}

	//15
	for (int i = 0; i < 3672; i++)
	{
		vertices[v_index] = matVecMult(scale, circle[i]);
		colors[v_index] = color[i];
		v_index++;
	}
	for (int l = tex; l < tex + 3672; l++)
	{
		float s = findS(vertices[l].x, 15);
		float t = findT(vertices[l].y, 15);
		tex_coords[l].x = s;
		tex_coords[l].y = t;
	}
	tex += 3672;
	for (int i = v_index - 3672; i < v_index; i++)
	{
		vertices[i] = matVecMult(trans15, vertices[i]);
	}

	//16
	for (int i = 0; i < 3672; i++)
	{
		vertices[v_index] = matVecMult(scale, circle[i]);
		colors[v_index] = color[i];
		v_index++;
	}
	for (int l = tex; l < tex + 3672; l++)
	{
		float s = findS(vertices[l].x, 16);
		float t = findT(vertices[l].y, 16);
		tex_coords[l].x = s;
		tex_coords[l].y = t;
	}
	tex += 3672;
	for (int i = v_index - 3672; i < v_index; i++)
	{
		vertices[i] = matVecMult(trans16, vertices[i]);
	}

	mat4 bulb_scale = scaling(.05, .05, .05);
	mat4 bulb_translation = translation(0, 1, 0);

	for (int i = 0; i < 3672; i++){ //bulb
		vertices[v_index] = matVecMult(matMult(bulb_translation, bulb_scale), circle[i]);
		vec4 white = {1, 1, 1, 1};
		colors[v_index] = white;
		v_index++;
	}

	vec4 f1 = {-5, 0, -5, 1};
	vec4 f2 = {5, 0, -5, 1};
	vec4 f5 = {5, 0, 5, 1};
	vec4 f6 = {-5, 0, 5, 1};
	//create floor
	vertices[62424] = f6;
	vertices[62425] = f5;
	vertices[62426] = f2;
	vertices[62427] = f2;
	vertices[62428] = f1;
	vertices[62429] = f6;

	//normalize the floor
	vec4 v1 = vecSub(vertices[62425], vertices[62424]);
	vec4 v2 = vecSub(vertices[62426], vertices[62425]);
	vec4 cross = crossProduct(v1, v2);
	vec4 norm = normalize(cross);

	colors[62424] = norm;
	colors[62425] = norm;
	colors[62426] = norm;

	v1 = vecSub(vertices[62428], vertices[62427]);
	v2 = vecSub(vertices[62429], vertices[62428]);
	cross = crossProduct(v1, v2);
	norm = normalize(cross);
	colors[62427] = norm;
	colors[62428] = norm;
	colors[62429] = norm;
}

int return_value;
void init(void)
{
	int width = 512;
	int height = 512;
	GLubyte my_texels[width][height][3];

	FILE *fp = fopen("pb_512_512.raw", "r");
	return_value = fread(my_texels, width * height * 3, 1, fp);
	fclose(fp);

	GLuint program = initShader("vshader.glsl", "fshader.glsl");
	glUseProgram(program);

	GLuint mytex[1];
	glGenTextures(1, mytex);
	glBindTexture(GL_TEXTURE_2D, mytex[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, my_texels);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	int param;
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &param);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors) + sizeof(tex_coords), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), sizeof(tex_coords), tex_coords);

	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	GLuint vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *)sizeof(vertices));

	GLuint vTexCoord = glGetAttribLocation(program, "vTexCoord");
	glEnableVertexAttribArray(vTexCoord);
	glVertexAttribPointer(vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0 + (sizeof(vertices) + sizeof(colors)));

	GLuint vNormal = glGetAttribLocation(program, "vNormal");
	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *)sizeof(vertices));

	ctm_location = glGetUniformLocation(program, "ctm");
	model_view_location = glGetUniformLocation(program, "model_view_matrix");
	glUniformMatrix4fv(model_view_location, 1, GL_FALSE, (GLfloat *)&model_view);
	projection_location = glGetUniformLocation(program, "projection_matrix");
	glUniformMatrix4fv(projection_location, 1, GL_FALSE, (GLfloat *)&projection);
	light_position_location = glGetUniformLocation(program, "light_position");
	is_shadow_location = glGetUniformLocation(program, "is_shadow");
	use_texture_location = glGetUniformLocation(program, "use_texture");
	shininess_location = glGetUniformLocation(program, "shininess");
	a_constant_location = glGetUniformLocation(program, "attenuation_constant");
	a_linear_location = glGetUniformLocation(program, "attenuation_linear");
	a_quadratic_location = glGetUniformLocation(program, "attenuation_quadratic");
	use_bulb_location = glGetUniformLocation(program, "use_bulb");

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glDepthRange(1, 0);

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUniform4fv(light_position_location, 1, (GLfloat *)&light_position);
	glUniformMatrix4fv(model_view_location, 1, GL_FALSE, (GLfloat *)&model_view);
	glUniform1fv(shininess_location, 1, (GLfloat *)&shininess);
	glUniform1fv(a_linear_location, 1, (GLfloat *)&a_linear);
	glUniform1fv(a_constant_location, 1, (GLfloat *)&a_constant);
	glUniform1fv(a_quadratic_location, 1, (GLfloat *)&a_quadratic);


	//send each object into the pipeline separately: 17 spheres and floor
	glUniform1i(use_bulb_location, 0);
	glUniform1i(use_texture_location, 0);
	glUniform1i(is_shadow_location, 0);
	glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *)&floor_ctm);
	glDrawArrays(GL_TRIANGLES, 62424, 6);

	glUniform1i(use_bulb_location, 0);
	glUniform1i(is_shadow_location, 0);
	glUniform1i(use_texture_location, 1);
	glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *)&sphere1_ctm);
	glDrawArrays(GL_TRIANGLES, 0, 3672);
	glUniform1i(is_shadow_location, 1);
	glDrawArrays(GL_TRIANGLES, 0, 3672);

	glUniform1i(use_bulb_location, 0);
	glUniform1i(is_shadow_location, 0);
	glUniform1i(use_texture_location, 1);
	glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *)&sphere2_ctm);
	glDrawArrays(GL_TRIANGLES, 3672, 3672);
	glUniform1i(is_shadow_location, 1);
	glDrawArrays(GL_TRIANGLES, 3672, 3672);

	glUniform1i(use_bulb_location, 0);
	glUniform1i(use_texture_location, 1);
	glUniform1i(is_shadow_location, 0);
	glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *)&sphere3_ctm);
	glDrawArrays(GL_TRIANGLES, 7344, 3672);
	glUniform1i(is_shadow_location, 1);
	glDrawArrays(GL_TRIANGLES, 7344, 3672);

	glUniform1i(use_bulb_location, 0);
	glUniform1i(use_texture_location, 1);
	glUniform1i(is_shadow_location, 0);
	glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *)&sphere4_ctm);
	glDrawArrays(GL_TRIANGLES, 11016, 3672);
	glUniform1i(is_shadow_location, 1);
	glDrawArrays(GL_TRIANGLES, 11016, 3672);

	glUniform1i(use_bulb_location, 0);
	glUniform1i(use_texture_location, 1);
	glUniform1i(is_shadow_location, 0);
	glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *)&sphere5_ctm); 
	glDrawArrays(GL_TRIANGLES, 14688, 3672);
	glUniform1i(is_shadow_location, 1); 
	glDrawArrays(GL_TRIANGLES, 14688, 3672);

	glUniform1i(use_bulb_location, 0);
	glUniform1i(use_texture_location, 1);
	glUniform1i(is_shadow_location, 0);
	glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *)&sphere6_ctm);
	glDrawArrays(GL_TRIANGLES, 18360, 3672);
	glUniform1i(is_shadow_location, 1);
	glDrawArrays(GL_TRIANGLES, 18360, 3672);

	glUniform1i(use_bulb_location, 0);
	glUniform1i(use_texture_location, 1);
	glUniform1i(is_shadow_location, 0);
	glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *)&sphere7_ctm);
	glDrawArrays(GL_TRIANGLES, 22032, 3672);
	glUniform1i(is_shadow_location, 1);
	glDrawArrays(GL_TRIANGLES, 22032, 3672);

	glUniform1i(use_bulb_location, 0);
	glUniform1i(use_texture_location, 1);
	glUniform1i(is_shadow_location, 0);
	glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *)&sphere8_ctm);
	glDrawArrays(GL_TRIANGLES, 25704, 3672);
	glUniform1i(is_shadow_location, 1);
	glDrawArrays(GL_TRIANGLES, 25704, 3672);

	glUniform1i(use_bulb_location, 0);
	glUniform1i(use_texture_location, 1);
	glUniform1i(is_shadow_location, 0);
	glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *)&sphere9_ctm);
	glDrawArrays(GL_TRIANGLES, 29376, 3672);
	glUniform1i(is_shadow_location, 1);
	glDrawArrays(GL_TRIANGLES, 29376, 3672);

	glUniform1i(use_bulb_location, 0);
	glUniform1i(use_texture_location, 1);
	glUniform1i(is_shadow_location, 0);
	glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *)&sphere10_ctm);
	glDrawArrays(GL_TRIANGLES, 33048, 3672);
	glUniform1i(is_shadow_location, 1);
	glDrawArrays(GL_TRIANGLES, 33048, 3672);

	glUniform1i(use_bulb_location, 0);
	glUniform1i(use_texture_location, 1);
	glUniform1i(is_shadow_location, 0);
	glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *)&sphere11_ctm);
	glDrawArrays(GL_TRIANGLES, 36720, 3672);
	glUniform1i(is_shadow_location, 1);
	glDrawArrays(GL_TRIANGLES, 36720, 3672);

	glUniform1i(use_bulb_location, 0);
	glUniform1i(use_texture_location, 1);
	glUniform1i(is_shadow_location, 0);
	glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *)&sphere12_ctm);
	glDrawArrays(GL_TRIANGLES, 40392, 3672);
	glUniform1i(is_shadow_location, 1);
	glDrawArrays(GL_TRIANGLES, 40392, 3672);

	glUniform1i(use_bulb_location, 0);
	glUniform1i(is_shadow_location, 0);
	glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *)&sphere13_ctm);
	glDrawArrays(GL_TRIANGLES, 44064, 3672);
	glUniform1i(is_shadow_location, 1);
	glDrawArrays(GL_TRIANGLES, 44064, 3672);

	glUniform1i(use_bulb_location, 0);
	glUniform1i(use_texture_location, 1);
	glUniform1i(is_shadow_location, 0);
	glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *)&sphere14_ctm);
	glDrawArrays(GL_TRIANGLES, 47736, 3672);
	glUniform1i(is_shadow_location, 1);
	glDrawArrays(GL_TRIANGLES, 47736, 3672);

	glUniform1i(use_bulb_location, 0);
	glUniform1i(use_texture_location, 1);
	glUniform1i(is_shadow_location, 0);
	glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *)&sphere15_ctm);
	glDrawArrays(GL_TRIANGLES, 51408, 3672);
	glUniform1i(is_shadow_location, 1);
	glDrawArrays(GL_TRIANGLES, 51408, 3672);

	glUniform1i(use_bulb_location, 0);
	glUniform1i(use_texture_location, 1);
	glUniform1i(is_shadow_location, 0);
	glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *)&sphere16_ctm);
	glDrawArrays(GL_TRIANGLES, 55080, 3672);
	glUniform1i(is_shadow_location, 1);
	glDrawArrays(GL_TRIANGLES, 55080, 3672);

	glUniform1i(use_bulb_location, 1);
	glUniform1i(use_texture_location, 0);
	glUniform1i(is_shadow_location, 0);
	glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *)&bulb_ctm);
	glDrawArrays(GL_TRIANGLES, 58752, 3672);

	glutSwapBuffers();
}

float bulbx = 0;
float bulby = 0;
float bulbz = 0;

float lightx = 0;
float lighty = 1;
float lightz = 0;

float eyex = 0;
float eyey = 1;
float eyez = 0;

float d = 1;
float theta = 0;

float phi = 90;
float upy = 0;
float upz = -1;

int start_line = 0;
int start_circle = 0;
float left = 0;
float right = 0;
void keyboard(unsigned char key, int mousex, int mousey)
{
	if (key == 'q')
	{
		glutLeaveMainLoop();
	}
	if (key == 's'){ //x decrease
		bulbx -= 0.1;
		lightx -= 0.1;
	}
	if (key == 'w'){ //x increase
		bulbx += 0.1;
		lightx += 0.1;
	}
	if (key == 'e'){ //y increase
		bulby += 0.1;
		lighty += 0.1;
	}
	if (key == 'd'){ //y decrease
		bulby -= 0.1;
		lighty -= 0.1;
	}
	if (key == 'r'){ //z increase
		bulbz += 0.1;
		lightz += 0.1;
	}
	if (key == 'f'){ //z decrease
		bulbz -= 0.1;
		lightz -= 0.1;
	}

	if (key == 'j'){//left
		left += 0.1;
		sphere1_ctm = matMult(rotateY(left), sphere1_ctm);
		sphere2_ctm = matMult(rotateY(left), sphere2_ctm);
		sphere3_ctm = matMult(rotateY(left), sphere3_ctm);
		sphere4_ctm = matMult(rotateY(left), sphere4_ctm);
		sphere5_ctm = matMult(rotateY(left), sphere5_ctm);
		sphere6_ctm = matMult(rotateY(left), sphere6_ctm);
		sphere7_ctm = matMult(rotateY(left), sphere7_ctm);
		sphere8_ctm = matMult(rotateY(left), sphere8_ctm);
		sphere9_ctm = matMult(rotateY(left), sphere9_ctm);
		sphere10_ctm = matMult(rotateY(left), sphere10_ctm);
		sphere11_ctm = matMult(rotateY(left), sphere11_ctm);
		sphere12_ctm = matMult(rotateY(left), sphere12_ctm);
		sphere13_ctm = matMult(rotateY(left), sphere13_ctm);
		sphere14_ctm = matMult(rotateY(left), sphere14_ctm);
		sphere15_ctm = matMult(rotateY(left), sphere15_ctm);
		sphere16_ctm = matMult(rotateY(left), sphere16_ctm);
		bulb_ctm = matMult(rotateY(left), bulb_ctm);
		floor_ctm = matMult(rotateY(left), floor_ctm);
	}
	if (key == 'l'){//right
		right -= 0.1;
		sphere1_ctm = matMult(rotateY(right), sphere1_ctm);
		sphere2_ctm = matMult(rotateY(right), sphere2_ctm);
		sphere3_ctm = matMult(rotateY(right), sphere3_ctm);
		sphere4_ctm = matMult(rotateY(right), sphere4_ctm);
		sphere5_ctm = matMult(rotateY(right), sphere5_ctm);
		sphere6_ctm = matMult(rotateY(right), sphere6_ctm);
		sphere7_ctm = matMult(rotateY(right), sphere7_ctm);
		sphere8_ctm = matMult(rotateY(right), sphere8_ctm);
		sphere9_ctm = matMult(rotateY(right), sphere9_ctm);
		sphere10_ctm = matMult(rotateY(right), sphere10_ctm);
		sphere11_ctm = matMult(rotateY(right), sphere11_ctm);
		sphere12_ctm = matMult(rotateY(right), sphere12_ctm);
		sphere13_ctm = matMult(rotateY(right), sphere13_ctm);
		sphere14_ctm = matMult(rotateY(right), sphere14_ctm);
		sphere15_ctm = matMult(rotateY(right), sphere15_ctm);
		sphere16_ctm = matMult(rotateY(right), sphere16_ctm);
		bulb_ctm = matMult(rotateY(right), bulb_ctm);
		floor_ctm = matMult(rotateY(right), floor_ctm);
	}

	if (key == 'y'){ //closer
		d -= 0.1;
		eyex = d * sin(phi * (M_PI / 180)) * cos(theta * (M_PI / 180));
		eyey = d * sin((phi) * (M_PI / 180)) * sin((theta) * (M_PI / 180));
		eyez = d * cos((phi) * (M_PI / 180));
	}
	if (key == 'h'){ //farther
		d += 0.1;
		eyex = d * sin(phi * (M_PI / 180)) * cos(theta * (M_PI / 180));
		eyey = d * sin((phi) * (M_PI / 180)) * sin((theta) * (M_PI / 180));
		eyez = d * cos((phi) * (M_PI / 180));
	}

	if (key == 'k'){ //up
		upy = 0;
		upz = -1;
		theta += 1;
		eyex = d * sin((phi) * (M_PI / 180)) * cos(theta * (M_PI / 180));
		eyey = d * sin((phi) * (M_PI / 180)) * sin((theta) * (M_PI / 180));
		eyez = d * cos((phi) * (M_PI / 180));
	}
	if (key == 'i'){ //down
		upy = 0;
		upz = -1;
		theta -= 1;
		eyex = d * sin((phi) * (M_PI / 180)) * cos(theta * (M_PI / 180));
		eyey = d * sin((phi) * (M_PI / 180)) * sin((theta) * (M_PI / 180));
		eyez = d * cos((phi) * (M_PI / 180));
	}

	if (key == 'x'){//start the lineup
		start_line = 1;
	}
	if (key == 'c'){//start the circle
		start_circle = 1;
	}

	model_view = look_at(eyez, eyex, eyey, 0, 0, 0, 0, upy, upz);
	vec4 l = {lightx, lighty, lightz, 1};
	light_position = l;
	bulb_ctm = translation(bulbx, bulby, bulbz);

	glutPostRedisplay();
}

void reshape(int width, int height)
{
	glViewport(0, 0, 512, 512);
}

int sphere1_line = 0;
float sphere1_z = 0;
float sphere1_x = 0;

int sphere2_line = 1;
float sphere2_z = 0;
float sphere2_x = 0;

int sphere3_line = 1;
float sphere3_z = 0;
float sphere3_x = 0;

int sphere4_line = 1;
float sphere4_z = 0;
float sphere4_x = 0;

int sphere5_line = 1;
float sphere5_z = 0;
float sphere5_x = 0;

int sphere6_line = 1;
float sphere6_z = 0;
float sphere6_x = 0;

int sphere7_line = 1;
float sphere7_z = 0;
float sphere7_x = 0;

int sphere8_line = 1;
float sphere8_z = 0;
float sphere8_x = 0;

int sphere9_line = 1;
float sphere9_z = 0;
float sphere9_x = 0;

int sphere10_line = 1;
float sphere10_z = 0;
float sphere10_x = 0;

int sphere11_line = 1;
float sphere11_z = 0;
float sphere11_x = 0;

int sphere12_line = 1;
float sphere12_z = 0;
float sphere12_x = 0;

int sphere13_line = 1;
float sphere13_z = 0;
float sphere13_x = 0;

int sphere14_line = 1;
float sphere14_z = 0;
float sphere14_x = 0;

int sphere15_line = 1;
float sphere15_z = 0;
float sphere15_x = 0;

int sphere16_line = 1;
float sphere16_z = 0;
float sphere16_x = 0;
float g = 0;
void idle(void)
{
	//lineup animatio
	if (start_line == 1)
	{
		if (sphere1_line == 0)
		{
			if (sphere1_z > -1.35)
			{
				if (sphere1_x < 0.15)
				{
					sphere1_x += 0.012;
				}
				sphere1_z -= 0.1;
				;
				sphere1_ctm = translation(sphere1_x, 0, sphere1_z);
			}
			else
			{
				sphere1_line = 1;
				sphere2_line = 0;
			}
		}

		if (sphere2_line == 0)
		{
			if (sphere2_z > -1.25)
			{
				if (sphere2_x < 0.05)
				{
					sphere2_x += 0.007;
				}
				sphere2_z -= 0.1;
				sphere2_ctm = translation(sphere2_x, 0, sphere2_z);
			}
			else
			{
				sphere2_line = 1;
				sphere3_line = 0;
			}
		}

		if (sphere3_line == 0)
		{
			if (sphere3_z > -1.15)
			{
				if (sphere3_x > -0.05)
				{
					sphere3_x -= 0.004;
				}
				sphere3_z -= 0.1;
				sphere3_ctm = translation(sphere3_x, 0, sphere3_z);
			}
			else
			{
				sphere3_line = 1;
				sphere4_line = 0;
			}
		}

		if (sphere4_line == 0)
		{
			if (sphere4_z > -1.05)
			{
				if (sphere4_x > -0.15)
				{
					sphere4_x -= 0.013;
				}
				sphere4_z -= 0.1;
				sphere4_ctm = translation(sphere4_x, 0, sphere4_z);
			}
			else
			{
				sphere4_line = 1;
				sphere5_line = 0;
			}
		}

		if (sphere5_line == 0)
		{
			if (sphere5_z > -1.05)
			{
				if (sphere5_x < 0.15)
				{
					sphere5_x += 0.015;
				}
				sphere5_z -= 0.1;
				sphere5_ctm = translation(sphere5_x, 0, sphere5_z);
			}
			else
			{
				sphere5_line = 1;
				sphere6_line = 0;
			}
		}

		if (sphere6_line == 0)
		{
			if (sphere6_z > -0.95)
			{
				if (sphere6_x < 0.05)
				{
					sphere6_x += 0.0075;
				}
				sphere6_z -= 0.1;
				sphere6_ctm = translation(sphere6_x, 0, sphere6_z);
			}
			else
			{
				sphere6_line = 1;
				sphere7_line = 0;
			}
		}

		if (sphere7_line == 0)
		{
			if (sphere7_z > -0.85)
			{
				if (sphere7_x > -0.05)
				{
					sphere7_x -= 0.005;
				}
				sphere7_z -= 0.1;
				sphere7_ctm = translation(sphere7_x, 0, sphere7_z);
			}
			else
			{
				sphere7_line = 1;
				sphere8_line = 0;
			}
		}

		if (sphere8_line == 0)
		{
			if (sphere8_z > -0.75)
			{
				if (sphere8_x > -0.15)
				{
					sphere8_x -= 0.025;
				}
				sphere8_z -= 0.1;
				sphere8_ctm = translation(sphere8_x, 0, sphere8_z);
			}
			else
			{
				sphere8_line = 1;
				sphere9_line = 0;
			}
		}

		if (sphere9_line == 0)
		{
			if (sphere9_z > -0.75)
			{
				if (sphere9_x < 0.15)
				{
					sphere9_x += 0.025;
				}
				sphere9_z -= 0.1;
				sphere9_ctm = translation(sphere9_x, 0, sphere9_z);
			}
			else
			{
				sphere9_line = 1;
				sphere10_line = 0;
			}
		}

		if (sphere10_line == 0)
		{
			if (sphere10_z > -0.65)
			{
				if (sphere10_x < 0.05)
				{
					sphere10_x += 0.01;
				}
				sphere10_z -= 0.1;
				sphere10_ctm = translation(sphere10_x, 0, sphere10_z);
			}
			else
			{
				sphere10_line = 1;
				sphere11_line = 0;
			}
		}

		if (sphere11_line == 0)
		{
			if (sphere11_z > -0.55)
			{
				if (sphere11_x > -0.05)
				{
					sphere11_x -= 0.01;
				}
				sphere11_z -= 0.1;
				sphere11_ctm = translation(sphere11_x, 0, sphere11_z);
			}
			else
			{
				sphere11_line = 1;
				sphere12_line = 0;
			}
		}

		if (sphere12_line == 0)
		{
			if (sphere12_z > -0.45)
			{
				if (sphere12_x > -0.15)
				{
					sphere12_x -= 0.03;
				}
				sphere12_z -= 0.1;
				sphere12_ctm = translation(sphere12_x, 0, sphere12_z);
			}
			else
			{
				sphere12_line = 1;
				sphere13_line = 0;
			}
		}

		if (sphere13_line == 0)
		{
			if (sphere13_z > -0.45)
			{
				if (sphere13_x < 0.15)
				{
					sphere13_x += 0.03;
				}
				sphere13_z -= 0.1;
				sphere13_ctm = translation(sphere13_x, 0, sphere13_z);
			}
			else
			{
				sphere13_line = 1;
				sphere14_line = 0;
			}
		}

		if (sphere14_line == 0)
		{
			if (sphere14_z > -0.35)
			{
				if (sphere14_x < 0.05)
				{
					sphere14_x += 0.017;
				}
				sphere14_z -= 0.1;
				sphere14_ctm = translation(sphere14_x, 0, sphere14_z);
			}
			else
			{
				sphere14_line = 1;
				sphere15_line = 0;
			}
		}

		if (sphere15_line == 0)
		{
			if (sphere15_z > -0.25)
			{
				if (sphere15_x > -0.05)
				{
					sphere15_x -= 0.017;
				}
				sphere15_z -= 0.1;
				sphere15_ctm = translation(sphere15_x, 0, sphere15_z);
			}
			else
			{
				sphere15_line = 1;
				sphere16_line = 0;
			}
		}
		if (sphere16_line == 0)
		{
			if (sphere16_z > -0.15)
			{
				if (sphere16_x > -0.15)
				{
					sphere16_x -= 0.075;
				}
				sphere16_z -= 0.1;
				sphere16_ctm = translation(sphere16_x, 0, sphere16_z);
			}
			else
			{
				sphere16_line = 1;
			}
		}
	}
	//circle animation
	if (start_circle == 1)
	{
		mat4 t = translation(sphere1_x, 0, sphere1_z);
		sphere1_ctm = matMult(rotateY(sphere1_degree), t);
		sphere1_degree += 1;

		t = translation(sphere2_x, 0, sphere2_z);
		sphere2_ctm = matMult(rotateY(sphere2_degree), t);
		sphere2_degree += 2;

		t = translation(sphere3_x, 0, sphere3_z);
		sphere3_ctm = matMult(rotateY(sphere3_degree), t);
		sphere3_degree += 3;

		t = translation(sphere4_x, 0, sphere4_z);
		sphere4_ctm = matMult(rotateY(sphere4_degree), t);
		sphere4_degree += 4;

		t = translation(sphere5_x, 0, sphere5_z);
		sphere5_ctm = matMult(rotateY(sphere5_degree), t);
		sphere5_degree += 5;

		t = translation(sphere6_x, 0, sphere6_z);
		sphere6_ctm = matMult(rotateY(sphere6_degree), t);
		sphere6_degree += 6;

		t = translation(sphere7_x, 0, sphere7_z);
		sphere7_ctm = matMult(rotateY(sphere7_degree), t);
		sphere7_degree += 7;

		t = translation(sphere8_x, 0, sphere8_z);
		sphere8_ctm = matMult(rotateY(sphere8_degree), t);
		sphere8_degree += 8;

		t = translation(sphere9_x, 0, sphere9_z);
		sphere9_ctm = matMult(rotateY(sphere9_degree), t);
		sphere9_degree += 9;

		t = translation(sphere10_x, 0, sphere10_z);
		sphere10_ctm = matMult(rotateY(sphere10_degree), t);
		sphere10_degree += 10;

		t = translation(sphere11_x, 0, sphere11_z);
		sphere11_ctm = matMult(rotateY(sphere11_degree), t);
		sphere11_degree += 11;

		t = translation(sphere12_x, 0, sphere12_z);
		sphere12_ctm = matMult(rotateY(sphere12_degree), t);
		sphere12_degree += 12;

		t = translation(sphere13_x, 0, sphere13_z);
		sphere13_ctm = matMult(rotateY(sphere13_degree), t);
		sphere13_degree += 13;

		t = translation(sphere14_x, 0, sphere14_z);
		sphere14_ctm = matMult(rotateY(sphere14_degree), t);
		sphere14_degree += 14;

		t = translation(sphere15_x, 0, sphere15_z);
		sphere15_ctm = matMult(rotateY(sphere15_degree), t);
		sphere15_degree += 15;

		//t = translation(sphere16_x,0,sphere16_z);
		//sphere16_ctm = matMult(rotateY(sphere16_degree),t);
		//sphere16_degree += 16;
	}


	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Project 3");
	glewInit();

	create_sphere();
	make_vertices();

	projection = frustum(-0.1, 0.1, -0.1, 0.1, -0.5, -20.0);
	model_view = look_at(0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);

	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutMainLoop();

	return 0;
}
