/*
 * template.c
 *
 * An OpenGL source code template.
 */


#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../mylib/initShader.h"
#include "../mylib/linear_alg.h"
//#include "../mylib/geo_objs.h"


#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))

int num_vertices = 3678;
//int num_triangles = 360/(num_vertices/3);
float x_prev;
float y_prev;
float z_prev;
int test = 0;
#define triangles 3000

vec4 circle[3678];
vec4 color[3678];

vec4 vertices[62430];
vec4 colors[62430];

vec4 sphere1_location;
vec4 sphere2_location;
vec4 sphere3_location;
vec4 sphere4_location;
vec4 sphere5_location;
vec4 sphere6_location = {-0.2, 0.1, 0.2, 1};
vec4 sphere7_location = {0.2, 0.1, 0.2, 1};
vec4 sphere8_location;
vec4 sphere9_location;
vec4 sphere10_location = {-0.2, 0.1, -0.2, 1};
vec4 sphere11_location = {0.2, 0.1, -0.2, 1};
vec4 sphere12_location;
vec4 sphere13_location;
vec4 sphere14_location;
vec4 sphere15_location;
vec4 sphere16_location;

float sphere1_degree= 0.0;
float sphere2_degree= 0.0;
float sphere3_degree= 0.0;
float sphere4_degree= 0.0;
float sphere5_degree= 0.0;
float sphere6_degree= 0.0;
float sphere7_degree= 0.0;
float sphere8_degree= 0.0;
float sphere9_degree= 0.0;
float sphere10_degree= 0.0;
float sphere11_degree= 0.0;
float sphere12_degree= 0.0;
float sphere13_degree= 0.0;
float sphere14_degree= 0.0;
float sphere15_degree= 0.0;
float sphere16_degree= 0.0;

mat4 sphere1_ctm = {{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}};
mat4 sphere2_ctm = {{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}};
mat4 sphere3_ctm = {{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}};
mat4 sphere4_ctm = {{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}};
mat4 sphere5_ctm = {{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}};
mat4 sphere6_ctm = {{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}};
mat4 sphere7_ctm = {{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}};
mat4 sphere8_ctm = {{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}};
mat4 sphere9_ctm = {{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}};
mat4 sphere10_ctm = {{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}};
mat4 sphere11_ctm = {{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}};
mat4 sphere12_ctm = {{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}};
mat4 sphere13_ctm = {{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}};
mat4 sphere14_ctm = {{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}};
mat4 sphere15_ctm = {{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}};
mat4 sphere16_ctm = {{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}};

mat4 bulb_ctm = {{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}};

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

GLuint model_view_location;
mat4 model_view = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

GLuint projection_location;
mat4 projection = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

GLuint light_position_location;

vec4 light_position = {0,1,0,1};
//vec4 light_ambient = {0.1,0.1,0.1,1.0};
//vec4 light_diffuse = {1.0,1.0,1.0,1.0};
//vec4 light_specular = {1.0,1.0,1.0,1.0};

vec4* sphere()
{
	int offset = 0;
	vec4 initial = {0.5, 0.0, 0.0, 1.0};
	vec4 initial2 = {0.5, 0.0, 0.0, 1.0};
	
	for(int j = 0; j < 8; j++)
	{	
	
		for(int i = 0; i < 36; i++)
		{	
			vec4 p3 = multMV(rotateY(i*10), multMV(rotateY(10), multMV(rotateZ(10), initial)));
			vec4 p2 = multMV(rotateY(i*10), multMV(rotateY(10), initial));
			vec4 p1 = multMV(rotateY(i*10), initial);
			vec4 p4 = multMV(rotateY(i*10), multMV(rotateZ(10), initial));
			
			circle[offset] = p1;
			circle[offset+1] = p2;
			circle[offset+2] = p3;
			circle[offset+3] = p1;
			circle[offset+4]= p3;
			circle[offset+5] =p4;
			
			vec4 p3a = multMV(rotateY(i*10), multMV(rotateY(-10), multMV(rotateZ(-10), initial2)));
			vec4 p2a = multMV(rotateY(i*10), multMV(rotateY(-10), initial2));
			vec4 p1a = multMV(rotateY(i*10), initial2);
			vec4 p4a = multMV(rotateY(i*10), multMV(rotateZ(-10), initial2));
			
			circle[offset+6] = p1a;
			circle[offset+7] = p2a;
			circle[offset+8] = p3a;
			circle[offset+9] = p1a;
			circle[offset+10]= p3a;
			circle[offset+11] =p4a;
			
			offset+= 12;
		}
		
		initial =multMV(rotateZ(10), initial);
		initial2= multMV(rotateZ(-10), initial2);
	}
	
	vec4 top = {0.0, 0.5, 0.0, 1.0};
	vec4 bot = {0.0, -0.5, 0.0, 1.0};
	for(int i = 0; i < 36; i++)
	{
		//offset = final * 3 *2;
		vec4 p1 = multMV(rotateY(i*10), initial);
		vec4 p2 = multMV(rotateY(i*10), multMV(rotateY(10), initial));
		
		circle[offset] = top;
		circle[offset+1] = p1;
		circle[offset+2] = p2;
		
		vec4 p3 = multMV(rotateY(i*10), initial2);
		vec4 p4 = multMV(rotateY(i*10), multMV(rotateY(-10), initial2));
		
		circle[offset+3] = bot;
		circle[offset+4] = p3;
		circle[offset+5] = p4;
		
		offset+=6;
	}
	return circle;
}

vec4* colorF()
{
	for(int i = 0; i < 1224; i++)
	{	
		float x = (float)rand() / (float)(RAND_MAX);
		float y = (float)rand() / (float)(RAND_MAX);
		float z = (float)rand() / (float)(RAND_MAX);
			
		int offset = i*3;
		color[offset].x = x;
		color[offset].y = y;
		color[offset].z = z;
		color[offset].w = 1.0;
		
		color[offset+1].x = x;
		color[offset+1].y = y;
		color[offset+1].z = z;
		color[offset+1].w = 1.0;
		
		color[offset+2].x = x;
		color[offset+2].y = y;
		color[offset+2].z = z;
		color[offset+2].w = 1.0;
	}

	return color;
}

void normals(){

	vec4 origin = {0,0,0,1};
	for(int i = 0; i < 1224; i++)
	{	
		int offset = i*3;

		color[offset] = subV(circle[offset], origin);
		color[offset+1] = subV(circle[offset+1], origin);
		color[offset+2] = subV(circle[offset+2], origin);
	}
}

void create_vertices(){
	int i = 0;
    int v_index = 0;

	mat4 s = scaling(0.1,0.1,0.1);
	mat4 sphere6_translation = translation(-0.05, 0.1, -0.05);
	mat4 sphere7_translation = translation(0.05, 0.1, -0.05);
	mat4 sphere10_translation = translation(-0.05, 0.1, 0.05);
	mat4 sphere11_translation = translation(0.05, 0.1, 0.05);

	mat4 sphere1_translation = translation(-0.15, 0.1, -0.15);
	mat4 sphere2_translation = translation(-0.05, 0.1, -0.15);
	mat4 sphere3_translation = translation(0.05, 0.1, -0.15);
	mat4 sphere4_translation = translation(0.15, 0.1, -0.15);

	mat4 sphere5_translation = translation(-0.15, 0.1, -0.05);
	mat4 sphere8_translation = translation(0.15, 0.1, -0.05);
	mat4 sphere9_translation = translation(-0.15, 0.1, 0.05);
	mat4 sphere12_translation = translation(0.15, 0.1, 0.05);

	mat4 sphere13_translation = translation(-0.15, 0.1, 0.15);
	mat4 sphere14_translation = translation(-0.05, 0.1, 0.15);
	mat4 sphere15_translation = translation(0.05, 0.1, 0.15);
	mat4 sphere16_translation = translation(0.15, 0.1, 0.15);

	for(i = 0; i < 3672; i++){//1
		vertices[v_index] = multMV(multM(sphere1_translation,s),circle[i]);
		colors[v_index] = color[i];
		v_index++;
	}

	for(i = 0; i < 3672; i++){//2
		vertices[v_index] = multMV(multM(sphere2_translation,s),circle[i]);
		colors[v_index] = color[i];
		v_index++;
	}

	for(i = 0; i < 3672; i++){//3
		vertices[v_index] = multMV(multM(sphere3_translation,s),circle[i]);
		colors[v_index] = color[i];
		v_index++;
	}

	for(i = 0; i < 3672; i++){//4
		vertices[v_index] = multMV(multM(sphere4_translation,s),circle[i]);
		colors[v_index] = color[i];
		v_index++;
	}

	for(i = 0; i < 3672; i++){//5
		vertices[v_index] = multMV(multM(sphere5_translation,s),circle[i]);
		colors[v_index] = color[i];
		v_index++;
	}

	for(i = 0; i < 3672; i++){//6
		vertices[v_index] = multMV(multM(sphere6_translation,s),circle[i]);
		colors[v_index] = color[i];
		v_index++;
	}

	for(i = 0; i < 3672; i++){//7
		vertices[v_index] = multMV(multM(sphere7_translation,s),circle[i]);
		colors[v_index] = color[i];
		v_index++;
	}

	for(i = 0; i < 3672; i++){//8
		vertices[v_index] = multMV(multM(sphere8_translation,s),circle[i]);
		colors[v_index] = color[i];
		v_index++;
	}

	for(i = 0; i < 3672; i++){//9
		vertices[v_index] = multMV(multM(sphere9_translation,s),circle[i]);
		colors[v_index] = color[i];
		v_index++;
	}

	for(i = 0; i < 3672; i++){//10
		vertices[v_index] = multMV(multM(sphere10_translation,s),circle[i]);
		colors[v_index] = color[i];
		v_index++;
	}
	for(i = 0; i < 3672; i++){//11
		vertices[v_index] = multMV(multM(sphere11_translation,s),circle[i]);
		colors[v_index] = colors[i];
		v_index++;
	}

	for(i = 0; i < 3672; i++){//12
		vertices[v_index] = multMV(multM(sphere12_translation,s),circle[i]);
		colors[v_index] = color[i];
		v_index++;
	}

	for(i = 0; i < 3672; i++){//13
		vertices[v_index] = multMV(multM(sphere13_translation,s),circle[i]);
		colors[v_index] = colors[i];
		v_index++;
	}

	for(i = 0; i < 3672; i++){//14
		vertices[v_index] = multMV(multM(sphere14_translation,s),circle[i]);
		colors[v_index] = color[i];
		v_index++;
	}

	for(i = 0; i < 3672; i++){//15
		vertices[v_index] = multMV(multM(sphere15_translation,s),circle[i]);
		colors[v_index] = color[i];
		v_index++;
	}

	for(i = 0; i < 3672; i++){//16
		vertices[v_index] = multMV(multM(sphere16_translation,s),circle[i]);
		colors[v_index] = color[i];
		v_index++;
	}

	mat4 bulb_scale = scaling(.05,.05,.05);
	mat4 bulb_translation = translation(0,1,0);

	for(i = 0; i < 3672; i++){//bulb
		vertices[v_index] = multMV(multM(bulb_translation,bulb_scale),circle[i]);
		vec4 white = {1,1,1,1};
		colors[v_index] = white;
		v_index++;
	}

	vec4 f1 = {-5, 0, -5, 1};
    vec4 f2 = {5, 0,-5, 1};
    vec4 f5 = {5, 0, 5, 1};
    vec4 f6 = {-5, 0, 5, 1};
	

	vertices[62424] = f6;
	vertices[62425] = f5;
	vertices[62426] = f2;
	vertices[62427] = f2;
	vertices[62428] = f1;
	vertices[62429] = f6;

	vec4 v1 = subV(vertices[62425],vertices[62424]);
   	vec4 v2 = subV(vertices[62426],vertices[62425]);
    vec4 cross = crossV(v1, v2);
    vec4 norm = normV(cross);

	colors[62424] = norm;
	colors[62425] = norm;
	colors[62426] = norm;

	v1 = subV(vertices[62428],vertices[62427]);
   	v2 = subV(vertices[62429],vertices[62428]);
    cross = crossV(v1, v2);
    norm = normV(cross);
	colors[62427] = norm;
	colors[62428] = norm;
	colors[62429] = norm;

}

void mouse(int button, int state, int x, int y){
	
	if(button == 3)
	{
		ctm = multM(ctm, scaling(1.2, 1.2, 1.2));	
	}
	else if(button == 4)
	{
		ctm = multM(ctm, scaling(1/1.2, 1/1.2, 1/1.2));
	}
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(x >= 256){
        		x_prev = (x - 255)/ 256.0;
    		}
    		else if(x < 256)
    		{
      			x_prev = (x - 256)/ 256.0;
    		}

    		if(y <= 256)
    		{
        		y_prev = -(y - 256)/ 256.0;
    		}
    		else if(y > 256)
    		{
        		y_prev = -(y - 255)/ 256.0;
    		}
		z_prev = sqrt(1 - (x_prev*x_prev) - (y_prev*y_prev));
	}
	
	//printf("xp: %f yp: %f \n\n", x_prev, y_prev);
}

void motion(int x, int y){
   	float x_pt = 0;
   	float y_pt = 0;
   	float z_pt = 0;
   	
	if(x > 511){
        	x = 511;
     	}
     	else if(x < 0){
        	x = 0;
    	}
   	if(y > 511){
        	y = 511;
    	}
    	else if(y < 0){
        	y = 0;
    	}
    	
    	if(x >= 256){
        	x_pt = (x - 255)/ 256.0;
    	}
    	else if(x < 256){
        	x_pt = (x - 256)/ 256.0;
    	}

    	if(y <= 256){
        	y_pt = -(y - 256)/ 256.0;
    	}
    	else if(y > 256){
        	y_pt = -(y - 255)/ 256.0;
    	}

    	z_pt = sqrt(1 - (x_pt*x_pt) - (y_pt*y_pt));
	
	
	
    	vec4 p1 = {x_prev, y_prev, z_prev, 0};
    	vec4 p2 = {x_pt, y_pt, z_pt, 0};

    	float thetaZ = acos(dotV(p2,p1)/(magV(p1) * magV(p2))) * 180/M_PI;

	if(thetaZ == thetaZ){ //check if nan
        	vec4 arb = crossV(p1,p2);
        	vec4 v = normV(arb);

        	float d = sqrt((v.y*v.y) + (v.z*v.z));
        	mat4 rx = rotateX(0);
        	rx.y.y = v.z/d;
        	rx.z.y = -(v.y)/d;
        	rx.y.z = (v.y)/d;
        	rx.z.z = v.z/d;
		
        	mat4 rx_neg = transpose(rx);

        	mat4 ry_neg = rotateY(0);
        	ry_neg.x.x = d;
        	ry_neg.x.z = v.x;
        	ry_neg.z.x = -v.x;
        	ry_neg.z.z = d;

       	mat4 ry = transpose(ry_neg);

        	mat4 m1 = multM(ry_neg, rx);
        	//printM(m1);
        	mat4 m2 = multM(rotateZ(thetaZ), m1);
        	//printM(m2);
        	mat4 m3 = multM(ry, m2);
        	//printM(m3);
        	mat4 r = multM(rx_neg, m3);
        	//printM(r);

        	ctm = multM(r, ctm);

    	}
	

    	x_prev = x_pt;
    	y_prev = y_pt;
    	z_prev = z_pt;

}

void init(void)
{
    GLuint program = initShader("vshader.glsl", "fshader.glsl");
    glUseProgram(program);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors);


    GLuint vPosition = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition/*unsigned int*/, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)/*starting index*/);
	
	GLuint vColor = glGetAttribLocation(program, "vColor");
    glEnableVertexAttribArray(vColor);
    glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *) sizeof(vertices)/*offset of where to start next*/);

    GLuint vNormal = glGetAttribLocation(program, "vNormal");
    glEnableVertexAttribArray(vNormal);
    glVertexAttribPointer(vNormal, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *) sizeof(vertices)/*offset of where to start next*/);
	
	

    ctm_location = glGetUniformLocation(program, "ctm"); //set up ctm
 
	model_view_location = glGetUniformLocation(program, "model_view_matrix");
    glUniformMatrix4fv(model_view_location, 1, GL_FALSE, (GLfloat *)&model_view);
	projection_location = glGetUniformLocation(program, "projection_matrix");
    glUniformMatrix4fv(projection_location, 1, GL_FALSE, (GLfloat *)&projection);
    light_position_location = glGetUniformLocation(program, "light_position");
    //glUniform4fv(light_position_location, 1, (GLfloat *) &light_position);
    is_shadow_location = glGetUniformLocation(program, "is_shadow");
    shininess_location = glGetUniformLocation(program,"shininess");
	a_constant_location = glGetUniformLocation(program,"attenuation_constant");
	a_linear_location = glGetUniformLocation(program,"attenuation_linear");
	a_quadratic_location = glGetUniformLocation(program,"attenuation_quadratic");

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glDepthRange(1,0);
    
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);
    
    //mat4 s = scaling(0.5, 1, 0.5);
    //mat4 r = rotateX(-45);
    //qctm = multM(r, ctm); //scale then rotate
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUniform4fv(light_position_location, 1, (GLfloat *) &light_position);
	glUniformMatrix4fv(model_view_location, 1, GL_FALSE, (GLfloat *)&model_view);
	glUniform1fv(shininess_location, 1, (GLfloat *) &shininess);
	glUniform1fv(a_linear_location, 1, (GLfloat *) &a_linear);
	glUniform1fv(a_constant_location, 1, (GLfloat *) &a_constant);
	glUniform1fv(a_quadratic_location, 1, (GLfloat *) &a_quadratic);

	glUniform1i(is_shadow_location, 0);
	glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &sphere1_ctm); //sends to graphics pipeline
	glDrawArrays(GL_TRIANGLES, 0, 3672);
	glUniform1i(is_shadow_location, 1); //sends to graphics pipeline
	glDrawArrays(GL_TRIANGLES, 0, 3672);

	glUniform1i(is_shadow_location, 0);
	glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &sphere2_ctm);
	glDrawArrays(GL_TRIANGLES, 3672, 3672);
	glUniform1i(is_shadow_location, 1);
	glDrawArrays(GL_TRIANGLES, 3672, 3672);
	
	glUniform1i(is_shadow_location, 0);
	glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &sphere3_ctm);
	glDrawArrays(GL_TRIANGLES, 7344, 3672);
	glUniform1i(is_shadow_location, 1);
	glDrawArrays(GL_TRIANGLES, 7344, 3672);

	glUniform1i(is_shadow_location, 0);
	glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &sphere4_ctm);
	glDrawArrays(GL_TRIANGLES, 11016, 3672);
	glUniform1i(is_shadow_location, 1);
	glDrawArrays(GL_TRIANGLES, 11016, 3672);

	glUniform1i(is_shadow_location, 0);
	glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &sphere5_ctm); //sends to graphics pipeline
	glDrawArrays(GL_TRIANGLES, 14688, 3672);
	glUniform1i(is_shadow_location, 1); //sends to graphics pipeline
	glDrawArrays(GL_TRIANGLES, 14688, 3672);

	glUniform1i(is_shadow_location, 0);
	glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &sphere6_ctm);
	glDrawArrays(GL_TRIANGLES, 18360, 3672);
	glUniform1i(is_shadow_location, 1);
	glDrawArrays(GL_TRIANGLES, 18360, 3672);
	
	glUniform1i(is_shadow_location, 0);
	glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &sphere7_ctm); //sends to graphics pipeline
	glDrawArrays(GL_TRIANGLES, 22032, 3672);
	glUniform1i(is_shadow_location, 1); //sends to graphics pipeline
	glDrawArrays(GL_TRIANGLES, 22032, 3672);

	glUniform1i(is_shadow_location, 0);
	glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &sphere8_ctm);
	glDrawArrays(GL_TRIANGLES, 25704, 3672);
	glUniform1i(is_shadow_location, 1);
	glDrawArrays(GL_TRIANGLES, 25704, 3672);
	
	glUniform1i(is_shadow_location, 0);
	glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &sphere9_ctm);
	glDrawArrays(GL_TRIANGLES, 29376, 3672);
	glUniform1i(is_shadow_location, 1);
	glDrawArrays(GL_TRIANGLES, 29376, 3672);

	glUniform1i(is_shadow_location, 0);
	glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &sphere10_ctm);
	glDrawArrays(GL_TRIANGLES, 33048, 3672);
	glUniform1i(is_shadow_location, 1);
	glDrawArrays(GL_TRIANGLES, 33048, 3672);

	glUniform1i(is_shadow_location, 0);
	glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &sphere11_ctm);
	glDrawArrays(GL_TRIANGLES, 36720, 3672);
	glUniform1i(is_shadow_location, 1);
	glDrawArrays(GL_TRIANGLES, 36720, 3672);

	glUniform1i(is_shadow_location, 0);
	glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &sphere12_ctm);
	glDrawArrays(GL_TRIANGLES, 40492, 3672);
	glUniform1i(is_shadow_location, 1);
	glDrawArrays(GL_TRIANGLES, 40492, 3672);

	glUniform1i(is_shadow_location, 0);
	glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &sphere13_ctm); //sends to graphics pipeline
	glDrawArrays(GL_TRIANGLES, 44064, 3672);
	glUniform1i(is_shadow_location, 1); //sends to graphics pipeline
	glDrawArrays(GL_TRIANGLES, 44064, 3672);

	glUniform1i(is_shadow_location, 0);
	glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &sphere14_ctm);
	glDrawArrays(GL_TRIANGLES, 47736, 3672);
	glUniform1i(is_shadow_location, 1);
	glDrawArrays(GL_TRIANGLES, 47736, 3672);

	glUniform1i(is_shadow_location, 0);
	glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &sphere15_ctm);
	glDrawArrays(GL_TRIANGLES, 51408, 3672);
	glUniform1i(is_shadow_location, 1);
	glDrawArrays(GL_TRIANGLES, 51408, 3672);

	glUniform1i(is_shadow_location, 0);
	glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &sphere16_ctm);
	glDrawArrays(GL_TRIANGLES, 55080, 3672);
	glUniform1i(is_shadow_location, 1);
	glDrawArrays(GL_TRIANGLES, 55080, 3672);
	
	glUniform1i(is_shadow_location, 0);
	glDrawArrays(GL_TRIANGLES, 62424, 6);
	
	glUniform1i(is_shadow_location, 0);
	glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &bulb_ctm);
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
float upz= -1;

float t =0;

void keyboard(unsigned char key, int mousex, int mousey)
{
    if(key == 'q'){
		glutLeaveMainLoop();
	}
    if(key == 's'){//x decrease
		bulbx -= 0.1;
		lightx -= 0.1;
	}
	if(key == 'w'){//x increase
		bulbx += 0.1;
		lightx += 0.1;
	}
	if(key == 'e'){//y increase
		bulby += 0.1;
		lighty += 0.1;
		//light_position.y = 1.1;
	}
	if(key == 'd'){//y decrease	
		bulby -= 0.1;
		lighty -= 0.1;
	}
	if(key == 'r'){//z increase
		bulbz += 0.1;
		lightz += 0.1;
		//light_position.y = 1.1;
	}
	if(key == 'f'){//z decrease	
		bulbz -= 0.1;
		lightz -= 0.1;
	}

	
	//printf("%f", theta);

	if(key == 'y'){//closer
		//t += 0.1;
		d-=0.1;
		eyex = d * sin(phi * (M_PI / 180)) * cos(theta * (M_PI / 180));
		eyey = d * sin((phi ) * (M_PI / 180)) * sin((theta) * (M_PI / 180));
		eyez = d * cos((phi) * (M_PI / 180));
		//model_view = look_at(0, 1, 0, 0,0,0,0,0,1);
	}
	if(key == 'h'){//farther
		d+=0.1;
		eyex = d * sin(phi * (M_PI / 180)) * cos(theta * (M_PI / 180));
		eyey = d * sin((phi) * (M_PI / 180)) * sin((theta ) * (M_PI / 180));
		eyez = d * cos((phi) * (M_PI / 180));
	}
	if(key == 'i'){//up
		upy = 0;
		upz= -1;
		theta+=1;
		eyex = d * sin((phi) * (M_PI / 180)) * cos(theta * (M_PI / 180));
		eyey = d * sin((phi) * (M_PI / 180)) * sin((theta) * (M_PI / 180));
		eyez = d * cos((phi) * (M_PI / 180));

	}
	if(key == 'k'){//down
		upy = 0;
		upz= -1;
		theta-=1;
		eyex = d * sin((phi) * (M_PI / 180)) * cos(theta * (M_PI / 180));
		eyey = d * sin((phi) * (M_PI / 180)) * sin((theta) * (M_PI / 180));
		eyez = d * cos((phi) * (M_PI / 180));

	}
	if(key == 'j'){//left
		upy = 1;
		upz= 0;
		t+=1;
		eyey = cos(t * (M_PI / 180));
      	eyez = sin(t * (M_PI / 180));
	}
	if(key == 'l'){//right
		upy = 1;
		upz= 0;
		t-=1;
		eyey = cos(t * (M_PI / 180));
      	eyez = sin(t * (M_PI / 180));
	}

	//printf("%c", key);
	//eyex = d * sin((phi) * (M_PI / 180)) * cos(theta * (M_PI / 180));
	//eyey = d * sin((phi) * (M_PI / 180)) * sin((theta) * (M_PI / 180));
	//eyez = d * cos((phi) * (M_PI / 180));

	//printf("x:%f y:%f z:%f\n", eyez, eyex, eyey);

	model_view = look_at(eyez, eyex, eyey, 0,0,0,0,upy,upz);
	//glutPostRedisplay();
	vec4 l = {lightx, lighty, lightz,1};
	light_position = l;
	bulb_ctm = translation(bulbx, bulby, bulbz);

    glutPostRedisplay();
}

void reshape(int width, int height)
{
    glViewport(0, 0, 512, 512);
}

//int is_spinning = 1;
float x = 1;
void idle(void)// idle already behaves like a loop
{   
	//model_view = look_at(0,x,0,0,0,0,0,0,-1);
	//bulb_ctm = translation(x, 1, 0);
	//sphere1_ctm = rotateY(x);
	///x += .1;
	//glutPostRedisplay();
	/*

	glutPostRedisplay();
	*/
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Template");
    glewInit();
    
    sphere();
    //colorF();
	normals();
	create_vertices();

	//model_view = look_at(0, .01, .01, 0, 0, 0, 0, 1, 0);
	projection = frustum(-0.1, 0.1, -0.1, 0.1, -0.5, -20.0);
	//projection = ortho(-2, 2, -2, 2, 2, -2);
	model_view = look_at(0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);
    //model_view = look_at(0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutMainLoop();

    return 0;
}

