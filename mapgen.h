#ifndef MAPGEN_H
#define MAPGEN_H
#include "screenrenderer.h"
#include "simpleplane.h"
#include "shader.h"
#include "transformation.h"
#include "mousekeyboardcameracontroller.h"
#include "trianglemesh.h"
#include "texture.h"
#include "keyboardtransformation.h"
#include "color.h"
#include "audioengine.h"
#include "soundsource.h"
#include "shadermanager.h"
#include "efx-presets.h"
#include "vector"

#include <QString>

class MapGen
{
public:
    MapGen();
    void SetzungTrafo_Plane();
    void SetzungTrafo_Envi();
    void SetzungTrafo_Mobs();
    void SetzungTrafo();


  //Var
    int m_x;
    int m_y;
    Drawable* v_Plane = new Drawable(new SimplePlane(50.f));

  //Physics
    int v_Slot = PhysicEngineManager::createNewPhysicEngineSlot(PhysicEngineName::BulletPhysicsLibrary);
    PhysicEngine* v_PhysicEngine = PhysicEngineManager::getPhysicEngineBySlot(v_Slot);

  //Drawable

  //Transformationen

    Transformation* v_TransformationPlane = new Transformation();
    Transformation* f_TPuffer = new Transformation();
    Transformation* f_TPuffer2 = new Transformation();
    Transformation* f_TPuffer3 = new Transformation();

    Transformation* e_TCoral = new Transformation();
    Transformation* e_TCoral2 = new Transformation();
    Transformation* e_TCoral3 = new Transformation();

    Transformation* e_TSeaw = new Transformation();
    Transformation* e_TSeaw2 = new Transformation();
    Transformation* e_TSeaw3 = new Transformation();

};

#endif // MAPGEN_H
