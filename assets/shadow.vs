#version 330

in vec3 vertexPosition;
in vec3 vertexNormal;
in vec2 vertexTexCoord;

uniform mat4 mvp;              // Model-View-Projection
uniform mat4 lightViewProj;    // Light camera view-proj matrix
uniform mat4 matModel;         // Model matrix

out vec3 fragNormal;
out vec2 fragTexCoord;
out vec4 fragPosLight;

void main() {
    fragNormal = mat3(matModel) * vertexNormal;
    fragTexCoord = vertexTexCoord;

    fragPosLight = lightViewProj * vec4(vertexPosition, 1.0);
    gl_Position = mvp * vec4(vertexPosition, 1.0);
}
