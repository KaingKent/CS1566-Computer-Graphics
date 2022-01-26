#version 120

varying vec4 color, N, L, V;
varying float distance;
//uniform int use_texture;
uniform float shininess;
uniform float attenuation_constant,attenuation_linear,attenuation_quadratic;
vec4 ambient, diffuse, specular;

void main()
{
	vec4 the_color = color;
	//if(use_texture == 1){
		//the_color = texture2D(texture,texCoord);
	//}

	vec4 NN = normalize(N);
	vec4 VV = normalize(V);
	vec4 LL = normalize(L);

	ambient = the_color * 0.2;
	vec4 H = normalize(LL + VV);
	diffuse = max(dot(LL,NN),0.0) * 0.8 * the_color;
	specular = pow(max(dot(NN,H),0.0),shininess) * vec4(1.0,1.0,1.0,1.0);
	float attenuation = 1/(attenuation_constant + (attenuation_linear * distance) + 
						(attenuation_quadratic * distance * distance));

	gl_FragColor = ambient + attenuation * (diffuse + specular);
}
