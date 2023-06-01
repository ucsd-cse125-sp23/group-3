#include "Fog.h"
#include <limits>


Fog::Fog()
{
	fogDistance = std::numeric_limits<float>::max();
}

void Fog::setFogDistance(float fogDistance)
{
	this->fogDistance = fogDistance;
}

void Fog::updateFog(GLuint shaderID, glm::vec3 playerPos)
{
	glUseProgram(shaderID);
	GLuint fog_player_pos, fog_fog_distance;
	fog_player_pos = glGetUniformLocation(shaderID, "fog.player_pos");
	fog_fog_distance = glGetUniformLocation(shaderID, "fog.fog_distance");
	glUniform3f(fog_player_pos, playerPos[0], playerPos[1], playerPos[2]);
	glUniform1f(fog_fog_distance, fogDistance);
}

void Fog::shrinkFog(float shrinkDistance)
{
	this->fogDistance -= shrinkDistance;
}
