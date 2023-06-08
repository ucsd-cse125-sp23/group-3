#include <DaeObject.h>

DaeObject::DaeObject(const std::string model_path,
	const std::string walking_animation_path,
	const std::string action_animation_path,
	const std::string attack_animation_path,
	const std::string win_animation_path,
	const std::string lose_animation_path,
	glm::vec3 scalingFactor)
{
	objModel = new DynamicModel(model_path);

	animation_walking = new Animation(walking_animation_path, objModel);
	animation_action = new Animation(action_animation_path, objModel);
	animation_attack = new Animation(attack_animation_path, objModel);
	animation_win = new Animation(win_animation_path, objModel);
	animation_lose = new Animation(lose_animation_path, objModel);

	lastStartWalking = std::numeric_limits<float>::min();
	lastStartAction = std::numeric_limits<float>::min();
	lastStartAttack = std::numeric_limits<float>::min();
	lastStartLose = std::numeric_limits<float>::min();

	placed = false;

	animator = new Animator(animation_walking);
	animator->UpdateAnimation(0.0f);

	mvp = glm::mat4(1.0f);
	mvp = mvp * glm::rotate(glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	translate = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = scalingFactor;
	currentStatus = Action::idle;
	gameStatus = GameStatus::playing;
	animated = true;
}

DaeObject::DaeObject(const std::string model_path, glm::vec3 scalingFactor)
{
	objModel = new DynamicModel(model_path);
	mvp = glm::mat4(1.0f);
	translate = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = scalingFactor;
	currentStatus = Action::idle;
	animated = false;
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
	if (animated)
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
		if (!Constants::offline) 
		{
			currMVP = currMVP * glm::rotate(glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		}
		shader.setMat4("model", currMVP);

		// Animation
		float currentFrame = glfwGetTime();
		float deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		//std::cerr << "Animation->GetDuration = " << animation->GetDuration() << std::endl;
		//std::cerr << "DeltaFrames = " << currentFrame - lastStartWalking << std::endl;
		if (gameStatus == GameStatus::win) 
		{
			updateAnimation(deltaTime);
		}
		else if (gameStatus == GameStatus::lose)
		{
			if (currentFrame - lastStartLose < animation_lose->GetDuration()/2 / 1000 - 0.2)
			{
				updateAnimation(deltaTime);
			}
		}
		else if (currentFrame - lastStartAttack < animation_attack->GetDuration() / 1000 &&\
			currentFrame - lastPressedAttack < 0.00001)
		{
			if (currentStatus != Action::attack)
			{
				animator->PlayAnimation(animation_attack);
				currentStatus = Action::attack;
			}
			updateAnimation(deltaTime);
		}
		else if (currentFrame - lastStartAction < animation_action->GetDuration() / 1000)
		{
			if (currentStatus != Action::action)
			{
				animator->PlayAnimation(animation_action);
				currentStatus = Action::action;
			}
			updateAnimation(deltaTime);
		}
		else if (currentFrame - lastStartWalking < animation_walking->GetDuration() / 1000)
		{
			if (currentStatus != Action::walking)
			{
				animator->PlayAnimation(animation_walking);
				currentStatus = Action::walking;
			}
			updateAnimation(deltaTime);
		}
		else {
			animator->PlayAnimation(animation_walking);
			currentStatus = Action::idle;
		}
		objModel->Draw(shader);
	}
	else 
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
		if (!Constants::offline) {
			currMVP = currMVP * glm::rotate(glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		}
		shader.setMat4("model", currMVP);
		objModel->Draw(shader);
	}
	
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

glm::vec3 DaeObject::getTranslation()
{
	return glm::vec3(mvp[3][0], mvp[3][1], mvp[3][2]);
}

void DaeObject::setModel(glm::mat4 &model)
{
	// If there is no delta between 2 frames, do nothing,
	// If not, update the mvp and set walk fram
	if (mvp != model)
	{
		float currentFrame = glfwGetTime();
		if (placed && currentFrame - lastStartWalking >= animation_walking->GetDuration() / 1000)
		{
			lastStartWalking = currentFrame;
		}
		placed = true;
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

void DaeObject::doWalk()
{
	float currentFrame = glfwGetTime();
	if (currentFrame - lastStartWalking >= animation_walking->GetDuration() / 1000)
	{
		lastStartWalking = currentFrame;
	}
}

void DaeObject::doAction()
{
	float currentFrame = glfwGetTime();
	if (currentFrame - lastStartAction >= animation_action->GetDuration() / 1000)
	{
		lastStartAction = currentFrame;
	}
}

void DaeObject::doAttack()
{
	float currentFrame = glfwGetTime();
	if (currentFrame - lastStartAttack >= animation_attack->GetDuration() / 1000)
	{
		lastStartAttack = currentFrame;
	}
	lastPressedAttack = currentFrame;
}

glm::mat4 DaeObject::calculateMoveMVP(float i)
{
	return glm::translate(mvp, glm::vec3(0, 0, -i));
}

void DaeObject::doWin()
{
	gameStatus = GameStatus::win;
	animator->PlayAnimation(animation_win);

}

void DaeObject::doLose()
{
	std::cout << "doLose" << std::endl;
	gameStatus = GameStatus::lose;
	animator->PlayAnimation(animation_lose);

	float currentFrame = glfwGetTime();
	lastStartLose = currentFrame;

}

void DaeObject::resetAnimation()
{
	placed = false;
	currentStatus = Action::idle;
	gameStatus = GameStatus::playing;
}


