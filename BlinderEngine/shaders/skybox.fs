#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

struct Fog {
    vec3 player_pos;
    float fog_distance;
};

uniform samplerCube skybox;
uniform Fog fog=Fog(vec3(0.0f,0.0f,0.0f),1000.0f);
uniform int windowWidth=800;
uniform int windowHeight=600;

vec4 CalcFog(vec4 inputColor);


void main()
{    
    FragColor = texture(skybox, TexCoords);
    FragColor = CalcFog(FragColor);
}

vec4 CalcFog(vec4 inputColor) {
	//hide items beyound certain threshold of playerposition
    float distanceX = abs(gl_FragCoord.x - windowWidth / 2);
    float distanceY = abs(gl_FragCoord.y - windowHeight / 2);
    float distance = sqrt(distanceX * distanceX + distanceY * distanceY);
    if(abs(distance) > fog.fog_distance) {
        inputColor = inputColor * 0.05;
    }
    return inputColor;

}