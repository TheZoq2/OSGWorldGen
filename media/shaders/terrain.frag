varying vec3 v_normals;
varying float v_lightAmount;

void main(void)
{
	v_lightAmount = 0.5 + (v_lightAmount * 0.5);

	gl_FragColor = vec4(1., 1., 1., 1.) * v_lightAmount;
}
