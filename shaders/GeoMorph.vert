in vec3 vertexPosition;
in vec3 vertexColor;
in vec4 lAxis;

uniform float Time;


uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;


void main()
{
   /* float radius = 1.0;
    float veclength = sqrt(pow(vertexPosition.x,2.0)+pow(vertexPosition.y,2.0)+pow(vertexPosition.z,2.0));
    vec3 temp = vertexPosition + normalize(vertexPosition) * ((radius - veclength)*Time);
    vec4 t = vec4(temp,1.);
   //Kreis
   */

  float radius = 1.0;
  float angle = 3.14 * Time;
  vec4 Kreis = vec4(radius * cos(angle), radius * sin(angle), 1,0);


  //Kasten
  vec4 v2Norm = lAxis;
  vec4 End = mix(v2Norm,Kreis,Time);



    gl_Position = projectionMatrix*modelViewMatrix*End*vec4(vertexPosition,1);
}
