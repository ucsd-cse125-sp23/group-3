#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <glm/glm.hpp>

#include <string>

namespace Constants
{
	const std::string static_shader_vert = "./shaders/model_loading.vs";
	const std::string static_shader_frag = "./shaders/model_loading.fs";
	
	const std::string ui_shader_vert = "./shaders/texture2D.vs";
	const std::string ui_shader_frag = "./shaders/texture2D.fs";

	const std::string dynamic_shader_vert = "./shaders/anim_model.vs";
	const std::string dynamic_shader_frag = "./shaders/anim_model.fs";

	// Define object path
	const std::string nanosuit_object_path = "./resources/objects/nanosuit/nanosuit.obj";
	const std::string backpack_object_path = "./resources/objects/backpack/backpack.obj";
	const std::string rock_object_path = "./resources/objects/rock/rock.obj";
	const std::string drone_object_path = "./resources/objects/uav/uav.dae";

	const std::string drone_object_animation = "./resources/objects/uav/uav.dae";

	// Define scaling factor for objects
	const glm::vec3 nanosuit_scaling_factor = glm::vec3(0.5f, 0.5f, 0.5f);
	const glm::vec3 backpack_scaling_factor = glm::vec3(2.0f, 2.0f, 2.0f);
	const glm::vec3 rock_scaling_factor = glm::vec3(5.0f, 5.0f, 5.0f);
	const glm::vec3 drone_scaling_factor = glm::vec3(1.0f, 1.0f, 1.0f);

	// Girl model & animation
	const std::string girl_model_path = "./resources/objects/girl/girl.dae";
	const std::string girl_walking_animation_path = "./resources/objects/girl/animation/girl_walking.dae";
	const std::string girl_action_animation_path = "./resources/objects/girl/animation/girl_dribbling.dae";
	const glm::vec3 girl_scaling_factor = glm::vec3(3.0f);


	// Alice model & anmiation
	const std::string alice_model_path = "./resources/objects/alice/alice.dae";
	const std::string alice_walking_animation_path = "./resources/objects/alice/animation/walking.dae";
	const std::string alice_action_animation_path = "./resources/objects/alice/animation/dancing.dae";
	const glm::vec3 alice_scaling_factor = glm::vec3(0.7f);

	const bool offline = false;


	const int DIST_LIMIT = 20;

	const float MINIMAP_OBJECT_SIZE=0.02;

};
#endif
