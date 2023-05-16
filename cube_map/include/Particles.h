#pragma once

#include <vector>
#include <utility>
#include "core.h"
#include "Light.h"

struct Particle {
    glm::vec3 Position, Velocity;
    glm::vec4 Color;
    float     Life;

    Particle() : Position(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f) { }
};

class Particles {
public:
    // constructor
    Particles( unsigned int amount,bool scatter);
    // update all particles
    void Update(float dt, glm::vec3 objectVelocity, glm::vec3 objectPosition, unsigned int newParticles, glm::vec3 offset = glm::vec3(0.0f));
    // render all particles
    void Draw(Shader shader,const glm::mat4& viewProjMtx);
    Light* light;
private:
    // state
    std::vector<Particle> particles;
    unsigned int amount;

    unsigned int VAO;
    bool scatter;
    GLuint EBO;
    
    // initializes buffer and vertex attributes
    void init();
    // returns the first Particle index that's currently unused e.g. Life <= 0.0f or 0 if no particle is currently inactive
    unsigned int firstUnusedParticle(bool &noDied);
    // respawns particle
    void respawnParticle(Particle &particle, glm::vec3 objectVelocity, glm::vec3 objectPosition,  glm::vec3 offset = glm::vec3(0.0f));
};