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