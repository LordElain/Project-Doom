#include "shader.h"
#include "shaderuiinputtouniforms.h"

ShaderUIInputToUniforms::ShaderUIInputToUniforms()
{
}

void ShaderUIInputToUniforms::setShaderUniforms()
{
    QVector4D lAxis = QVector4D(mX, mY, mZ,0);
    ShaderTimed::setShaderUniforms();
    lAxis.normalize();
    this->shaderProgram()->setUniformValue("Time", lAxis);
}
