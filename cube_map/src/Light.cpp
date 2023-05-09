#include "Light.h"

Light::Light(bool _spotLight,bool _pointLight,glm::vec3 _color, glm::vec3 _direction, glm::vec3 _position, float _ambient, float _diffuse, float _specular){
	spotLight=_spotLight;
	pointLight=_pointLight;
	lightcolor=_color;
	direction=_direction;
	position=_position;
	ambient=_ambient;
	diffuse=_diffuse;
	specular=_specular;
	
}

Light::~Light(){

}

void Light::SetParam(float _constant, float _linear, float _quadratic){
	constant=_constant;
	linear=_linear;
	quadratic=_quadratic;
}

void Light::SetSpot(float _cutoff,float _outerCutOff){
	cutoff=_cutoff;
	outerCutOff=_outerCutOff;
}

