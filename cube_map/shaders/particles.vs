#version 330 core
layout (location = 0) in vec3 vertex; // <vec3 position>
layout (location = 1) in vec2 text; 

out vec4 ParticleColor;
out vec2 TexCoords;

uniform mat4 projection;
uniform mat4 view;
uniform vec3 offset;
uniform vec4 color;
uniform float scale=0.05f;

void main()
{
    ParticleColor = color;
    TexCoords = text;
    gl_Position = projection *((view*vec4((vertex * scale) , 1.0))+ vec4(offset,0.0f));
}