uniform mat4 u_rotMat;
attribute vec3 a_colL;
varying vec3 v_col;
attribute vec3 a_posL;
attribute vec2 a_uv;
attribute vec2 a_uv2;
varying vec2 v_uv;
varying vec2 v_uv2;
uniform vec3 height;
vec4 c_blend;
uniform sampler2D texture_3;

varying vec3 v_posL;
uniform mat4 model;
varying vec3 v_normal0;
attribute vec3 a_normal0;

void main()
{
	v_col = a_colL;
	v_uv = a_uv;
	v_uv2 = a_uv2;
	v_normal0 = (model * vec4(a_normal0, 0.0)).xyz;
	//gl_Position = u_rotMat * vec4(a_posL, 1.0);
	c_blend = texture2D(texture_3, a_uv);
	vec3 pos_nou = a_posL;
	pos_nou.y = pos_nou.y + (c_blend.r * height.r +c_blend.g * height.g + c_blend.b * height.b);
	v_posL = (model * vec4(a_posL, 1.0)).xyz;
	gl_Position = u_rotMat * vec4(pos_nou, 1.0);
}
   