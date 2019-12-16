uniform float hasTexture=0.0f;
uniform sampler2D textureMap;
uniform float Time=1;

in vec2 texCoords;
out vec4 fragColor;

void main()
{
    mat3 laplace = mat3(0.0,1.0,0.0,1.0,-4.0,1.0,0.0,1.0,0.0);
    mat3 gauss = mat3(1.0,2.0,1.0,2.0,4.0,2.0,1.0,2.0,1.0);
    mat3 Rechnung;
    vec3 color = vec3(0.0,0.0,0.0);
    ivec2 textureSize2d = textureSize(textureMap,0);
    float stepX = 1.0/textureSize2d.x;
    float stepY = 1.0/textureSize2d.y;

  Rechnung = gauss/16.0;
  //  Rechnung = laplace;

    if(hasTexture > 0.5)
    { //In the fragment shader, to get the color from the texture, you need to use the texture2d() glsl function. Like so:
      //@color = texture2d( textureUniform, texture );
        vec4 textureFrag = texture(textureMap, texCoords);
        fragColor = vec4(textureFrag.rgb, textureFrag.a);
    }

    if (texCoords.y < 0.5)
       {
            for (int i=-1; i<2; i++)
               {
                    for (int j=-1; j<2; j++)
                    {
                          color += float(Rechnung[i+1][j+1])*vec3(texture(textureMap, vec2(texCoords.x + float(i)*stepX,texCoords.y + float(j)*stepY)));
                    }
               }
        }
    else
    {
            color = vec3(texture(textureMap,texCoords));
    }

    fragColor = mix(texture(textureMap, texCoords), vec4(color,1.0), Time);

}
