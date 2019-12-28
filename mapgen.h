#ifndef MAPGEN_H
#define MAPGEN_H

#include <QString>
#include <time.h>

#include "scenemanager.h"
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




class MapGen: public QString
{
public:
    MapGen();
    void SetzungTrafo_Plane();
    void SetzungTrafo_Envi();
    void SetzungTrafo_Mobs();
    void SetzungTrafo();
    void SetzungTrafo_Player();

    Texture *t;

    //Geometry
    Geometry* e_Fish = new TriangleMesh(":/objects/Pufferfish_Mob.obj");
    Geometry* e_Coral =new TriangleMesh(":/objects/Environment_Coral_1.obj");
    Geometry* e_Seaw = new TriangleMesh(":/objects/Environment_Seaweed.obj");

    //Drawable
    Drawable* v_Plane = new Drawable(new SimplePlane(50.f));
    Drawable* model1 = new Drawable(e_Fish);
    Drawable* model2 = new Drawable(e_Coral);
    Drawable* model3 = new Drawable(e_Seaw);


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
