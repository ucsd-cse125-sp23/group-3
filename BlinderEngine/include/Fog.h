#pragma once
#include <core.h>
#include <StaticShader.h>
#include <DynamicShader.h>

class Fog
{
public:
	Fog();
	void setFogDistance(float fogDistance);
	void updateFog(GLuint shaderID, glm::vec3 playerPos, int width, int height);
	void shrinkFog();

private:
	float fogDistance;
	int staticFrames;
};
