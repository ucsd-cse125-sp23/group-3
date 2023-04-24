#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <glm/glm.hpp>
#include <string>

namespace Constants
{
	// Define object path
	const std::string nanosuit_object_path = "./resources/objects/nanosuit/nanosuit.obj";
	const std::string backpack_object_path = "./resources/objects/backpack/backpack.obj";
	const std::string rock_object_path = "./resources/objects/rock/rock.obj";

	// Define scaling factor for objects
	const glm::vec3 nanosuit_scaling_factor = glm::vec3(0.5f, 0.5f, 0.5f);
	const glm::vec3 backpack_scaling_factor = glm::vec3(2.0f, 2.0f, 2.0f);
	const glm::vec3 rock_scaling_factor = glm::vec3(5.0f, 5.0f, 5.0f);
	const bool offline = true;
};
#endif
