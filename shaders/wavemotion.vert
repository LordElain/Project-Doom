in vec3 vertexPosition;
in vec3 vertexColor;

uniform float Time;
uniform float xs=2.0, zs=10.0; // frequencies
uniform float h=1.0; // height scale

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;



void main()
{

    float angle = 3.14*Time;
    mat4 rotX = mat4(1.f,0.0,0.0,0.0,
                     0.0,cos(angle),sin(angle),0.0,
                     0.0,-sin(angle),cos(angle),0.0,
                     0.0,0.0,0.0,1.f  );


    gl_Position = projectionMatrix*modelViewMatrix*rotX*vec4(vertexPosition,1.0);
}
