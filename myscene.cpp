#include <QString>
#include <time.h>

#include "scenemanager.h"
#include "screenrenderer.h"
#include "simpleplane.h"
#include "shader.h"
#include "shadertimed.h"
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
#include "spieler.h"
#include "mapgen.h"
#include "vector"
#include "physicaccessablecamera.h"
#include "opengl.h"
#include "scene.h"
#include "modeltransformation.h"
#include "simplecube.h"
#include "simplesphere.h"
#include "mainwindow.h"






Node *initScene1();

ScreenRenderer* sortedRenderer;
ScreenRenderer* preOrderRenderer;
unsigned int myScene, myScene2;
SoundSource *gSoundSource1, *gSoundSource2, *gSoundSource3, *gAmbientSoundSource;
Node* gAudioListenerNode;

class SceneSwitcher: public Listener
{
    void keyboard(int key, int modifier)
    {
        if (key == '1')
        {
            sortedRenderer->setScene(myScene);
            gSoundSource1->play();
        }
        else if(key =='2')
        {
            sortedRenderer->setScene(myScene2);
            gSoundSource2->play();
        }
        else if (key == 'l' || key == 'L')
        {
            gSoundSource3->play();
        }
    }
};

void SceneManager::initScenes()
{

    PhysicAccessableCamera* cam = new PhysicAccessableCamera;
    RenderingContext* myContext = new RenderingContext(cam);
    unsigned int myContextNr = SceneManager::instance()->addContext(myContext);
    unsigned int myScene = SceneManager::instance()->addScene(initScene1());
    ScreenRenderer* myRenderer = new ScreenRenderer(myContextNr, myScene);
    Q_UNUSED(myRenderer);
    myScene = SceneManager::instance()->addScene(initScene1());

    //Vorsicht: Die Szene muss initialisiert sein, bevor das Fenster verändert wird (Fullscreen)
    SceneManager::instance()->setActiveScene(myScene);
    SceneManager::instance()->setActiveContext(myContextNr);
    SceneManager::instance()->setFullScreen();
}


Node *initScene1()
{
    //Deklaration
    QString path(SRCDIR);
    QString shaderPath(path+"/");
    MapGen Gen;
    Node* root=new Node();

    PhysicObject* Mob;

    int v_Slot = PhysicEngineManager::createNewPhysicEngineSlot(PhysicEngineName::BulletPhysicsLibrary);
    PhysicEngine* v_PhysicEngine = PhysicEngineManager::getPhysicEngineBySlot(v_Slot);

    //Physiks
    PhysicObject* v_PlanePhys = v_PhysicEngine->createNewPhysicObject(Gen.v_Plane);
    PhysicObjectConstructionInfo* v_Constrinf = new PhysicObjectConstructionInfo();
    Gen.v_Plane->setStaticGeometry(true);
    v_Constrinf->setCollisionHull(CollisionHull::BoxAABB); // Automatische generierung einer Box aus den Vertexpunkten
    v_PlanePhys->setConstructionInfo(v_Constrinf);
    v_PlanePhys->registerPhysicObject();

    //Mobs
    Mob = v_PhysicEngine->createNewPhysicObject(Gen.model1);
    PhysicObjectConstructionInfo* v_Constrinf_Mob = new PhysicObjectConstructionInfo();
    v_Constrinf_Mob->setCcdActivation(true);
    v_Constrinf_Mob->setCollisionHull(CollisionHull::BVHTriangleMesh);
    v_Constrinf_Mob->setMass(2.f);
    v_Constrinf_Mob->setRollingFriction(0.1f);
    v_Constrinf_Mob->setMidpointTransformation(QMatrix4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1));
    Mob->setConstructionInfo(v_Constrinf_Mob);
    Gen.model1->getPhysicObject()->registerPhysicObject();
    Gen.model1->setStaticGeometry(true);

    //Envi
   /* Gen.model2->getPhysicObject()->registerPhysicObject();
    Gen.model2->setStaticGeometry(true);
    Gen.model3->getPhysicObject()->registerPhysicObject();
    Gen.model3->setStaticGeometry(true);
*/

    //Player
    Drawable* v_Ball;
    ModelTransformation* v_Transformation;
    v_Ball = new Drawable(new SimpleSphere(0.5f));
    v_Transformation = v_Ball->getProperty<ModelTransformation>();
    v_Transformation->translate(0.f, 1.f, 0.f);
    root->addChild(new Node(v_Ball));
    Mob = v_PhysicEngine->createNewPhysicObject(v_Ball);
    DynamicCharacterWithCam* v_CharacterWithCam = v_PhysicEngine->createNewDynamicCharacterWithCam(v_Ball);
    v_CharacterWithCam->setCam(dynamic_cast<PhysicAccessableCamera*>(SceneManager::instance()->getActiveContext()->getCamera()));
    // Relative Kameraposition zum Drawable setzen
    v_CharacterWithCam->setRelativeCamPosition(0.f, 4.f, 6.f);
    v_CharacterWithCam->setUpDownView(-35.0F);
    new Spieler (v_CharacterWithCam);

    v_Ball->getPhysicObject()->registerPhysicObject();



    //Nodes
    Node* transformationFish = new Node(Gen.f_TPuffer);
    Node* transformationPlaneNode = new Node(Gen.v_TransformationPlane);
    Node* transformationEnvironment = new Node (Gen.e_TCoral);


    //Funktionen
    Gen.SetzungTrafo_Plane();
    Gen.SetzungTrafo_Mobs();

    //Baum
    root->addChild(transformationPlaneNode);
    transformationPlaneNode->addChild(new Node(Gen.v_Plane));
    root->addChild(transformationEnvironment);
    transformationEnvironment->addChild(new Node(Gen.model2));
    transformationEnvironment->addChild(new Node(Gen.model3));
    root->addChild(transformationFish);
    transformationFish->addChild(new Node(Gen.model1));



    return root;
}
