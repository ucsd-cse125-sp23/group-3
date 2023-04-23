#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 fragNormal;

uniform vec3 AmbientColor = vec3(0.2);
uniform vec3 LightDirection = normalize(vec3(1, 5, 2));
uniform vec3 LightColor = vec3(0.5);
uniform sampler2D texture_diffuse1;

void main()
{    
    // Compute irradiance (sum of ambient & direct lighting)
    vec3 irradiance = AmbientColor + LightColor * max(0, dot(LightDirection, fragNormal));
    
    vec3 DiffuseColor = vec3(texture(texture_diffuse1, TexCoords));
    vec3 reflectance = irradiance * DiffuseColor;
    FragColor = vec4(sqrt(reflectance), 1);
    //FragColor=texture(texture_diffuse1, TexCoords);
}