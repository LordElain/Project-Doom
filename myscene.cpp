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
#include "vector"
#include "physicaccessablecamera.h"
#include "opengl.h"
#include "scene.h"
#include "modeltransformation.h"
#include "simplecube.h"
#include "simplesphere.h"
#include "mainwindow.h"
#include "listener.h"
#include "audioengine.h"
#include "soundsource.h"




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
        Node* root=new Node();
       // Texture *t;
        PhysicObject* Mob;

        PhysicObject* Player;



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
        Drawable* model1_Fish = new Drawable(e_Fish);
        Drawable* model2 = new Drawable(e_Coral);
        Drawable* model3 = new Drawable(e_Seaw);
        Drawable* model4_Spawn = new Drawable(b_Spawn);

    //Transformation
        Transformation* f_TPuffer = new Transformation();

        Transformation* e_TCoral = new Transformation();
        Transformation* e_TSeaw = new Transformation();


        Transformation* b_TSpawn1 = new Transformation();

    //Nodes
        Node* transformationFish = new Node(f_TPuffer);
        Node* transformationEnvironment = new Node (e_TCoral);
        Node* transformationBuilding = new Node (b_TSpawn1);


    //Physiks
    int v_Slot = PhysicEngineManager::createNewPhysicEngineSlot(PhysicEngineName::BulletPhysicsLibrary);
    PhysicEngine* v_PhysicEngine = PhysicEngineManager::getPhysicEngineBySlot(v_Slot);

    //Mobs
        Mob = v_PhysicEngine->createNewPhysicObject(model1_Fish);
        PhysicObjectConstructionInfo* v_Constrinf_Mob = new PhysicObjectConstructionInfo();
        v_Constrinf_Mob->setCollisionHull(CollisionHull::BVHTriangleMesh);
        v_Constrinf_Mob->setMidpointTransformation(QMatrix4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1));
        v_Constrinf_Mob->setMass(3.f);
        Mob->setConstructionInfo(v_Constrinf_Mob);
        model1_Fish->getPhysicObject()->registerPhysicObject();
        f_TPuffer->translate(-5.f,0.f,0.f);


    //Envi
        Mob = v_PhysicEngine->createNewPhysicObject(model2);
        Mob = v_PhysicEngine->createNewPhysicObject(model3);
        model2->getPhysicObject()->registerPhysicObject();
        e_TCoral->translate(5.f,0.f,0.f);
        e_TSeaw->translate(5.0f,0.f,2.0f);



    //Buildings
        PhysicObject* Build = v_PhysicEngine->createNewPhysicObject(model4_Spawn);
        PhysicObjectConstructionInfo* v_Constrinf_Build = new PhysicObjectConstructionInfo();
        v_Constrinf_Build->setMass(10.f);
        v_Constrinf_Build->setLocalInertiaPoint(QVector3D(0.f, 0.f, 0.f));
        v_Constrinf_Build->setCollisionHull(CollisionHull::BVHTriangleMesh);
        v_Constrinf_Build->setBoxHalfExtends(QVector3D(0.5f, 0.5f, 0.5f));
        Build->setConstructionInfo(v_Constrinf_Build);
        model4_Spawn->getPhysicObject()->registerPhysicObject();
        model4_Spawn->setStaticGeometry(true);
        b_TSpawn1->translate(0.f,1.f,0.f);

    //Player
        Drawable* v_Ball;
        ModelTransformation* v_Transformation;

        // Zweiter Ball der gesteuert werden kann und den eine Kamera verfolgt
        v_Ball = new Drawable(new SimpleSphere(0.3f));
        v_Transformation = v_Ball->getProperty<ModelTransformation>();
        v_Transformation->translate(0.f, 1.f, 2.f);
        root->addChild(new Node(v_Ball));

        // Character Objekt erzeugen mit einer Verfolgerkamera
        DynamicCharacterWithCam* v_CharacterWithCam = v_PhysicEngine->createNewDynamicCharacterWithCam(v_Ball);
        // Kamera anhängen, die bestimmung der kameraposition wird nun komplett von dem character übernommen,  allein
        // die x achsendrehung kann noch beeinflusst werden
        v_CharacterWithCam->setCam(dynamic_cast<PhysicAccessableCamera*>(SceneManager::instance()->getActiveContext()->getCamera()));
        // Relative Kameraposition zum Drawable setzen
        v_CharacterWithCam->setRelativeCamPosition(0.f, 4.0f, 6.0f);
        v_CharacterWithCam->setUpDownView(-30.0F);
        // Physic Object registrieren


        v_Ball->getPhysicObject()->registerPhysicObject();

        new Spieler (v_CharacterWithCam);


    //Boden
        Drawable* v_Plane = new Drawable(new SimplePlane(20.f));
        v_Plane->getProperty<ModelTransformation>()->rotate(90, 1.f, 0.f, 0.f);
        v_Plane->setStaticGeometry(true); // Der Oberfläche ein statisches verhalten zuweisen
        PhysicObject* v_PlanePhys = v_PhysicEngine->createNewPhysicObject(v_Plane);
        PhysicObjectConstructionInfo* v_Constrinf = new PhysicObjectConstructionInfo();
        v_Constrinf->setCollisionHull(CollisionHull::BoxAABB); // Automatische generierung einer Box
        v_PlanePhys->setConstructionInfo(v_Constrinf);
        v_PlanePhys->registerPhysicObject();

    //Audio
        //AudioListener anlegen
        AudioListener* lAudioListener= new AudioListener();
        gAudioListenerNode = new Node(lAudioListener);
        AudioEngine::instance().init(AudioEngineType::QtStereo);

        //NatureAmbience ist Stereo und ändert daher als ambienter Sound seine "Position" nicht
        gAmbientSoundSource = new SoundSource(new SoundFile(path+QString("/sound/RollerMobster.wav")));
        gAmbientSoundSource->setLooping(true);
        gAmbientSoundSource->play();



    //Baum
        root->addChild(gAudioListenerNode);
        root->addChild(new Node(v_Plane));
        root->addChild(transformationEnvironment);
        transformationEnvironment->addChild(new Node(model2));
        transformationEnvironment->addChild(new Node(model3));
        root->addChild(transformationFish);
        transformationFish->addChild(new Node(model1_Fish));
        root->addChild(transformationBuilding);
        transformationBuilding->addChild(new Node(model4_Spawn));



    return root;
}
