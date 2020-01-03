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
    void SetzungTrafo_Build();




    //Geometry
    Geometry* e_Fish = new TriangleMesh(":/objects/Pufferfish_Mob.obj");
    Geometry* e_Coral =new TriangleMesh(":/objects/Environment_Coral_1.obj");
    Geometry* e_Seaw = new TriangleMesh(":/objects/Environment_Seaweed.obj");
    Geometry* b_Small = new TriangleMesh(":/objects/Buildings_Small_1.obj");
    Geometry* b_Medium = new TriangleMesh(":/objects/Buildings_Medium_1.obj");
    Geometry* b_Tall = new TriangleMesh(":/objects/Buildings_Tall_1.obj");
    Geometry* b_Spawn = new TriangleMesh(":/objects/Buildings_Spawn_1.obj");
    Geometry* b_Door = new TriangleMesh(":/objects/Buildings_Spawn_Door_1.obj");

    //Drawable
    Drawable* v_Plane = new Drawable(new SimplePlane(50.f));
    Drawable* model1_Fish = new Drawable(e_Fish);
    Drawable* model2 = new Drawable(e_Coral);
    Drawable* model3 = new Drawable(e_Seaw);
    Drawable* model4_Spawn = new Drawable(b_Spawn);


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

    Transformation* b_TSpawn1 = new Transformation();

};

#endif // MAPGEN_H
