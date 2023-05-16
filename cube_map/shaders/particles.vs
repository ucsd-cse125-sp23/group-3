#version 330 core
layout (location = 0) in vec3 vertex; // <vec3 position>

out vec4 ParticleColor;

uniform mat4 projection;
uniform vec3 offset;
uniform vec4 color;
uniform float scale=0.05f;

void main()
{
    ParticleColor = color;
    gl_Position = projection * vec4((vertex * scale) + offset, 1.0);
}