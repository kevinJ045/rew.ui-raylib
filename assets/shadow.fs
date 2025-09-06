#version 330

in vec3 fragNormal;
in vec2 fragTexCoord;
in vec4 fragPosLight;

uniform sampler2D texture0;       // Diffuse texture
uniform sampler2D shadowMap;      // The shadow render target
uniform vec3 lightDir;

out vec4 finalColor;

float ShadowCalculation(vec4 fragPosLight) {
    // Perspective divide
    vec3 projCoords = fragPosLight.xyz / fragPosLight.w;
    projCoords = projCoords * 0.5 + 0.5; // to [0,1]

    // Sample closest depth from shadow map
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;

    // Simple shadow test with bias
    float bias = 0.005;
    float shadow = currentDepth - bias > closestDepth ? 0.5 : 1.0;
    return shadow;
}

void main() {
    vec3 baseColor = texture(texture0, fragTexCoord).rgb;
    float shadow = ShadowCalculation(fragPosLight);

    vec3 light = max(dot(normalize(fragNormal), -lightDir), 0.0) * vec3(1.0);
    vec3 lighting = (0.3 + light) * shadow;

    finalColor = vec4(baseColor * lighting, 1.0);
}
