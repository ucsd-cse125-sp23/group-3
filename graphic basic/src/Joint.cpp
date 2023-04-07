#include <string>
#include <iostream>
#include "Joint.h"
#include "Cube.h"
#include "Tokenizer.h"
#include "DOF.h"


std::vector<Joint*> Joint::Jointlist= std::vector<Joint*>();

Joint::Joint(std::string name, Joint *parent) {
    this->jnt = new Cube(glm::vec3(-0.1,-0.1,-0.1), glm::vec3(0.1,0.1,0.1));
    this->name= name;
    this->local=glm::mat4(1.0f);
    this->world=glm::mat4(1.0f);
    this->bind=glm::mat4(1.0f);
    this->offset=glm:: vec3(0,0,0);
    this->dofs=new DOF();
    this->children=std:: vector<Joint*>();
    this->parent=parent;
    Joint::Jointlist.push_back(this);
}

Joint::~Joint() {
    delete jnt;
    delete dofs;
}

std::vector<Joint*> Joint::getList(){
    return Jointlist;
}



void Joint::setbind(glm::mat4 mat){
    bind=mat;
}

glm::mat4 Joint::getBind(){
    //std::cout<<"update skin"<<std::endl;
    //std::cout<<glm::to_string(world)<<std::endl;
    return world*glm::inverse(bind);
}

void Joint::SetBox(glm::vec3 boxmin, glm::vec3 boxmax){
    delete jnt;
    this->jnt= new Cube(boxmin, boxmax);
}

std::string Joint::getname(){
    return this->name;
}

DOF* Joint::getDOF(){
    return dofs;
}

void Joint::setOffset(float data,int x){
    if(x==0){
        this->offset.x=data;
    }else if(x==1){
        this->offset.y=data;
    }else if(x==2){
        this->offset.z=data;
    }
}

bool Joint::load(Tokenizer &token) {
    token.FindToken("{");
    glm::vec3 jntmin;
    glm::vec3 jntmax;
    
    while(1) {
        char temp[256];
        token.GetToken(temp);
        if(strcmp(temp,"offset")==0) {
            offset.x=token.GetFloat();
            offset.y=token.GetFloat();
            offset.z=token.GetFloat();
        }
        else if (strcmp(temp,"boxmin")==0){
            jntmin.x=token.GetFloat();
            jntmin.y=token.GetFloat();
            jntmin.z=token.GetFloat();
        }
        else if (strcmp(temp,"boxmax")==0){
            jntmax.x=token.GetFloat();
            jntmax.y=token.GetFloat();
            jntmax.z=token.GetFloat();
            SetBox(jntmin,jntmax);
        }
        else if (strcmp(temp,"rotxlimit")==0){
            float x=token.GetFloat();
            float y=token.GetFloat();
            dofs->SetXMinMax(x, y);
        }
        else if (strcmp(temp,"rotylimit")==0){
            float x=token.GetFloat();
            float y=token.GetFloat();
            dofs->SetYMinMax(x, y);
        }
        else if (strcmp(temp,"rotzlimit")==0){
            float x=token.GetFloat();
            float y=token.GetFloat();
            dofs->SetZMinMax(x, y);
        }
        else if (strcmp(temp,"pose")==0){
            glm::vec3 dof;
            dof.x=token.GetFloat();
            dof.y=token.GetFloat();
            dof.z=token.GetFloat();
            dofs->SetValue(dof);
        }
        else if(strcmp(temp,"balljoint")==0) {
            token.GetToken(temp);
            Joint* childjnt=new Joint(temp,this);
            childjnt->load(token);
            children.push_back(childjnt);
        }
        else if(strcmp(temp,"}")==0) break;
        else token.SkipLine(); // Unrecognized token
    }

}

void Joint::setModel(glm::vec3 deg, glm::vec3 offset) {
    //std::cout <<glm::to_string(deg) << std::endl;
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, offset);
    model = model * glm::rotate(deg.z, glm::vec3(0.0f, 0.0f, 1.0f));
    model = model * glm::rotate(deg.y, glm::vec3(0.0f, 1.0f, 0.0f));
    model = model * glm::rotate(deg.x, glm::vec3(1.0f, 0.0f, 0.0f));
    local =model;
    //std::cout<<glm::to_string(local)<<std::endl;
}

void Joint::update(glm::mat4 parent) {
    // Compute local matrix L
    setModel(dofs->GetValue(),offset);
    // Compute world matrix W
    world=parent * local;
    //std::cout<<"update skeleton"<<std::endl;
    //std::cout<<glm::to_string(world)<<std::endl;
    jnt->update(world);
    // Recursively call Update() on children
    for (std:: vector<Joint*>::iterator it = children.begin(); it != children.end(); it++){
        (*it)->update(world);
    }
}

void Joint::draw(const glm::mat4& viewProjMtx, GLuint shader) {
    // Draw oriented box with OpenGL
    jnt->draw(viewProjMtx, shader);
    // Recursively call Draw() on children
    for (std:: vector<Joint*>::iterator it = children.begin(); it != children.end(); it++){
        (*it)->draw(viewProjMtx, shader);
    }
}

