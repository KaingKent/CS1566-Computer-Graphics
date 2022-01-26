#version 120

attribute vec4 vPosition;
attribute vec4 vColor;
varying vec4 color;
attribute vec2 vTexCoord;
varying vec2 texCoord;

uniform mat4 ctm;
uniform mat4 model_view;
uniform mat4 projection_matrix;
void main()
{
	color = vColor;
	texCoord = vTexCoord;
	gl_Position = projection_matrix * model_view * ctm * vPosition;
}
