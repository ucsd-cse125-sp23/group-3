#pragma once
#include <core.h>
#include <Animation.h>
#include <Animator.h>
#include <DynamicShader.h>
#include <StaticShader.h>
#include <DynamicModel.h>
enum Action { idle, walking, action };
class DaeObject
{
public:
	DaeObject(const std::string model_path,
		const std::string walking_animation_path,
		const std::string action_animation_path,
		glm::vec3 scalingFactor = glm::vec3(1.0f, 1.0f, 1.0f));

	void draw(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& translate, DynamicShader& shader);
	void draw(const glm::mat4& projection, const glm::mat4& view, DynamicShader& shader);

	void updateAnimation(float deltaTime);
	void setTranslation(glm::vec3& translate);

	void update(glm::mat4 world);
	glm::mat4 getModel() { return mvp; };
	void setModel(glm::mat4 model);

	void spin(float deg);
	void move(float i);

	void doAction();


	glm::mat4 calculateMoveMVP(float i);
private:
	DynamicModel* objModel;
	Animation* animation_walking;
	Animation* animation_action;
	Animator* animator;

	glm::vec3 scale;
	glm::mat4 mvp;
	glm::vec3 translate;

	float lastFrame;
	float lastStartWalking;
	float lastStartAction;

	Action currentStatus;
};