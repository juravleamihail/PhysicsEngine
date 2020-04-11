precision mediump float;
varying vec3 v_col;
varying vec2 v_texture_coord;
uniform sampler2D texture_1;
void main()
{
	//gl_FragColor = vec4(v_col,1.0);
	vec4 color = vec4(0.0,1.0,0.0,1.0);
	//color = texture2D(texture_1,v_texture_coord);
	if (color.a < 0.1)
	{
		discard;
	}
	gl_FragColor = color;
}
