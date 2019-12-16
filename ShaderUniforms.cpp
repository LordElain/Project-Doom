#include "shader.h"
#include "ShaderUniforms.h"

ShaderUniforms::ShaderUniforms()
{
}

void ShaderUniforms::setShaderUniforms()
{
    QVector3D VekU = QVector3D(mX, mY, mZ);
    ShaderTimed::setShaderUniforms();
    VekU.normalize();
    this->shaderProgram()->setUniformValue("Vek", VekU);
}
