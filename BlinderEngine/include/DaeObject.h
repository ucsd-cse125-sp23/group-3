#pragma once
#include <core.h>
#include <Animation.h>
#include <Animator.h>
#include <BShader.h>
#include <MShader.h>
#include <DynamicModel.h>

class DaeObject
{
public:
	DaeObject(const std::string path, glm::vec3 scalingFactor = glm::vec3(1.0f, 1.0f, 1.0f));

	void draw(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& translate, BShader& shader);
	void draw(const glm::mat4& projection, const glm::mat4& view, BShader& shader);

	void updateAnimation(float deltaTime);
	void setTranslation(glm::vec3& translate);

	void update(glm::mat4 world);
	glm::mat4 getModel() { return mvp; };
	void spin(float deg);
	void move(float i);
private:
	DynamicModel* objModel;
	Animation* animation;
	Animator* animator;

	glm::vec3 scale;
	glm::mat4 mvp;
	glm::vec3 translate;
};