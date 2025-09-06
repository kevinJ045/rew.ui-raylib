#version 330 core

in vec3 fragNormal;
in vec2 fragTexCoord;
in vec4 fragPosLight;   

uniform sampler2D texture0;       
uniform sampler2D shadowMap;      
uniform vec3 lightDir;            

out vec4 finalColor;


float ShadowCalculation(vec4 fragPosLight)
{
    
    vec3 projCoords = fragPosLight.xyz;
    projCoords = projCoords * 0.5 + 0.5; 

    float currentDepth = projCoords.z;

    
    float shadow = 0.0;
    float bias = 0.01; 
    float texelSize = 1.0 / 1024.0; 

    for(int x=-1; x<=1; ++x)
    {
        for(int y=-1; y<=1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x,y)*texelSize).r;
            shadow += currentDepth - bias > pcfDepth ? 0.5 : 1.0;
        }
    }
    shadow /= 9.0;

    return shadow;
}

void main()
{
    vec3 baseColor = texture(texture0, fragTexCoord).rgb;

    
    float shadow = ShadowCalculation(fragPosLight);

    
    vec3 N = normalize(fragNormal);
    vec3 L = normalize(-lightDir);  
    float diff = max(dot(N, L), 0.0);
    vec3 diffuse = diff * vec3(1.0);

    
    vec3 ambient = vec3(0.1);

    vec3 lighting = (ambient + diffuse) * shadow;

    finalColor = vec4(baseColor * lighting, 1.0);
}
