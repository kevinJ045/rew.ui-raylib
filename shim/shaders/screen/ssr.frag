#version 330 core

/* === Varyings === */

noperspective in vec2 vTexCoord;

/* === Uniforms === */

uniform sampler2D uTexColor;
uniform sampler2D uTexAlbedo;
uniform sampler2D uTexNormal;
uniform sampler2D uTexORM;
uniform sampler2D uTexDepth;

uniform int uMaxRaySteps;
uniform int uBinarySearchSteps;
uniform float uRayMarchLength;
uniform float uDepthThickness;
uniform float uDepthTolerance;
uniform float uEdgeFadeStart;
uniform float uEdgeFadeEnd;

uniform mat4 uMatView;
uniform mat4 uMatInvProj;
uniform mat4 uMatInvView;
uniform mat4 uMatViewProj;
uniform vec3 uViewPosition;

/* === Constants === */

const float PI = 3.14159265359;

/* === Output === */

out vec4 FragColor;

/* === Helper Functions === */

vec2 OctahedronWrap(vec2 val)
{
    return (1.0 - abs(val.yx)) * mix(vec2(-1.0), vec2(1.0), 
        vec2(greaterThanEqual(val.xy, vec2(0.0))));
}

vec3 DecodeOctahedral(vec2 encoded)
{
    encoded = encoded * 2.0 - 1.0;
    vec3 normal;
    normal.z = 1.0 - abs(encoded.x) - abs(encoded.y);
    normal.xy = normal.z >= 0.0 ? encoded.xy : OctahedronWrap(encoded.xy);
    return normalize(normal);
}

vec3 ReconstructViewPosition(vec2 texCoord, float depth)
{
    vec4 ndcPos = vec4(texCoord * 2.0 - 1.0, depth * 2.0 - 1.0, 1.0);
    vec4 viewPos = uMatInvProj * ndcPos;
    return viewPos.xyz / viewPos.w;
}

vec3 ReconstructWorldPosition(vec2 texCoord, float depth)
{
    vec3 viewPos = ReconstructViewPosition(texCoord, depth);
    return (uMatInvView * vec4(viewPos, 1.0)).xyz;
}

vec2 WorldToScreenSpace(vec3 worldPos)
{
    vec4 projPos = uMatViewProj * vec4(worldPos, 1.0);
    projPos /= projPos.w;
    return projPos.xy * 0.5 + 0.5;
}

bool IsOutOfScreen(vec2 uv)
{
    return any(greaterThan(uv, vec2(1.0))) || any(lessThan(uv, vec2(0.0)));
}

float ScreenEdgeFade(vec2 uv)
{
    vec2 fade = max(vec2(0.0), abs(uv - 0.5) * 2.0 - vec2(uEdgeFadeStart));
    fade = fade / (uEdgeFadeEnd - uEdgeFadeStart);

    return 1.0 - clamp(max(fade.x, fade.y), 0.0, 1.0);
}

/* === PBR Functions === */

vec3 ComputeF0(float metallic, float specular, vec3 albedo)
{
    float dielectric = 0.16 * specular * specular;
    // use (albedo * metallic) as colored specular reflectance at 0 angle for metallic materials
    // SEE: https://google.github.io/filament/Filament.md.html
    return mix(vec3(dielectric), albedo, vec3(metallic));
}

vec3 SchlickFresnel(float cNdotV, vec3 F0)
{
    float m = 1.0 - cNdotV, m2 = m * m;
    float fresnel = m2 * m2 * m;

    return F0 + (1.0 - F0) * fresnel;
}

/* === Raymarching === */

vec3 BinarySearch(vec3 startPos, vec3 endPos)
{
    for (int i = 0; i < uBinarySearchSteps; i++)
    {
        vec3 midPos = (startPos + endPos) * 0.5;

        vec2 uv = WorldToScreenSpace(midPos);
        float sampledDepth = texture(uTexDepth, uv).r;

        vec3 sampledViewPos = ReconstructViewPosition(uv, sampledDepth);
        vec3 midViewPos = (uMatView * vec4(midPos, 1.0)).xyz;

        float depthDiff = sampledViewPos.z - midViewPos.z;

        if (depthDiff > -uDepthTolerance) {
            endPos = midPos;    // surface in front of us
        }
        else {
            startPos = midPos;  // surface behind
        }
    }

    return endPos; // refined final position
}

vec3 TraceReflectionRay(vec3 startPos, vec3 reflectionDir)
{
    float minStep = uRayMarchLength / float(uMaxRaySteps);
    float stepSize = minStep;

    vec3 currentPos = startPos;

    for (int i = 0; i < uMaxRaySteps; i++)
    {
        currentPos += reflectionDir * stepSize;

        vec2 uv = WorldToScreenSpace(currentPos);
        if (IsOutOfScreen(uv)) break;

        float sampledDepth = texture(uTexDepth, uv).r;

        vec3 sampledViewPos  = ReconstructViewPosition(uv, sampledDepth);
        vec3 currentViewPos = (uMatView * vec4(currentPos, 1.0)).xyz;

        float depthDiff = sampledViewPos.z - currentViewPos.z;

        if (depthDiff > -uDepthTolerance && depthDiff < uDepthThickness)
        {
            currentPos = BinarySearch(startPos, currentPos);
            uv = WorldToScreenSpace(currentPos);

            vec3 color = texture(uTexColor, uv).rgb;
            float fade = ScreenEdgeFade(uv);
            return color * fade;
        }

        stepSize = max(depthDiff * 0.9, minStep);
    }

    return vec3(0.0);
}

/* === Main Program === */

void main()
{
    /* --- Texture sampling and scene property extraction --- */

    vec3 sceneColor = texture(uTexColor, vTexCoord).rgb;
    float depth = texture(uTexDepth, vTexCoord).r;

    if (depth > 0.999) {
        FragColor = vec4(sceneColor, 1.0);
        return;
    }

    vec2 encodedNormal = texture(uTexNormal, vTexCoord).rg;
    vec3 albedo = texture(uTexAlbedo, vTexCoord).rgb;
    vec3 orm = texture(uTexORM, vTexCoord).rgb;

    float occlusion = orm.r;
    float roughness = orm.g;
    float metallic = orm.b;

    vec3 worldNormal = DecodeOctahedral(encodedNormal);
    vec3 worldPos = ReconstructWorldPosition(vTexCoord, depth);

    /* --- Calculating view and reflection directions --- */

    vec3 viewDir = normalize(worldPos - uViewPosition);
    vec3 reflectionDir = reflect(viewDir, worldNormal);

    if (dot(reflectionDir, worldNormal) < 0.0) {
        FragColor = vec4(sceneColor, 1.0);
        return;
    }

    /* --- Reflection sampling and hotspot filtering --- */

    vec3 reflectionColor = TraceReflectionRay(worldPos, reflectionDir);

    float reflectionLuminance = dot(reflectionColor, vec3(0.299, 0.587, 0.114));
    float sceneLuminance = dot(sceneColor, vec3(0.299, 0.587, 0.114));
    float maxReflectionLuminance = sceneLuminance * 4.0;

    if (reflectionLuminance > maxReflectionLuminance) {
        reflectionColor *= maxReflectionLuminance / reflectionLuminance;
    }

    /* --- Calculate specular reflection --- */

    float cNdotV = max(0.0, dot(worldNormal, -viewDir));
    vec3 F0 = ComputeF0(metallic, 0.5, albedo);

    vec3 F = SchlickFresnel(cNdotV, F0);
    vec3 specular = reflectionColor * F;

    // NOTE: Ideally, we should blur according to the roughness, but this
    //       would be expensive for some platforms, so we only attenuate

    float attenuation = 1.0 - roughness;
    attenuation *= attenuation;
    specular *= attenuation;

    /* --- Final mix --- */

    FragColor = vec4(sceneColor + specular, 1.0);
}
