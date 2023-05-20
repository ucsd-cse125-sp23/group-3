#include "AliceSkill.h"

AliceSkill::AliceSkill() {
    leading1 = new Particle();
    leading2 = new Particle();
    leading3 = new Particle();
    leading4 = new Particle();
    start = false;
    end = false;
}

void AliceSkill::SetUp(glm::mat4 model) {
    leading1->position = vec3(model * glm::vec4(-1.5f, 1.0f, 2.0f, 1.0f));
    leading2->position = vec3(model * glm::vec4(-0.5f, 1.0f, 2.0f, 1.0f));
    leading3->position = vec3(model * glm::vec4(0.5f, 1.0f, 2.0f, 1.0f));
    leading4->position = vec3(model * glm::vec4(1.5f, 1.0f, 2.0f, 1.0f));
}