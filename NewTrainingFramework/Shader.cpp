#include "stdafx.h"
#include "Shader.h"

#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include


Shader::Shader()
{
}

Shader::~Shader()
{
}

void Shader::Load()
{
	sr->vertexShader = esLoadShader(GL_VERTEX_SHADER, &sr->vsPath[0u]);

	sr->fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, &sr->fsPath[0u]);

	//if (vertexShader == 0)
	//	return -1;

	//if (fragmentShader == 0)
	//{
	//	glDeleteShader(vertexShader);
	//	return -2;
	//}

	programId = esLoadProgram(sr->vertexShader, sr->fragmentShader);

	//finding location of uniforms / attributes
	sr->positionAttribute = glGetAttribLocation(programId, "a_posL");
	sr->colorAttribute = glGetAttribLocation(programId, "a_colL");
	sr->rotationMatrixUniform = glGetUniformLocation(programId, "u_rotMat");

	sr->uniformTexture[0] = glGetUniformLocation(programId, "texture_0");
	sr->uniformTexture[1] = glGetUniformLocation(programId, "texture_1");
	sr->uniformTexture[2] = glGetUniformLocation(programId, "texture_2");
	sr->uniformTexture[3] = glGetUniformLocation(programId, "texture_3");
	sr->uniformTexture[4] = glGetUniformLocation(programId, "texture_4");
	sr->uniformTexture[5] = glGetUniformLocation(programId, "texture_5");

	sr->textureCoordAttribute = glGetAttribLocation(programId, "a_uv");
	sr->textureCoordAttribute2 = glGetAttribLocation(programId, "a_uv2");

	sr->heightUniform = glGetUniformLocation(programId, "height");

	sr->modelUniform = glGetUniformLocation(programId, "model");
	sr->smallRadiusUniform = glGetUniformLocation(programId, "smallRadius");
	sr->wideRadiusUniform = glGetUniformLocation(programId, "wideRadius");
	sr->fogColorUniform = glGetUniformLocation(programId, "fogColor");
	sr->camPosUniform = glGetUniformLocation(programId, "camPos");

	sr->u_TimeUniform = glGetUniformLocation(programId, "u_Time");
	sr->dispMaxUniform = glGetUniformLocation(programId, "u_DispMax");

	sr->c_ambUniform = glGetUniformLocation(programId, "c_amb");
	sr->c_luminaDiffUniform[0] = glGetUniformLocation(programId, "c_luminaDiff0");
	sr->c_luminaDiffUniform[1] = glGetUniformLocation(programId, "c_luminaDiff1");
	sr->c_luminaDiffUniform[2] = glGetUniformLocation(programId, "c_luminaDiff2");
	sr->c_luminaSpecUniform[0] = glGetUniformLocation(programId, "c_luminaSpec0");
	sr->c_luminaSpecUniform[1] = glGetUniformLocation(programId, "c_luminaSpec1");
	sr->c_luminaSpecUniform[2] = glGetUniformLocation(programId, "c_luminaSpec2");
	sr->a_normalUniform[0] = glGetAttribLocation(programId, "a_normal0");
	sr->a_normalUniform[1] = glGetAttribLocation(programId, "a_normal1");
	sr->a_normalUniform[2] = glGetAttribLocation(programId, "a_normal2");
	sr->directionLightUniform[0] = glGetUniformLocation(programId, "directionLight0");
	sr->directionLightUniform[1] = glGetUniformLocation(programId, "directionLight1");
	sr->directionLightUniform[2] = glGetUniformLocation(programId, "directionLight2");
	sr->SpecPowerUniform[0] = glGetUniformLocation(programId, "SpecPower0");
	sr->SpecPowerUniform[1] = glGetUniformLocation(programId, "SpecPower1");
	sr->SpecPowerUniform[2] = glGetUniformLocation(programId, "SpecPower2");
	sr->ratioAmbientalUniform = glGetUniformLocation(programId, "ratioAmbiental");
	//return 0;
}