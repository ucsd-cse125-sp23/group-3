#include "Fog.h"
#include <limits>


Fog::Fog()
{
	fogDistance = std::numeric_limits<float>::max();
	staticFrames = 300;
}

void Fog::setFogDistance(float fogDistance)
{
	this->fogDistance = fogDistance;
}

void Fog::updateFog(GLuint shaderID, glm::vec3 playerPos, int width, int height)
{
	glUseProgram(shaderID);
	GLuint fog_player_pos, fog_fog_distance;
	fog_player_pos = glGetUniformLocation(shaderID, "fog.player_pos");
	fog_fog_distance = glGetUniformLocation(shaderID, "fog.fog_distance");
	glUniform3f(fog_player_pos, playerPos[0], playerPos[1], playerPos[2]);
	glUniform1f(fog_fog_distance, fogDistance);
	GLuint windowWidthID, windowHeightID;
	windowWidthID = glGetUniformLocation(shaderID, "windowWidth");
	windowHeightID = glGetUniformLocation(shaderID, "windowHeight");
	glUniform1i(windowWidthID, width);
	glUniform1i(windowHeightID, height);
}

void Fog::shrinkFog()
{
	if (fogDistance > 100) {
		fogDistance -= 3.0f;
	}
	else if (staticFrames == 0)
	{
		fogDistance -= 1.0f;
	}
	else
	{
		staticFrames--;
	}


}

void Fog::reset()
{

	fogDistance = std::numeric_limits<float>::max();
}
