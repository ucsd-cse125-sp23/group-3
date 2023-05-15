#include "Particles.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>

Particles::Particles(unsigned int amount,bool scatter)
    : amount(amount), scatter(scatter)
{
    this->init();
}

void Particles::Update(float dt, glm::vec3 objectVelocity, glm::vec3 objectPosition, unsigned int newParticles, glm::vec3 offset)
{
    // add new particles 
    for (unsigned int i = 0; i < newParticles; ++i)
    {
        bool noDied=false;
        int unusedParticle = this->firstUnusedParticle(noDied);
        if(noDied==false){
            this->respawnParticle(this->particles[unusedParticle], objectVelocity, objectPosition, offset);
        }
        
    }
    // update all particles
    for (unsigned int i = 0; i < this->amount; ++i)
    {
        Particle &p = this->particles[i];
         // reduce life
        if (p.Life > 0.0f)
        {	// particle is alive, thus update
            p.Position -= p.Velocity * dt; 
            p.Color.a -= dt*0.5f ;
        }
        p.Life = p.Color.a;
    }
}

// render all particles
void Particles::Draw(Shader shader,const glm::mat4& viewProjMtx)
{
    // use additive blending to give it a 'glow' effect
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    shader.use();
    shader.setMat4("projection",viewProjMtx);
    //std::cout<<"round "<<std::endl;
    for (Particle particle : this->particles)
    {
        if (particle.Life > 0.0f)
        {
            //std::cout<<"error here"<<std::endl;
            shader.setVec3("offset", particle.Position);
            shader.setVec4("color", particle.Color);
    
            //std::cout<<"particle.Position "<<glm::to_string(particle.Position)<<std::endl;
            //std::cout<<"particle.color "<<glm::to_string(particle.Color)<<std::endl;

            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            
        }
    }
    //std::cout<<"error here"<<std::endl;
    // don't forget to reset to default blending mode
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Particles::init()
{
    // set up mesh and attribute properties
    unsigned int VBO;
    float particle_quad[] = {
        -0.5f,  0.5f,-0.5f,//0
        0.5f, 0.5f,-0.5f, //1
        0.5f,  0.5f,0.5f,//2
        -0.5f,   0.5f,0.5f,//3
        -0.5f,  -0.5f,-0.5f,//4
        0.5f, -0.5f,-0.5f,//5
        0.5f,  -0.5f,0.5f,//6
        -0.5f,   -0.5f,0.5f,//7
    }; 
    unsigned int indices[] = {
		0, 1, 2, 2, 3, 0, //top
        7, 6, 2, 7, 2, 3, //front
        5, 4, 0, 5, 0, 1, //back
        4, 5, 6, 6, 7, 4, //bottom
        4, 7, 3, 4, 3, 0, //left
        6, 5, 1, 6, 1, 2, 
	};

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    //glGenBuffers(1, &EBO);
    // fill mesh buffer
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);
    
    

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
    glBindVertexArray(0);
    // create this->amount default particle instances
    for (unsigned int i = 0; i < this->amount; ++i)
        this->particles.push_back(Particle());
}

// stores the index of the last particle used (for quick access to next dead particle)
unsigned int lastUsedParticle = 0;
unsigned int Particles::firstUnusedParticle(bool &noDied)
{
    // first search from last used particle, this will usually return almost instantly
    for (unsigned int i = lastUsedParticle; i < this->amount; ++i){
        if (this->particles[i].Life <= 0.0f){
            lastUsedParticle = i;
            return i;
        }
    }
    // otherwise, do a linear search
    for (unsigned int i = 0; i < lastUsedParticle; ++i){
        if (this->particles[i].Life <= 0.0f){
            lastUsedParticle = i;
            return i;
        }
    }
    // all particles are taken, override the first one (note that if it repeatedly hits this case, more particles should be reserved)
    lastUsedParticle = 0;
    noDied=true;
    return 0;
}

void Particles::respawnParticle(Particle &particle, glm::vec3 objectVelocity, glm::vec3 objectPosition, glm::vec3 offset)
{
    float random1 = ((rand() % 1000) - 5) / 2000.0f;
    float random2 = ((rand() % 1000) - 5) / 2000.0f;
    float random3 = ((rand() % 1000) - 5) / 2000.0f;
    float factor=((rand() % 1000) - 5) / 2000.0f;
    glm::vec3 random=glm::vec3(random1,random2,random3)*factor*factor;
    //float random=0.0f;
    float rColor = 0.5f + ((rand() % 100) / 100.0f);
    particle.Position = objectPosition  + offset;
    if(scatter){
        particle.Position+=random;
    }
    particle.Color = glm::vec4(rColor, rColor, rColor, 1.0f);
    //particle.Life = 1.0f;
    //particle.Velocity = objectVelocity* 0.1f;
    particle.Velocity = glm::vec3(0.0f);
    
}