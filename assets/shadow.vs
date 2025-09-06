#version 330 core


layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexTexCoord;


uniform mat4 model;           
uniform mat4 view;            
uniform mat4 projection;      
uniform mat4 lightViewProj;   


out vec3 fragNormal;
out vec2 fragTexCoord;
out vec4 fragPosLight;

void main()
{
    
    vec4 worldPos = model * vec4(vertexPosition, 1.0);

    
    fragNormal = mat3(transpose(inverse(model))) * vertexNormal;

    
    fragTexCoord = vertexTexCoord;

    
    fragPosLight = lightViewProj * worldPos;

    
    gl_Position = projection * view * worldPos;
}
