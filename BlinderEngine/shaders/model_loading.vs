#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

// Outputs the current position for the Fragment Shader
out vec3 FragPos;
// Outputs the normal for the Fragment Shader
out vec3 Normal;
// Outputs the texture coordinates to the Fragment Shader
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    TexCoords = aTexCoords;    
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    FragPos= vec3(model * vec4(aPos, 1.0));
    Normal = vec3(model * vec4(aNormal, 0));
}