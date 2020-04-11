uniform mat4 u_rotMat;
attribute vec3 a_colL;
varying vec3 v_col;
attribute vec3 a_posL;
attribute vec2 texture_coord;
varying vec2 v_texture_coord;

void main()
{
	v_col = a_colL;
	v_texture_coord = texture_coord;
	gl_Position = u_rotMat * vec4(a_posL, 1.0);
}
   