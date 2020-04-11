precision mediump float;
varying vec3 v_col;
varying vec2 v_uv;
varying vec2 v_uv2;
varying vec3 v_coord;
uniform samplerCube texture_0;
void main()
{
	//gl_FragColor = vec4(v_col,1.0);
	vec4 color = vec4(0.0,0.0,1.0,1.0);
	
	color = textureCube(texture_0, v_coord);

	gl_FragColor = color;
}