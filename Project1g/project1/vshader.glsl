
#version 120

attribute vec4 vPosition;
attribute vec4 vColor;
attribute vec4 vNormal;
varying vec4 color;

varying vec4 N;
varying vec4 L;
varying vec4 V;
varying float distance;

uniform mat4 model_view_matrix;
uniform mat4 projection_matrix;
uniform mat4 ctm;
uniform vec4 light_position;
uniform int is_shadow;

void main()
{
	gl_Position = projection_matrix * model_view_matrix * ctm * vPosition;

	if(is_shadow == 0){
		color = vColor;
		gl_Position = projection_matrix * model_view_matrix * ctm * vPosition;
		N = normalize(model_view_matrix* ctm * vNormal);
		vec4 L_temp = model_view_matrix * (light_position - ctm * vPosition);
		L = normalize(L_temp);
		vec4 eye_point = vec4(0.0,0.0,0.0,1.0);
		V = normalize(eye_point-(model_view_matrix*ctm*vPosition));
		distance = length(L_temp);
	}else{
		vec4 current_position = ctm * vPosition;
		float x = light_position.x - light_position.y * ((light_position.x - current_position.x) / (light_position.y - current_position.y));
		float y = 0.001;
		float z = light_position.z - light_position.y * ((light_position.z - current_position.z) / (light_position.y - current_position.y));
		gl_Position = projection_matrix * model_view_matrix * vec4(x, y, z, 1);
		color = vec4(0,0,0,1);
	}
	

	
}
