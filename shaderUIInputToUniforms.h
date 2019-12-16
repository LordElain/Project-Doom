#ifndef SHADERUIINPUTTOUNIFORMS_H
#define SHADERUIINPUTTOUNIFORMS_H

#include <QObject>
#include "shadertimed.h"

class ShaderUIInputToUniforms : public QObject, public ShaderTimed
{
    Q_OBJECT
public:
    ShaderUIInputToUniforms();

public slots:
    void setX(int pX) {this->mX = pX;}
    void setY(int pY) {this->mY = pY;}
    void setZ(int pZ) {this->mZ = pZ;}

protected:
    virtual void setShaderUniforms() override;

private:
    float mX, mY, mZ;
};

#endif // SHADERUIINPUTTOUNIFORMS_H
