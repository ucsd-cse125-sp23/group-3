#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 norm;
layout(location = 2) in vec2 tex;
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 bitangent;
layout(location = 5) in ivec4 boneIds; 
layout(location = 6) in vec4 weights;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;
uniform mat4 finalBonesMatrices[MAX_BONES];

// Outputs the current position for the Fragment Shader
out vec3 FragPos;
// Outputs the normal for the Fragment Shader
out vec3 Normal;
// Outputs the texture coordinates to the Fragment Shader
out vec2 TexCoords;

void main()
{
    vec4 totalPosition = vec4(0.0f);
    vec4 totalNormal = vec4(0.0f);
    for(int i = 0 ; i < MAX_BONE_INFLUENCE ; i++)
    {
        if(boneIds[i] == -1) 
            continue;
        if(boneIds[i] >=MAX_BONES) 
        {
            totalPosition = vec4(pos,1.0f);
            break;
        }
        vec4 localPosition = finalBonesMatrices[boneIds[i]] * vec4(pos,1.0f);
        totalPosition += localPosition * weights[i];
        vec4 localNormal = finalBonesMatrices[boneIds[i]] * vec4(norm,0.0f);
        totalNormal += localNormal*weights[i];
   }

    mat4 viewModel = view * model;
    gl_Position =  projection * viewModel * totalPosition;
    FragPos=vec3( model*totalPosition);
    Normal=vec3(model*normalize(totalNormal));
    //Normal=vec3(model*normalize(vec4(norm,0.0f)));
	TexCoords = tex;
}
