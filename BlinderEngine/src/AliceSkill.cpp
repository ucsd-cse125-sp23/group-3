#include "AliceSkill.h"

AliceSkill::AliceSkill() {
    /*leading1 = new Particle();
    leading2 = new Particle();
    leading3 = new Particle();
    leading4 = new Particle();
    ;*/
    system1 = new Particles(1000, true, 5.0f, 0.1f, 0.8f, glm::vec3(0.8f, 0.8f, 1.0f));
    system1->bindTexture("./images/particle.png");
    start = false;
    end = false;
}

void AliceSkill::SetUp(glm::mat4 model) {
    /*leading1->position = vec3(model * glm::vec4(-1.5f, 1.0f, 2.0f, 1.0f));
    leading2->position = vec3(model * glm::vec4(-0.5f, 1.0f, 2.0f, 1.0f));
    leading3->position = vec3(model * glm::vec4(0.5f, 1.0f, 2.0f, 1.0f));
    leading4->position = vec3(model * glm::vec4(1.5f, 1.0f, 2.0f, 1.0f));*/
    // lights->particles_light.push_back(particles_2->light);
    // leading->Position=glm::vec3(3.0f,3.0f,0.0f);
    // leading->Velocity = glm::vec3(0.1f, 0.0f, 0.1f) * 5.0f;
    
    /* double newtimer = glfwGetTime();
    float dt = (newtimer - timer);
    timer = newtimer;
    if (usingSkill && skillTime > 0) {

        skillTime -= 0.0003f;
        //leading->Position+=leading->Velocity*dt;
        //UPDATION FOR SYSTEM +LIGHT AT END
        leading->Position += leading->Velocity * dt;
        particles_2->Update(dt, leading->Velocity, leading->Position, 1, glm::vec3(0.0f));
        //lights->particles_light[0]=particles_2->light;
        // lights->particles_light[0]=particles_2->light;
    }
    else {
        particles_2->Update(dt, leading->Velocity, leading->Position, 0, glm::vec3(0.0f));
        usingSkill = false;
        skillTime = 1.0f;

    }
    lights->particles_light[0] = particles_2->light;*/
}

/*
* 
* Ending position of the particle

bool Server::check_detectability(int obs_id)
{
    glm::mat4* loc = &this->gd->location_A;
    glm::vec4 transf(0, 0, -2*ATTACK_RANGE, 1);
    glm::vec4 ahead_point = *loc * transf;
    glm::vec2 player_pt(ahead_point[0], ahead_point[2]);
    float* pSourceObs = (float*)glm::value_ptr(map->obs->glm_vec[obs_id]);
    glm::vec2 centerObs(pSourceObs[12], pSourceObs[14]);
    return glm::length(player_pt - centerObs) < 2*ATTACK_RANGE;
}

*/
