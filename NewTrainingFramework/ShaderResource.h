#include <string>
#pragma once

class ShaderResource
{
public:
	int vertexShader, fragmentShader;
	int positionAttribute;
	int rotationMatrixUniform;
	int heightUniform;
	int modelUniform, viewUniform, projectionUniform;
	int camPosUniform;
	int smallRadiusUniform, wideRadiusUniform, fogColorUniform;
	int c_ambUniform, c_luminaDiffUniform[3], c_luminaSpecUniform[3], a_normalUniform[3], directionLightUniform[3], SpecPowerUniform[3], ratioAmbientalUniform; //light
	int u_TimeUniform, dispMaxUniform;
	int uniformTexture[6];
	int colorAttribute;
	int textureCoordAttribute, textureCoordAttribute2;
	std::string vsPath;
	std::string fsPath;
};
