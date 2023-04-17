#include <string>
#include <iostream>
#include "Map.h"
#include <glm/gtx/string_cast.hpp>


Map::Map() {
    
    wallheight=2.0f;
    groundheight=0.0f;
    wallwidth=0.2f;
    groundsize=5.0f;

    std::vector<glm::vec3> wallsmin1=std::vector<glm::vec3>();
    std::vector<glm::vec3> wallsmax1=std::vector<glm::vec3>();
    const char* file1="./scene/map_animal.txt";
    readWallsCoord(file1,wallsmin1,wallsmax1,glm::vec3(-5.1f,0.0f,0.1f));

    glm::vec3 groundmin1=glm::vec3(0.0f,0.0f,0.0f);
    glm::vec3 groundmax1=glm::vec3(-groundsize-wallwidth,-0.2f,groundsize+wallwidth);
    map1=new Submap(wallsmin1,wallsmax1,groundmin1,groundmax1);
    glm::mat4 trans1 = {
        {1,0,0,0},
        {0,1,0,0},
        {0.5,0,0.5*glm::sqrt(3.0f),0},
        {0,0,0,1}};
    map1->setModel(trans1);

    std::vector<glm::vec3> wallsmin2=std::vector<glm::vec3>();
    std::vector<glm::vec3> wallsmax2=std::vector<glm::vec3>();
    const char* file2="./scene/map_clown.txt";
    readWallsCoord(file2,wallsmin2,wallsmax2,glm::vec3(-5.1f,0.0f,-5.1f));

    glm::vec3 groundmin2=glm::vec3(0.0f,0.0f,0.0f);
    glm::vec3 groundmax2=glm::vec3(-(groundsize+wallwidth),-0.2f,-(groundsize+wallwidth));
    map2=new Submap(wallsmin2,wallsmax2,groundmin2,groundmax2);
    glm::mat4 trans2 = {
        {1,0,0,0},
        {0,1,0,0},
        {-0.5,0,0.5*glm::sqrt(3.0f),0},
        {0,0,0,1}};
    map2->setModel(trans2);

    std::vector<glm::vec3> wallsmin3=std::vector<glm::vec3>();
    std::vector<glm::vec3> wallsmax3=std::vector<glm::vec3>();
    const char* file3="./scene/map_sculpture.txt";
    readWallsCoord(file3,wallsmin3,wallsmax3,glm::vec3(0.1f,0.0f,-5.1f));

    glm::vec3 groundmin3=glm::vec3(0.0f,0.0f,0.0f);
    glm::vec3 groundmax3=glm::vec3((groundsize+wallwidth),-0.2f,-(groundsize+wallwidth));
    map3=new Submap(wallsmin3,wallsmax3,groundmin3,groundmax3);
    glm::mat4 trans3 = {
        {0.5,0,0.5*glm::sqrt(3.0f),0},
        {0,1,0,0},
        {-0.5,0,0.5*glm::sqrt(3.0f),0},
        {0,0,0,1}};
    map3->setModel(trans3);
}

Map::~Map() {
    delete map1;
    delete map2;
    delete map3;
}

void Map::readWallsCoord(const char* file,std::vector<glm::vec3> &wallsmin, std::vector<glm::vec3> &wallsmax,glm::vec3 translation){
    Tokenizer token=Tokenizer();
    char temp[256];
    token.Open(file);
    float walllength=groundsize/5.0f;
    float offsetforwidth=wallwidth/2.0f;
    //std::cout<<"offset "<<offsetforwidth<<std::endl;
    for(int j=0;j<6;j++){
        for(int i=0;i<6;i++){
            int tempint=token.GetInt();
            
            //std::cout<<"int "<<tempint<<std::endl;
            glm::vec3 topwallmin=glm::vec3(i*walllength-offsetforwidth,0.0f,j*walllength-offsetforwidth)+translation;
            glm::vec3 topwallmax=glm::vec3((i+1)*walllength+offsetforwidth,wallheight,j*walllength+offsetforwidth)+translation;
            glm::vec3 leftwallmin=glm::vec3(i*walllength-offsetforwidth,0.0f,j*walllength-offsetforwidth)+translation;
            glm::vec3 leftwallmax=glm::vec3((i)*walllength+offsetforwidth,wallheight,(j+1)*walllength+offsetforwidth)+translation;
            //std::cout<<"topwallmin "<<glm::to_string(topwallmin)<<std::endl;
            //std::cout<<"topwallmax "<<glm::to_string(topwallmax)<<std::endl;
            //std::cout<<"leftwallmin "<<glm::to_string(leftwallmin)<<std::endl;
            //std::cout<<"leftwallmax "<<glm::to_string(leftwallmax)<<std::endl;
            if(tempint==0){
                continue;
            }else if(tempint==1){
                wallsmin.push_back(topwallmin);
                wallsmax.push_back(topwallmax);
            }else if(tempint==2){
                wallsmin.push_back(leftwallmin);
                wallsmax.push_back(leftwallmax);
            }else if(tempint==3){
                wallsmin.push_back(topwallmin);
                wallsmax.push_back(topwallmax);
                wallsmin.push_back(leftwallmin);
                wallsmax.push_back(leftwallmax);
            }
        }
    }
    //std::cout<<"get here"<<std::endl;
    token.Close();
}

void Map::update(){
    map1->update();
    map2->update();
    map3->update();
}

void Map::draw(const glm::mat4& viewProjMtx, GLuint shader){
    map1->draw(viewProjMtx,shader);
    map2->draw(viewProjMtx,shader);
    map3->draw(viewProjMtx,shader);
}

