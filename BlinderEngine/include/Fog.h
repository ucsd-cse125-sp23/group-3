#pragma once
#include <core.h>
#include <StaticShader.h>
#include <DynamicShader.h>

class Fog
{
public:
	Fog();
	void setFogDistance(float fogDistance);
	void updateFog(GLuint shaderID, glm::vec3 playerPos);
	void shrinkFog(float shrinkDistance);

private:
	float fogDistance;
};
