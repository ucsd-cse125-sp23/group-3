#version 330 core
layout (location = 0) in vec3 vertex; // <vec3 position>

out vec4 ParticleColor;

uniform mat4 projection;
uniform vec3 offset;
uniform vec4 color;

void main()
{
    float scale = 0.05f;
    ParticleColor = color;
    gl_Position = projection * vec4((vertex * scale) + offset, 1.0);
}