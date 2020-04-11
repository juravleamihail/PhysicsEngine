precision mediump float;
varying vec3 v_col;
varying vec2 v_uv;
varying vec2 v_uv2;
vec2 v_uv_displaced;
varying vec3 v_coord;
uniform sampler2D texture_0; //DisplacementMap
uniform sampler2D texture_1; //fire3.tga
uniform sampler2D texture_2; //fire.mask.tga
uniform float u_Time;
uniform float u_DispMax;

void main()
{
	vec2 disp;
	disp = texture2D(texture_0, vec2(v_uv.x, v_uv.y + u_Time)).xy;
	vec4 c_fire = vec4(0.0,0.0,1.0,1.0);
	vec4 c_alpha = vec4(0.0,0.0,1.0,1.0);

	v_uv_displaced = v_uv + ((disp * 2.0) - 1.0) * u_DispMax;

	c_fire = texture2D(texture_1, v_uv_displaced);
	c_alpha = texture2D(texture_2, v_uv);
	c_fire.a = c_fire.a * c_alpha.x;

	if (c_fire.a < 0.1)
	{
		discard;
	}

	gl_FragColor = c_fire;
}
