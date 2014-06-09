uniform mat4 gl_ModelViewMatrix;
uniform mat4 gl_ProjectionMatrix;
uniform mat3 gl_NormalMatrix;

attribute vec4 gl_Vertex;
attribute vec3 gl_Normal;

//The amount of sunlight cast on the terrain
varying float v_lightAmount;

vec3 lightPos = vec3(500, 500, 245);

void main(void)
{
	vec4 position = gl_ModelViewMatrix * gl_Vertex;

	gl_Position = gl_ProjectionMatrix * position;//gl_ModelViewMatrix * gl_Vertex;

	//Calculating normals
	vec3 normals = gl_Normal;

	vec4 sunDir = normalize(vec4(lightPos, 0) - position);

	v_lightAmount = dot(vec4(normalize(normals), 1), sunDir);
	//v_lightAmount = dot(normals, vec3(0., 1., 0.));
}
