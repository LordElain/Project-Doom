#ifndef SPIELER_H
#define SPIELER_H
#include <QElapsedTimer>

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
#include "simplesphere.h"
#include "mapgen.h"
#include "modeltransformation.h"

#include "idleobserver.h"
#include "physics.h"



class Spieler: public IdleObserver
{
public:
    Spieler(DynamicCharacterWithCam* dynaCam);
    void doIt();

private:
    DynamicCharacterWithCam* m_DynaChWithCam;
    // Timer für genaue Delta Zeitberechnung
    QElapsedTimer m_Timer;

};

#endif // SPIELER_H

