#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <glm/glm.hpp>

#include <string>

namespace Constants
{
	// Shader path
	const std::string static_shader_vert = "./shaders/model_loading.vs";
	const std::string static_shader_frag = "./shaders/model_loading.fs";
	
	const std::string ui_shader_vert = "./shaders/texture2D.vs";
	const std::string ui_shader_frag = "./shaders/texture2D.fs";

	const std::string dynamic_shader_vert = "./shaders/anim_model.vs";
	const std::string dynamic_shader_frag = "./shaders/anim_model.fs";

	// Alice model & anmiation
	const std::string alice_model_path = "./resources/objects/alice/alice.dae";
	const std::string alice_walking_animation_path = "./resources/objects/alice/animation/alice_walking.dae";
	const std::string alice_action_animation_path = "./resources/objects/alice/animation/alice_skill.dae";
	const std::string alice_attack_animation_path = "./resources/objects/alice/animation/alice_skill.dae";
	const std::string alice_win_animation_path = "./resources/objects/alice/animation/alice_victory.dae";
	const std::string alice_lose_animation_path = "./resources/objects/alice/animation/alice_lose.dae";
	const glm::vec3 alice_scaling_factor = glm::vec3(0.7f);

	const std::string bob_model_path = "./resources/objects/bob/bob.dae";
	const std::string bob_walking_animation_path = "./resources/objects/bob/animation/bob_walking.dae";
	const std::string bob_action_animation_path = "./resources/objects/bob/animation/bob_skill.dae";
	const std::string bob_attack_animation_path = "./resources/objects/bob/animation/bob_attack.dae";
	const std::string bob_win_animation_path = "./resources/objects/bob/animation/bob_victory.dae";
	const std::string bob_lose_animation_path = "./resources/objects/bob/animation/bob_lose.dae";
	const glm::vec3 bob_scaling_factor = glm::vec3(0.7f);

	const std::string carol_model_path = "./resources/objects/carol/carol.dae";
	const std::string carol_walking_animation_path = "./resources/objects/carol/animation/carol_walking.dae";
	const std::string carol_action_animation_path = "./resources/objects/carol/animation/carol_spell.dae";
	const std::string carol_attack_animation_path = "./resources/objects/carol/animation/carol_attack.dae";
	const std::string carol_win_animation_path = "./resources/objects/carol/animation/carol_victory.dae";
	const std::string carol_lose_animation_path = "./resources/objects/carol/animation/carol_lose.dae";
	const glm::vec3 carol_scaling_factor = glm::vec3(0.4f);

	const std::string dave_model_path = "./resources/objects/dave/dave.dae";
	const std::string dave_walking_animation_path = "./resources/objects/dave/animation/dave_walking.dae";
	const std::string dave_action_animation_path = "./resources/objects/dave/animation/dave_skill.dae";
	const std::string dave_attack_animation_path = "./resources/objects/dave/animation/dave_attack.dae";
	const std::string dave_win_animation_path = "./resources/objects/dave/animation/dave_victory.dae";
	const std::string dave_lose_animation_path = "./resources/objects/dave/animation/dave_lose.dae";
	const glm::vec3 dave_scaling_factor = glm::vec3(0.8f);

	// Obstacles model path
	const std::string bowlingpin_model_path = "./resources/objects/bowlingpin/bowlingpin.obj";
	const glm::vec3 bowlingpin_scaling_factor = glm::vec3(1.0f);

	const std::string cage_model_path = "./resources/objects/cage/cage_sketchfab.obj";
	const glm::vec3 cage_scaling_factor = glm::vec3(8.0f);

	const std::string door_model_path = "./resources/objects/door/door.obj";
	const glm::vec3 door_scaling_factor = glm::vec3(1.2f);

	// Scene model path
	const std::string exitdoor_model_path = "./resources/objects/exit/Exitdoor_tri.obj";
	const glm::vec3 exitdoor_scaling_factor = glm::vec3(1.0f);


	// Env
	const bool offline = false;
	const int DIST_LIMIT = 20;
	const float MINIMAP_OBJECT_SIZE=0.02f;

};
#endif
