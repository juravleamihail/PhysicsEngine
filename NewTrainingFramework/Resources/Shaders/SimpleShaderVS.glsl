uniform mat4 u_rotMat;
attribute vec3 a_colL;
varying vec3 v_col;
attribute vec3 a_posL;
attribute vec2 a_uv;
varying vec2 v_uv;
varying vec2 v_uv2;

varying vec3 v_posL;
uniform mat4 model;

attribute vec4 N, L;
varying vec3 v_normal0;
attribute vec3 a_normal0;

void main()
{
	v_col = a_colL;
	v_uv = a_uv;
	v_posL = (model * vec4(a_posL, 1.0)).xyz;
	v_normal0 = (model * vec4(a_normal0, 0.0)).xyz;

	gl_Position = u_rotMat * vec4(a_posL, 1.0);
}
   