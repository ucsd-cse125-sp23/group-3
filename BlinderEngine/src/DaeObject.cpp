#include <DaeObject.h>

DaeObject::DaeObject(const std::string path, glm::vec3 scalingFactor)
{
	objModel = new DynamicModel(path);
	animation = new Animation(path, objModel);
	animator = new Animator(animation);
	animator->UpdateAnimation(0.0f);

	mvp = glm::mat4(1.0f);
	mvp = mvp * glm::rotate(glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	translate = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = scalingFactor;
}

void DaeObject::draw(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& translate, DynamicShader& shader)
{
	shader.use();

	auto transforms = animator->GetFinalBoneMatrices();
	for (int i = 0; i < transforms.size(); ++i)
		shader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);

	shader.setMat4("projection", projection);
	shader.setMat4("view", view);

	this->translate = translate;
	mvp = glm::mat4(1.0f);
	mvp = glm::translate(mvp, translate); // translate it down so it's at the center of the scene
	mvp = glm::scale(mvp, scale);
	shader.setMat4("model", mvp);
	objModel->Draw(shader);
}

void DaeObject::draw(const glm::mat4& projection, const glm::mat4& view, DynamicShader& shader)
{
	shader.use();

	auto transforms = animator->GetFinalBoneMatrices();
	for (int i = 0; i < transforms.size(); ++i)
		shader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);

	shader.setMat4("projection", projection);
	shader.setMat4("view", view);

	// If mvp is not calculated
	if (mvp == glm::mat4(1.0f))
	{
		mvp = glm::translate(mvp, translate);
	}
	glm::mat4 currMVP = glm::scale(mvp, scale);
	shader.setMat4("model", currMVP);

	// Animation
	float currentFrame = glfwGetTime();
	float deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	//std::cerr << "Animation->GetDuration = " << animation->GetDuration() << std::endl;
	//std::cerr << "DeltaFrames = " << currentFrame - lastStartWalking << std::endl;
	if (currentFrame - lastStartWalking < animation->GetDuration() / 1000)
	{
		this->updateAnimation(deltaTime);
	}

	objModel->Draw(shader);
}

void DaeObject::updateAnimation(float deltaTime)
{
	animator->UpdateAnimation(deltaTime);
}

void DaeObject::setTranslation(glm::vec3& translate)
{
	this->translate = translate;
}



void DaeObject::update(glm::mat4 world)
{
	mvp = world;
}

void DaeObject::setModel(glm::mat4 model)
{
	// If there is no delta between 2 frames, do nothing,
	// If not, update the mvp and set walk fram
	if (mvp != model)
	{
		float currentFrame = glfwGetTime();
		if (currentFrame - lastStartWalking >= animation->GetDuration() / 1000)
		{
			lastStartWalking = currentFrame;
		}
		mvp = model;
	}
}

void DaeObject::spin(float deg)
{
	mvp = mvp * glm::rotate(glm::radians(deg), glm::vec3(0.0f, 1.0f, 0.0f));
}

void DaeObject::move(float i)
{
	//float currentFrame = glfwGetTime();
	//if (currentFrame - lastStartWalking >= animation->GetDuration() / 1000) 
	//{
	//	lastStartWalking = currentFrame;
	//}
	mvp = glm::translate(mvp, glm::vec3(0, 0, -i));
}

glm::mat4 DaeObject::calculateMoveMVP(float i)
{
	return glm::translate(mvp, glm::vec3(0, 0, -i));
}


