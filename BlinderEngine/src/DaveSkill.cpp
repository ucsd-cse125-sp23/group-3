#include "DaveSkill.h"

DaveSkill::DaveSkill(std::vector<Light*>& light) {

    systems.push_back(new Particles(1000, true, 5.0f, 0.5f, 1.8f, glm::vec3(0.8f, 0.8f, 1.0f)));
    systems[0]->bindTexture("./images/particle.png");
    /*systems.push_back(new Particles(1000, true, 5.0f, 0.1f, 1.8f, glm::vec3(0.8f, 0.8f, 1.0f)));
    systems[1]->bindTexture("./images/particle.png");
    systems.push_back(new Particles(1000, true, 5.0f, 0.1f, 1.8f, glm::vec3(0.8f, 0.8f, 1.0f)));
    systems[2]->bindTexture("./images/particle.png");
    systems.push_back(new Particles(1000, true, 5.0f, 0.1f, 1.8f, glm::vec3(0.8f, 0.8f, 1.0f)));
    systems[3]->bindTexture("./images/particle.png");*/

    light_index_start = light.size();
    for (int i = 0; i < 4; i++) {
        // light.push_back(systems[i]->light);
        leadingparticles.push_back(new Particle());
        initial_pos.push_back(glm::vec3(0.0f));
    }
    particles_light = light;
    start = false;
    setup = false;
}

void DaveSkill::SetUp(glm::mat4 model) {
    if (!setup) {
        // light position glm::vec3(model * glm::vec4(0.0f, 3.0f, 0.0f, 1.0f))
        _model = model;
        angle = 0.0f;
        radius = 3.0f;
        ending_height = 10.0f;
        height = 2.0f;
        glm::vec3 relative_position = glm::vec3(radius * sin(angle), height, radius * cos(angle));
        leadingparticles[0]->Position = relative_position;
        /*leadingparticles[1]->Position = glm::vec3(model * glm::vec4(-0.5f, 3.0f, -2.0f, 1.0f));
        leadingparticles[2]->Position = glm::vec3(model * glm::vec4(0.5f, 3.0f, -2.0f, 1.0f));
        leadingparticles[3]->Position = glm::vec3(model * glm::vec4(1.5f, 3.0f, -2.0f, 1.0f));
        initial_pos[0] = leadingparticles[0]->Position;
        initial_pos[1] = leadingparticles[1]->Position;
        initial_pos[2] = leadingparticles[2]->Position;
        initial_pos[3] = leadingparticles[3]->Position;*/
        leadingparticles[0]->Velocity = glm::vec3(0.0f);
        //std::cout << "setup" << std::endl;
        
        start = true;
        setup = true;
    }
}

void DaveSkill::update(float dt, glm::mat4 model) {
    if (start) {
        angle += dt;
        height += dt;
        _model = model;
        glm::vec3 relative_position = glm::vec3(radius * sin(angle), height, radius * cos(angle));
        leadingparticles[0]->Position = relative_position;
        systems[0]->Update(dt, leadingparticles[0]->Velocity, leadingparticles[0]->Position, 1, glm::vec3(0.0f));
        if (height >= ending_height) {
            start = false;
            setup = false;
        }

    }
    else {
        // for (int i = 0; i < 4; i++) {
            systems[0]->Update(dt, leadingparticles[0]->Velocity, leadingparticles[0]->Position, 0, glm::vec3(0.0f));
            // *(particles_light[light_index_start + i]) = *(systems[i]->light);
        // }
    }
}

void DaveSkill::draw(StaticShader shader, const glm::mat4& viewProjMtx) {
    // for (int i = 0; i < 4; i++) {
        systems[0]->Draw(_model,shader, viewProjMtx);
        //std::cout << "drawing" << std::endl;
    // } 
}
