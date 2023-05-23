#include "AliceSkill.h"

AliceSkill::AliceSkill(std::vector<Light*> &light){

    systems.push_back(new Particles(1000,true,5.0f,0.1f,0.8f,glm::vec3(0.8f,0.8f,1.0f)));
    systems[0]->bindTexture("./images/particle.png");
    systems.push_back(new Particles(1000,true,5.0f,0.1f,0.8f,glm::vec3(0.8f,0.8f,1.0f)));
    systems[1]->bindTexture("./images/particle.png");
    systems.push_back(new Particles(1000,true,5.0f,0.1f,0.8f,glm::vec3(0.8f,0.8f,1.0f)));
    systems[2]->bindTexture("./images/particle.png");
    systems.push_back(new Particles(1000,true,5.0f,0.1f,0.8f,glm::vec3(0.8f,0.8f,1.0f)));
    systems[3]->bindTexture("./images/particle.png");

    light_index_start=light.size();
    for(int i=0;i<4;i++){
        light.push_back(systems[i]->light);
        leadingparticles.push_back(new Particle());
    }
    particles_light=light;
    start=false;
    setup=false;
}

void AliceSkill::SetUp(glm::mat4 model){
    if(!setup){
        leadingparticles[0]->Position=glm::vec3(model*glm::vec4(-1.5f,2.0f,-2.0f,1.0f));
        leadingparticles[1]->Position=glm::vec3(model*glm::vec4(-0.5f,2.0f,-2.0f,1.0f));
        leadingparticles[2]->Position=glm::vec3(model*glm::vec4(0.5f,2.0f,-2.0f,1.0f));
        leadingparticles[3]->Position=glm::vec3(model*glm::vec4(1.5f,2.0f,-2.0f,1.0f));

        leadingparticles[0]->Velocity=glm::vec3(model*glm::vec4(0.05f,0.02f,-0.4f,0.0f))*2.0f;
        leadingparticles[1]->Velocity=glm::vec3(model*glm::vec4(0.025f,0.02f,-0.4f,0.0f))*2.0f;
        leadingparticles[2]->Velocity=glm::vec3(model*glm::vec4(-0.025f,0.02f,-0.4f,0.0f))*2.0f;
        leadingparticles[3]->Velocity=glm::vec3(model*glm::vec4(-0.05f,0.02f,-0.4f,0.0f))*2.0f;
        start=true;
        setup=true;
    }
}

void AliceSkill::update(float dt){
    if(start){
        for(int i=0;i<4;i++){
            leadingparticles[i]->Position+=leadingparticles[i]->Velocity*dt;
            systems[i]->Update(dt,leadingparticles[i]->Velocity,leadingparticles[i]->Position,1,glm::vec3(0.0f));
            *(particles_light[light_index_start+i])=*(systems[i]->light);
        }
    }else{
        for(int i=0;i<4;i++){
            systems[i]->Update(dt,leadingparticles[i]->Velocity,leadingparticles[i]->Position,0,glm::vec3(0.0f));
            *(particles_light[light_index_start+i])=*(systems[i]->light);
        }
    }
}

void AliceSkill::draw(Shader shader,const glm::mat4& viewProjMtx,glm::mat4 camView){
    for(int i=0;i<4;i++){
        systems[i]->Draw(shader,viewProjMtx ,camView);
    }
}
   
    