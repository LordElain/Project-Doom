#include "mapgen.h"

MapGen::MapGen()
{

}

void MapGen::SetzungTrafo_Plane()
{

    v_Plane->setStaticGeometry(true);
    v_TransformationPlane->rotate(-90.f, 1.f, 0.f, 0.f);
    PhysicObject* v_PlanePhys = v_PhysicEngine->createNewPhysicObject(v_Plane);
    PhysicObjectConstructionInfo* v_Constrinf = new PhysicObjectConstructionInfo();
    v_Constrinf->setCollisionHull(CollisionHull::BVHTriangleMesh); // Automatische generierung einer Box aus den Vertexpunkten
    v_PlanePhys->setConstructionInfo(v_Constrinf);
    v_PlanePhys->registerPhysicObject();



}

void MapGen::SetzungTrafo_Mobs()
{
    f_TPuffer->translate(0.f,10.f,0.f);

}
