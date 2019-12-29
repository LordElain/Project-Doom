#include "mapgen.h"

MapGen::MapGen()
{

}

void MapGen::SetzungTrafo_Plane()
{

    v_TransformationPlane->rotate(-90.f, 1.f, 0.f, 0.f);
    t = v_Plane->getProperty<Texture>();
    t->loadPicture(":/modelstextures/kempten.bmp");



}

void MapGen::SetzungTrafo_Mobs()
{

    f_TPuffer->translate(5.f,10.f,0.f);
}

void MapGen::SetzungTrafo_Player()
{

}
