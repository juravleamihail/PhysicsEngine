uniform mat4 u_rotMat;
attribute vec3 a_colL;
varying vec3 v_col;
attribute vec3 a_posL;
attribute vec2 a_uv;
varying vec2 v_uv;
varying vec2 v_uv2;

void main()
{
	v_col = a_colL;
	v_uv = a_uv;
	gl_Position = u_rotMat * vec4(a_posL, 1.0);
}