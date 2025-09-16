/*
 * Copyright (c) 2025 Le Juez Victor
 *
 * This software is provided "as-is", without any express or implied warranty. In no event
 * will the authors be held liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose, including commercial
 * applications, and to alter it and redistribute it freely, subject to the following restrictions:
 *
 *   1. The origin of this software must not be misrepresented; you must not claim that you
 *   wrote the original software. If you use this software in a product, an acknowledgment
 *   in the product documentation would be appreciated but is not required.
 *
 *   2. Altered source versions must be plainly marked as such, and must not be misrepresented
 *   as being the original software.
 *
 *   3. This notice may not be removed or altered from any source distribution.
 */

#version 330 core

/* === Definitions === */

#define FOG_DISABLED 0
#define FOG_LINEAR 1
#define FOG_EXP2 2
#define FOG_EXP 3

/* === Varyings === */

noperspective in vec2 vTexCoord;

/* === Uniforms === */

uniform sampler2D uTexColor;
uniform sampler2D uTexDepth;

uniform float uNear;
uniform float uFar;

uniform lowp int uFogMode;
uniform vec3 uFogColor;
uniform float uFogStart;
uniform float uFogEnd;
uniform float uFogDensity;
uniform float uSkyAffect;

/* === Fragments === */

out vec4 FragColor;

// === Helper functions === //

float LinearizeDepth(float depth, float near, float far)
{
    return (2.0 * near * far) / (far + near - (2.0 * depth - 1.0) * (far - near));;
}

float FogFactorLinear(float dist, float start, float end)
{
    return 1.0 - clamp((end - dist) / (end - start), 0.0, 1.0);
}

float FogFactorExp2(float dist, float density)
{
    const float LOG2 = -1.442695;
    float d = density * dist;
    return 1.0 - clamp(exp2(d * d * LOG2), 0.0, 1.0);
}

float FogFactorExp(float dist, float density)
{
    return 1.0 - clamp(exp(-density * dist), 0.0, 1.0);
}

float FogFactor(float dist, int mode, float density, float start, float end)
{
    if (mode == FOG_LINEAR) return FogFactorLinear(dist, start, end);
    if (mode == FOG_EXP2) return FogFactorExp2(dist, density);
    if (mode == FOG_EXP) return FogFactorExp(dist, density);
    return 1.0; // FOG_DISABLED
}

// === Main program === //

void main()
{
    // Sampling scene color texture
    vec3 result = texture(uTexColor, vTexCoord).rgb;

    // Depth retrieval and distance calculation
    float depth = texture(uTexDepth, vTexCoord).r;
    depth = LinearizeDepth(depth, uNear, uFar);

    // Applying the fog factor to the resulting color
    float fogFactor = FogFactor(depth, uFogMode, uFogDensity, uFogStart, uFogEnd);
    fogFactor *= uSkyAffect * step(depth, uFar);
    result = mix(result, uFogColor, fogFactor);

    // Final color output
    FragColor = vec4(result, 1.0);
}
