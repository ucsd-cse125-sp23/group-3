
#include "Skeleton.h"
#include <string>
#include "Joint.h"
#include "Cube.h"
#include "Tokenizer.h"
#include "DOF.h"

Skeleton::Skeleton() {
    this->root=NULL;
}

Skeleton::~Skeleton(){
    delete root;
}

bool Skeleton::Load(const char *file) {
    Tokenizer token=Tokenizer();
    token.Open(file);
    token.FindToken("balljoint");
    // Parse tree
    char temp[256];
    token.GetToken(temp);
    root=new Joint(temp, NULL);
    root->load(token);
    // Finish
    token.Close();
    
    return true;
}

void Skeleton::Update() {
    root->update(glm::mat4(1.0f));
}

Joint* Skeleton::find(int num){
    
}

void Skeleton::Draw(const glm::mat4& viewProjMtx, GLuint shader) {
    root->draw(viewProjMtx, shader);
}