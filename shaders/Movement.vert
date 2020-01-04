in vec4 vertexPosition;
in vec3 vertexNormal;
in vec4 vertexColor;
in vec2 textureCoords;

uniform float Time;

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

out vec2 texCoords;

void main()
{
    mat4 t = mat4 (Time,0,0,0) * vertexPosition;
    gl_Position = projectionMatrix * modelViewMatrix * vertexPosition * t;

    texCoords=textureCoords;
}
