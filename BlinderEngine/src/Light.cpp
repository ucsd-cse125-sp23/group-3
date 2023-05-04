#include "Light.h"

Light::Light(glm::vec3 _position, glm::vec3 _direction, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, bool spotlight) {
	position = _position;
	direction = _direction;
	ambient = _ambient;
	diffuse = _diffuse;
	specular = _specular;
	spotLight = spotlight;
}

Light::~Light() {

}

void Light::SetLighttoDShader(DynamicShader shader) {
	shader.use();
	glUniform3f(glGetUniformLocation(shader.ID, "lightPos"), position.x,position.y,position.z);
	glUniform3f(glGetUniformLocation(shader.ID, "lightDir"), direction.x, direction.y, direction.z);
}

void Light::SetLighttoSShader(StaticShader shader) {
	shader.use();
	glUniform3f(glGetUniformLocation(shader.ID, "lightPos"), position.x, position.y, position.z);
	glUniform3f(glGetUniformLocation(shader.ID, "lightDir"), direction.x, direction.y, direction.z);
}