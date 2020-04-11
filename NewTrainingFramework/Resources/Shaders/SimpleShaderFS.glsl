precision mediump float;
varying vec3 v_col;
varying vec2 v_uv;
varying vec2 v_uv2;
uniform sampler2D texture_0;
vec4 colObj;

//fog
uniform float smallRadius, wideRadius;
uniform vec3 fogColor;
varying vec3 v_posL;
uniform vec3 camPos;
float dist;
float alpha;

//light
uniform vec4 c_luminaDiff0, c_luminaSpec0;
uniform vec3 c_amb;
varying vec3 v_normal0;
uniform vec4 directionLight0;
uniform float SpecPower0;
uniform float ratioAmbiental;

void main()
{
	vec4 color = vec4(0.0,0.0,1.0,1.0);
	color = texture2D(texture_0,v_uv);

	if (color.a < 0.1)
	{
		discard;
	}

	dist = distance(v_posL,camPos);
	alpha = clamp((dist - smallRadius) / (wideRadius - smallRadius),0.0,1.0);

	//light
	colObj = vec4(alpha * fogColor + ((1.0 - alpha) * color.xyz),1.0);
	vec4 N = vec4(normalize(v_normal0.xyz),0.0);
	vec4 L = vec4(normalize(directionLight0.xyz),0.0);
	vec4 R = reflect(L,N);
	vec4 E = vec4(normalize(camPos - v_posL),0.0);
	vec4 Comp_amb = colObj * vec4(c_amb,1.0);
	vec4 Cdiff = colObj * c_luminaDiff0 * max(dot(N,-L), 0.0);
	vec4 Cspec = c_luminaSpec0 * pow(max(dot(R,E), 0.0), SpecPower0);
	vec4 Cfinal = Comp_amb * ratioAmbiental + ( Cdiff + Cspec) * (1.0 - ratioAmbiental);
	Cfinal.a = colObj.a;

	//gl_FragColor = vec4(alpha * fogColor + ((1.0 - alpha) * color.xyz),1.0);
	gl_FragColor = Cfinal;

//	if(c_amb.r == 0.0)
//	{
//		gl_FragColor = vec4(c_amb,1.0);
//	}
//	else
//		gl_FragColor = vec4(c_amb,1.0);
}
