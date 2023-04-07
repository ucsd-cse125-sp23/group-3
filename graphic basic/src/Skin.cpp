#include "Skin.h"
#include <iostream>

Skin::Skin(Skeleton* parent) {
    // Model matrix.
    model = glm::mat4(1.0f);
    skl=parent;
    // Specify vertex positions
    color = glm::vec3(1.0f, 0.95f, 0.1f);
    vertices= std::vector<Vertex* >();
    
    // Specify indices
    indices = std::vector<unsigned int>();
    positions=std::vector<glm::vec3>();
    normals=std::vector<glm::vec3>();

}

Skin::~Skin() {
    for (std:: vector<Vertex* >::iterator it = vertices.begin(); it != vertices.end(); it++){
        delete (*it);
    }
    // Delete the VBOs and the VAO.
    glDeleteBuffers(1, &VBO_positions);
    glDeleteBuffers(1, &VBO_normals);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
}

void Skin::Load(const char* file){
    Tokenizer token=Tokenizer();
    token.Open(file);

    jntlist=Joint::getList();
    while(1) {
        char temp[256];
        token.GetToken(temp);
        if(strcmp(temp,"positions")==0) {
            int count=token.GetInt();
            token.GetToken(temp);
            glm::vec3 newpos;
            for(int i =0;i<count;i++){
                newpos.x=token.GetFloat();
                newpos.y=token.GetFloat();
                newpos.z=token.GetFloat();
                Vertex* vex=new Vertex(newpos);
                vertices.push_back(vex);
            }
        }
        else if(strcmp(temp,"normals")==0){
            int count=token.GetInt();
            token.GetToken(temp);
            glm::vec3 newpos;
            for(int i =0;i<count;i++){
                newpos.x=token.GetFloat();
                newpos.y=token.GetFloat();
                newpos.z=token.GetFloat();
                vertices.at(i)->setnormal(newpos);
            }
        }
        else if(strcmp(temp,"skinweights")==0){
            int count=token.GetInt();
            token.GetToken(temp);
            glm::vec3 newpos;
            for(int i =0;i<count;i++){
                int cntj=token.GetInt();
                for(int j=0;j<cntj;j++){
                    int JNT=token.GetInt();
                    float weight=token.GetFloat();
                    vertices.at(i)->addJoint(jntlist.at(JNT),weight);
                }
            }
        }
        else if(strcmp(temp,"triangles")==0){
            int count=token.GetInt();
            token.GetToken(temp);
            glm::vec3 newpos;
            for(int i =0;i<count;i++){
                for(int j=0;j<3;j++){
                    indices.push_back(token.GetInt());
                }   
            }
        }
        else if(strcmp(temp,"bindings")==0){
            int count=token.GetInt();
            token.GetToken(temp);
            for(int i =0;i<count;i++){
                token.GetToken(temp);
                token.GetToken(temp);
                float aaa[12];
                for(int j=0;j<12;j++){
                    aaa[j]=token.GetFloat();
                }   
                glm::mat4 bbb = glm::mat4(
                    aaa[0], aaa[1],aaa[2],0, 
                    aaa[3], aaa[4],aaa[5], 0,  
                    aaa[6], aaa[7],aaa[8],  0, 
                    aaa[9],aaa[10],aaa[11], 1.0f);
                jntlist.at(i)->setbind(bbb);
                token.GetToken(temp);
            }
            break ;
        }
        else token.SkipLine(); 
    }
    token.Close();

    for(std:: vector<Vertex*>::iterator it = vertices.begin(); it != vertices.end(); it++){
        positions.push_back((*it)->getposition());
        //std::cout<<((*it)->getposition()).x<<std::endl;
        normals.push_back((*it)->getnormal());
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO_positions);
    glGenBuffers(1, &VBO_normals);
    // Bind to the VAO.
    glBindVertexArray(VAO);

    // Bind to the first VBO - We will use it to store the vertices
    glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * positions.size(), positions.data(), GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

    // Bind to the second VBO - We will use it to store the normals
    glBindBuffer(GL_ARRAY_BUFFER, VBO_normals);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(), normals.data(), GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

    // Generate EBO, bind the EBO to the bound VAO and send the data
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

    // Unbind the VBOs.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Skin::updateVertex() {
    // Generate a vertex array (VAO) and two vertex buffer objects (VBO).
    int i=0;
    positions=std::vector<glm::vec3>();
    normals=std::vector<glm::vec3>();
    for(std:: vector<Vertex*>::iterator it = vertices.begin(); it != vertices.end(); it++){
        positions.push_back((*it)->getposition());
        //std::cout<<((*it)->getposition()).x<<std::endl;
        normals.push_back((*it)->getnormal());
    }
    glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);
    glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(glm::vec3) * positions.size(), positions.data());
    glBindBuffer(GL_ARRAY_BUFFER, VBO_normals);
    glBufferSubData(GL_ARRAY_BUFFER,0, sizeof(glm::vec3) * normals.size(), normals.data());
    

}

void Skin::draw(const glm::mat4& viewProjMtx, GLuint shader) {
    // actiavte the shader program
    glUseProgram(shader);

    // get the locations and send the uniforms to the shader
    glUniformMatrix4fv(glGetUniformLocation(shader, "viewProj"), 1, false, (float*)&viewProjMtx);
    glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, (float*)&model);
    glUniform3fv(glGetUniformLocation(shader, "DiffuseColor"), 1, &color[0]);

    // Bind the VAO
    glBindVertexArray(VAO);

    // draw the points using triangles, indexed with the EBO
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    // Unbind the VAO and shader program
    glBindVertexArray(0);
    glUseProgram(0);
}
