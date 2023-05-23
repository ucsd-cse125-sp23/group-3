#include "Particles.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>


Particles::Particles(unsigned int amount,bool scatter,float range,float size,float lightintensity,glm::vec3 lightcolor)
    : amount(amount), scatter(scatter), range(range), size(size),lightintensity(lightintensity),lightcolor(lightcolor)
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
        //if(!noDied){
            this->respawnParticle(this->particles[unusedParticle], objectVelocity, objectPosition, glm::vec3(0.0f));
       // }
        
        
    }
    // update all particles
    glm::vec3 Lightpos=glm::vec3(0.0f);
    int intensity=0;
    for (unsigned int i = 0; i < this->amount; ++i)
    {
        Particle &p = this->particles[i];
         // reduce life
        if (p.Life > 0.0f)
        {	// particle is alive, thus update
            p.Position += p.Velocity * dt; 
            p.Color.a -= dt*0.5f ;
            p.Life = p.Color.a;
            Lightpos+=p.Position;
            //std::cout<<"particle pos "<<i<<" "<<glm::to_string(p.Position)<<std::endl;
            intensity++;
        }
        
    }
    //std::cout<<"alive particles "<<intensity<<std::endl;
    
    if(intensity!=0){
        Lightpos=Lightpos/((float)intensity);
        //std::cout<<"error here"<< glm::to_string(Lightpos)<<std::endl;
        //std::cout<<"Lightpos "<<glm::to_string(Lightpos)<<std::endl;
        //std::cout<<"objectpos "<<glm::to_string(objectPosition)<<std::endl;
        light=new Light(false,true,lightcolor,glm::vec3(1.0f),Lightpos,0.0f,lightintensity*0.7f*intensity/((float)1000.0f),0.0f);
        light->SetParam(1.0f,0.1f,0.03f);
    }else{
        light=new Light(false,true,glm::vec3(0.0f),glm::vec3(1.0f),glm::vec3(0.0f),0.0f,0.0f,0.0f);
        light->SetParam(1.0f,0.1f,0.03f);
    }
    
}

// render all particles
void Particles::Draw(Shader shader,const glm::mat4& viewProjMtx,glm::mat4 camView)
{
    // use additive blending to give it a 'glow' effect
    glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    shader.use();
    shader.setMat4("projection",viewProjMtx);
    //std::cout<<"round "<<std::endl;
    for (Particle particle : this->particles)
    {
        if (particle.Life > 0.0f)
        {
            //std::cout<<"error here"<<std::endl;
            glBindTexture(GL_TEXTURE_2D, texture);
            shader.setVec3("offset", particle.Position);
            shader.setVec4("color", particle.Color);
            //shader.setFloat("scale",(rand()%10)/50.0f+0.05);
            int size_int=(int)(size*10000);
            shader.setFloat("scale",(rand()%size_int)/((float)10000)+size);
            shader.setMat4("view",camView);
            //std::cout<<(rand()%10)/200.0f+0.05<<std::endl;
            //std::cout<<"particle.Position "<<glm::to_string(particle.Position)<<std::endl;
            //std::cout<<"particle.color "<<glm::to_string(particle.Color)<<std::endl;

            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            
        }
    }
    //std::cout<<"error here"<<std::endl;
    // don't forget to reset to default blending mode
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Particles::bindTexture(const char* filename){
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        // set the texture wrapping/filtering options (on the currently bound texture object)
        int width, height, nrComponents;
        Image* newimg=new Image();
        newimg->load(filename, width, height, nrComponents, 4);
        // load and generate the texture
        data=newimg->getData();
        if (data){
                GLenum format;
                if (nrComponents == 1)
                format = GL_RED;
                else if (nrComponents == 3)
                format = GL_RGB;
                else if (nrComponents == 4)
                format = GL_RGBA;

                glBindTexture(GL_TEXTURE_2D, texture);
                glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT); // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes texels from next repeat 
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }
        else{
                std::cout << "Failed to load texture" << std::endl;
        }
        delete newimg;
}

void Particles::init()
{
    // set up mesh and attribute properties
    unsigned int VBO;
    /*float particle_quad[] = {
        -0.5f,  0.5f,-0.5f,//0
        0.5f, 0.5f,-0.5f, //1
        0.5f,  0.5f,0.5f,//2
        -0.5f,   0.5f,0.5f,//3
        -0.5f,  -0.5f,-0.5f,//4
        0.5f, -0.5f,-0.5f,//5
        0.5f,  -0.5f,0.5f,//6
        -0.5f,   -0.5f,0.5f,//7
    }; */
    float particle_quad[] = {
        -0.5f,  -0.5f,0.0f,0.0f,1.0f,//0 
        0.5f, -0.5f,0.0f,1.0f,1.0f, //1
        0.5f,  0.5f,0.0f,1.0f,0.0f, //2
        -0.5f,   0.5f,0.0f,0.0f,0.0f,//3
    }; 
    /*unsigned int indices[] = {
		0, 1, 2, 2, 3, 0, //top
        7, 6, 2, 7, 2, 3, //front
        5, 4, 0, 5, 0, 1, //back
        4, 5, 6, 6, 7, 4, //bottom
        4, 7, 3, 4, 3, 0, //left
        6, 5, 1, 6, 1, 2, 
	};*/
    unsigned int indices[] = {
		0, 1, 2, 2, 3, 0, //top
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5* sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    glBindVertexArray(0);
    light=new Light(false,true,glm::vec3(0.0f),glm::vec3(1.0f),glm::vec3(0.0f),0.0f,0.0f,0.0f);
    light->SetParam(1.0f,0.1f,0.03f);
    // create this->amount default particle instances
    for (unsigned int i = 0; i < this->amount; ++i){
        this->particles.push_back(Particle());
        //std::cout<<"life band"<<particles[i].Life<<std::endl;
    }
        
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
    int lowest=0;
    float lowest_life=1.0f;
    for (unsigned int i = 0; i < lastUsedParticle; ++i){
        if (this->particles[i].Life <= 0.0f){
            lastUsedParticle = i;
            return i;
        }else if(this->particles[i].Life <= lowest_life){
            lowest=i;
            lowest_life=this->particles[i].Life;
        }
    }
    // all particles are taken, override the first one (note that if it repeatedly hits this case, more particles should be reserved)
    lastUsedParticle = 0;
    noDied=true;
    return lowest;
}

void Particles::respawnParticle(Particle &particle, glm::vec3 objectVelocity, glm::vec3 objectPosition, glm::vec3 offset)
{
    float random1 = ((rand() % 2000) - 1000) / (range*2000.0f);
    float random2 = ((rand() % 2000) - 1000) / (range*2000.0f);
    float random3 = ((rand() % 2000) - 1000) / (range*2000.0f);
    float factor1=(rand() % 2000) / 2000.0f;
    float factor2=(rand() % 2000) / 2000.0f;
    glm::vec3 random=glm::vec3(random1,random2,random3)*factor1*factor2;
    //float random=0.0f;
    float rColor = 0.5f;
    particle.Position = objectPosition;
    if(scatter){
        particle.Position+=random;
    }
    //std::cout<<offset.x<<std::endl;
    particle.Color = glm::vec4(rColor, rColor, rColor,1.0f);
    //particle.Life = 1.0f;
    particle.Velocity = objectVelocity* 0.0f;
    //particle.Velocity = glm::vec3(0.0f);
    particle.Life=1.0f;
}