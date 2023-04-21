#include "ObjObject.h"

ObjObject::ObjObject(const std::string path, glm::vec3 scalingFactor)
{
	objModel = new Model(path);

	mvp = glm::mat4(1.0f);
	translate = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = scalingFactor;
}

void ObjObject::draw(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& translate, Shader& shader)
{
	shader.use();

	shader.setMat4("projection", projection);
	shader.setMat4("view", view);

	this->translate = translate;

	mvp = glm::mat4(1.0f);
	mvp = glm::translate(mvp, translate); // translate it down so it's at the center of the scene
	mvp = glm::scale(mvp, scale);	
	shader.setMat4("model", mvp);
	objModel->Draw(shader);
}

void ObjObject::draw(const glm::mat4& projection, const glm::mat4& view, Shader& shader)
{
	shader.use();

	shader.setMat4("projection", projection);
	shader.setMat4("view", view);

	// If mvp is not calculated
	if (mvp == glm::mat4(1.0f))
	{
		mvp = glm::translate(mvp, translate);
	}
	glm::mat4 currMVP = glm::scale(mvp, scale);
	shader.setMat4("model", currMVP);
	objModel->Draw(shader);
}

void ObjObject::setTranslation(glm::vec3& translate)
{
	this->translate = translate;
}

void ObjObject::update(glm::mat4 world) 
{
	mvp = world;
}

void ObjObject::spin(float deg) 
{
	mvp = mvp * glm::rotate(glm::radians(deg), glm::vec3(0.0f, 1.0f, 0.0f));
}
void ObjObject::move(float i) 
{
	mvp = glm::translate(mvp, glm::vec3(0, 0, i));

}
