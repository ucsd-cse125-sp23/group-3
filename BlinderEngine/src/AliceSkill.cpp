#include "AliceSkill.h"

AliceSkill::AliceSkill(std::vector<Light*>& light) {

    systems.push_back(new Particles(1000, true, 5.0f, 0.1f, 0.8f, glm::vec3(0.8f, 0.8f, 1.0f)));
    systems[0]->bindTexture("./images/particle.png");
    systems.push_back(new Particles(1000, true, 5.0f, 0.1f, 0.8f, glm::vec3(0.8f, 0.8f, 1.0f)));
    systems[1]->bindTexture("./images/particle.png");
    systems.push_back(new Particles(1000, true, 5.0f, 0.1f, 0.8f, glm::vec3(0.8f, 0.8f, 1.0f)));
    systems[2]->bindTexture("./images/particle.png");
    systems.push_back(new Particles(1000, true, 5.0f, 0.1f, 0.8f, glm::vec3(0.8f, 0.8f, 1.0f)));
    systems[3]->bindTexture("./images/particle.png");

    light_index_start = light.size();
    for (int i = 0; i < 4; i++) {
        light.push_back(systems[i]->light);
        leadingparticles.push_back(new Particle());
        initial_pos.push_back(glm::vec3(0.0f));
    }
    particles_light = light;
    start = false;
    setup = false;
}

void AliceSkill::SetUp(glm::mat4 model) {
    if (!setup) {
        dest = glm::vec3(model * glm::vec4(0.0f, 3.0f, -8.0f, 1.0f));
        leadingparticles[0]->Position = glm::vec3(model * glm::vec4(-1.5f, 3.0f, -2.0f, 1.0f));
        leadingparticles[1]->Position = glm::vec3(model * glm::vec4(-0.5f, 3.0f, -2.0f, 1.0f));
        leadingparticles[2]->Position = glm::vec3(model * glm::vec4(0.5f, 3.0f, -2.0f, 1.0f));
        leadingparticles[3]->Position = glm::vec3(model * glm::vec4(1.5f, 3.0f, -2.0f, 1.0f));
        initial_pos[0] = leadingparticles[0]->Position;
        initial_pos[1] = leadingparticles[1]->Position;
        initial_pos[2] = leadingparticles[2]->Position;
        initial_pos[3] = leadingparticles[3]->Position;

        leadingparticles[0]->Velocity = (dest - leadingparticles[0]->Position) / 2000.0f;
        leadingparticles[1]->Velocity = (dest - leadingparticles[1]->Position) / 2000.0f;
        leadingparticles[2]->Velocity = (dest - leadingparticles[2]->Position) / 2000.0f;
        leadingparticles[3]->Velocity = (dest - leadingparticles[3]->Position) / 2000.0f;
        start = true;
        setup = true;
    }
}

void AliceSkill::update(float dt) {
    if (start) {
        for (int i = 0; i < 4; i++) {
            leadingparticles[i]->Position += leadingparticles[i]->Velocity * dt;
            systems[i]->Update(dt, leadingparticles[i]->Velocity, leadingparticles[i]->Position, 1, glm::vec3(0.0f));
            *(particles_light[light_index_start + i]) = *(systems[i]->light);
            if (glm::length(leadingparticles[i]->Position - initial_pos[i]) / glm::length(leadingparticles[i]->Velocity) >= 2000.0f) {
                start = false;
            }
        }
    }
    else {
        for (int i = 0; i < 4; i++) {
            systems[i]->Update(dt, leadingparticles[i]->Velocity, leadingparticles[i]->Position, 0, glm::vec3(0.0f));
            *(particles_light[light_index_start + i]) = *(systems[i]->light);
        }
    }
}

void AliceSkill::draw(StaticShader shader, const glm::mat4& viewProjMtx) {
    for (int i = 0; i < 4; i++) {
        systems[i]->Draw(shader, viewProjMtx);
    }
}
