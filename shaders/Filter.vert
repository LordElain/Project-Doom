in vec3 vertexPosition;
in vec2 textureCoords;

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;


out vec3 Color;
out vec2 texCoords;

void main()
{
    gl_Position = projectionMatrix*modelViewMatrix*vec4(vertexPosition,1);
    Color = vec3 (1.f,1.f,1.f);
    texCoords=textureCoords;
}
