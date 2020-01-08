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
SoundSource *gSoundSource1, *gAmbientSoundSource;
Node* gAudioListenerNode;

class SceneSwitcher: public Listener
{

};

void SceneManager::initScenes()
{

    PhysicAccessableCamera* cam = new PhysicAccessableCamera;
    RenderingContext* myContext = new RenderingContext(cam);
    unsigned int myContextNr = SceneManager::instance()->addContext(myContext);
    unsigned int myScene = SceneManager::instance()->addScene(initScene1());
    ScreenRenderer* myRenderer = new ScreenRenderer(myContextNr, myScene);
    Q_UNUSED(myRenderer)
    myScene = SceneManager::instance()->addScene(initScene1());

    //Vorsicht: Die Szene muss initialisiert sein, bevor das Fenster verändert wird (Fullscreen)
    SceneManager::instance()->setActiveScene(myScene);
    SceneManager::instance()->setActiveContext(myContextNr);
    //SceneManager::instance()->setFullScreen();
}


Node *initScene1()
{
    //Deklaration
        QString path(SRCDIR);
        QString shaderPath(path+"/");
        Node* root=new Node();
        Texture *t;
        Shader* s = ShaderManager::getShader((":/shaders/Filter.vert"), (":/shaders/Filter.frag"));
        //Shader* s1 = ShaderManager::getShader((":/shaders/Movement.vert"), (":/shaders/Filter.frag"));

    //Geometry
        Geometry* e_Fish = new TriangleMesh(":/objects/Pufferfish_Mob.obj");
        Geometry* e_Coral =new TriangleMesh(":/objects/Environment_Coral_1.obj");
        Geometry* e_Seaw = new TriangleMesh(":/objects/Environment_Seaweed.obj");
        Geometry* b_Small = new TriangleMesh(":/objects/Buildings_Small_1.obj");
        Geometry* b_Medium = new TriangleMesh(":/objects/Buildings_Medium_1.obj");
        Geometry* b_Tall = new TriangleMesh(":/objects/Buildings_Tall_1.obj");
        Geometry* b_Spawn_links = new TriangleMesh(":/objects/Buildings_Spawn_links.obj");
        Geometry* b_Door = new TriangleMesh(":/objects/Buildings_Spawn_Door_1.obj");
        Geometry* b_Spawn_rechts = new TriangleMesh(":/objects/Buildings_Spawn_rechts.obj");
        Geometry* b_Spawn_oben = new TriangleMesh(":/objects/Buildings_Spawn_oben.obj");
        Geometry* b_Spawn_unten = new TriangleMesh(":/objects/Buildings_Spawn_unten.obj");

    //Drawable
        Drawable* model1_Fish = new Drawable(e_Fish);
        Drawable* model2 = new Drawable(e_Coral);
        Drawable* model3 = new Drawable(e_Seaw);
        Drawable* model4_Spawn = new Drawable(b_Spawn_oben);
        Drawable* model5_Small = new Drawable(b_Small);
        Drawable* model6_Middle = new Drawable(b_Medium);
        Drawable* model7_Tall = new Drawable(b_Tall);
        Drawable* model8_Spawn2 = new Drawable(b_Spawn_links);
        Drawable* model9_Spawn3 = new Drawable(b_Spawn_rechts);
        Drawable* model10_Spawn4 = new Drawable(b_Spawn_unten);
        Drawable* model11_SDoor = new Drawable(b_Door);
        Drawable* model12_Small2 = new Drawable(b_Small);
        Drawable* model13_Middle2 = new Drawable(b_Medium);
        Drawable* model14_Tall2 = new Drawable(b_Tall);
        Drawable* model15_Tall3 = new Drawable(b_Tall);
        Drawable* model16_Tall4 = new Drawable(b_Tall);
        Drawable* model17_Small3 = new Drawable(b_Small);
        Drawable* model18_Small4 = new Drawable(b_Small);
        Drawable* model19_Middle3 = new Drawable(b_Medium);
        Drawable* model20_Tall5 = new Drawable(b_Tall);
        Drawable* model21_Small5 = new Drawable(b_Small);

    //Transformation
        //Mobs
        Transformation* f_TPuffer = new Transformation();
        Node* transformationFish = new Node(f_TPuffer);

        //Korallen
        Transformation* e_TCoral = new Transformation();
        Node* transformationEnvironment = new Node (e_TCoral);

        //SeaWeed
        Transformation* e_TSeaw = new Transformation();
        Node* transformationEnvironment1 = new Node (e_TSeaw);

        //Spawn
        Transformation* b_TSpawn1 = new Transformation();
        Node* transformationBuildingSpawn = new Node (b_TSpawn1);

        Transformation* b_TSpawn2 = new Transformation();
        Node* transformationBuildingSpawn2 = new Node (b_TSpawn2);

        Transformation* b_TSpawn3 = new Transformation();
        Node* transformationBuildingSpawn3 = new Node (b_TSpawn3);

        Transformation* b_TSpawn4 = new Transformation();
        Node* transformationBuildingSpawn4 = new Node (b_TSpawn4);

        Transformation* b_TSpawn5 = new Transformation();
        Node* transformationBuildingSpawn5 = new Node (b_TSpawn5);

        //Small
        Transformation* b_TSmall = new Transformation();
        Node* transformationBuilding1 = new Node(b_TSmall);

        Transformation* b_TSmall2 = new Transformation();
        Node* transformationBuilding4 = new Node(b_TSmall2);

        Transformation* b_TSmall3 = new Transformation();
        Node* transformationBuilding9 = new Node(b_TSmall3);

        Transformation* b_TSmall4 = new Transformation();
        Node* transformationBuilding10 = new Node(b_TSmall4);

        Transformation* b_TSmall5 = new Transformation();
        Node* transformationBuilding13 = new Node(b_TSmall5);


        //Middle
        Transformation* b_TMiddle = new Transformation();
        Node* transformationBuilding2 = new Node(b_TMiddle);

        Transformation* b_TMiddle2 = new Transformation();
        Node* transformationBuilding5 = new Node(b_TMiddle2);

        Transformation* b_TMiddle3 = new Transformation();
        Node* transformationBuilding11 = new Node(b_TMiddle3);

        //Tall
        Transformation* b_TTall = new Transformation();
        Node* transformationBuilding3 = new Node (b_TTall);

        Transformation* b_TTall2 = new Transformation();
        Node* transformationBuilding6 = new Node (b_TTall2);

        Transformation* b_TTall3 = new Transformation();
        Node* transformationBuilding7 = new Node (b_TTall3);

        Transformation* b_TTall4 = new Transformation();
        Node* transformationBuilding8 = new Node (b_TTall4);

        Transformation* b_TTall5 = new Transformation();
        Node* transformationBuilding12 = new Node (b_TTall5);

    //Physiks
    int v_Slot = PhysicEngineManager::createNewPhysicEngineSlot(PhysicEngineName::BulletPhysicsLibrary);
    PhysicEngine* v_PhysicEngine = PhysicEngineManager::getPhysicEngineBySlot(v_Slot);

    //Mobs
        PhysicObject* Mob;
        Mob = v_PhysicEngine->createNewPhysicObject(model1_Fish);
        PhysicObjectConstructionInfo* v_Constrinf_Mob = new PhysicObjectConstructionInfo();
        v_Constrinf_Mob->setCollisionHull(CollisionHull::SphereAABB);
        v_Constrinf_Mob->setCcdActivation(true);
        //v_Constrinf_Mob->setMidpointTransformation(QMatrix4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1));
        v_Constrinf_Mob->setMass(1.f);

        Mob->setConstructionInfo(v_Constrinf_Mob);
        model1_Fish->getPhysicObject()->registerPhysicObject();


        f_TPuffer->translate(10.f,0.1f,0.f);



    //Envi
        PhysicObject* Envi;
        Envi = v_PhysicEngine->createNewPhysicObject(model2);
        Envi = v_PhysicEngine->createNewPhysicObject(model3);

        model2->getPhysicObject()->registerPhysicObject();
        model3->getPhysicObject()->registerPhysicObject();
        e_TCoral->translate(7.f,0.1f,0.f);
        e_TSeaw->translate(5.0f,0.f,2.0f);

    //Spawn
       model4_Spawn->setStaticGeometry(true);
       model8_Spawn2->setStaticGeometry(true);
       model9_Spawn3->setStaticGeometry(true);
       model10_Spawn4->setStaticGeometry(true);
    //   model11_SDoor->setStaticGeometry(true);
       PhysicObject* Spawn = v_PhysicEngine->createNewPhysicObject(model4_Spawn);
       Spawn = v_PhysicEngine->createNewPhysicObject(model8_Spawn2);
       Spawn = v_PhysicEngine->createNewPhysicObject(model9_Spawn3);
       Spawn = v_PhysicEngine->createNewPhysicObject(model10_Spawn4);
       Spawn = v_PhysicEngine->createNewPhysicObject(model11_SDoor);
       model4_Spawn->getPhysicObject()->registerPhysicObject();
       model8_Spawn2->getPhysicObject()->registerPhysicObject();
       model9_Spawn3->getPhysicObject()->registerPhysicObject();
       model10_Spawn4->getPhysicObject()->registerPhysicObject();
       model11_SDoor->getPhysicObject()->registerPhysicObject();

       b_TSpawn1->translate(0.f,0.05f,0.f);
       b_TSpawn2->translate(-0.05f,0.f,0.f);
       b_TSpawn3->translate(0.05f,0.f,0.f);
       b_TSpawn4->translate(0.f,0.f,-1.f);
       b_TSpawn5->translate(0.f,0.f,4.f);
      // b_TSpawn5->rotate(30,0.f,1.f,0.f);


    //Buildings
        model5_Small->setStaticGeometry(true);
        model6_Middle->setStaticGeometry(true);
        model7_Tall->setStaticGeometry(true);
        model12_Small2->setStaticGeometry(true);
        model13_Middle2->setStaticGeometry(true);
        model14_Tall2->setStaticGeometry(true);
        model15_Tall3->setStaticGeometry(true);
        model16_Tall4->setStaticGeometry(true);
        model17_Small3->setStaticGeometry(true);
        model18_Small4->setStaticGeometry(true);
        model19_Middle3->setStaticGeometry(true);
        model20_Tall5->setStaticGeometry(true);
        model21_Small5->setStaticGeometry(true);
        PhysicObject* Build = v_PhysicEngine->createNewPhysicObject(model5_Small);
        Build = v_PhysicEngine->createNewPhysicObject(model6_Middle);
        Build = v_PhysicEngine->createNewPhysicObject(model7_Tall);
        Build = v_PhysicEngine->createNewPhysicObject(model12_Small2);
        Build = v_PhysicEngine->createNewPhysicObject(model13_Middle2);
        Build = v_PhysicEngine->createNewPhysicObject(model14_Tall2);
        Build = v_PhysicEngine->createNewPhysicObject(model15_Tall3);
        Build = v_PhysicEngine->createNewPhysicObject(model16_Tall4);
        Build = v_PhysicEngine->createNewPhysicObject(model17_Small3);
        Build = v_PhysicEngine->createNewPhysicObject(model18_Small4);
        Build = v_PhysicEngine->createNewPhysicObject(model19_Middle3);
        Build = v_PhysicEngine->createNewPhysicObject(model20_Tall5);
        Build = v_PhysicEngine->createNewPhysicObject(model21_Small5);
        PhysicObjectConstructionInfo* v_Constrinf_Build = new PhysicObjectConstructionInfo();
        v_Constrinf_Build->setMass(10.f);
        //v_Constrinf_Build->setLocalInertiaPoint(QVector3D(0.f, 0.f, 0.f));
        v_Constrinf_Build->setCollisionHull(CollisionHull::BVHTriangleMesh);
        //v_Constrinf_Build->setBoxHalfExtends(QVector3D(0.5f, 0.5f, 0.5f));
        Build->setConstructionInfo(v_Constrinf_Build);        
        model5_Small->getPhysicObject()->registerPhysicObject();
        model6_Middle->getPhysicObject()->registerPhysicObject();
        model7_Tall->getPhysicObject()->registerPhysicObject();
        model12_Small2->getPhysicObject()->registerPhysicObject();
        model13_Middle2->getPhysicObject()->registerPhysicObject();
        model14_Tall2->getPhysicObject()->registerPhysicObject();
        model15_Tall3->getPhysicObject()->registerPhysicObject();
        model16_Tall4->getPhysicObject()->registerPhysicObject();
        model17_Small3->getPhysicObject()->registerPhysicObject();
        model18_Small4->getPhysicObject()->registerPhysicObject();
        model19_Middle3->getPhysicObject()->registerPhysicObject();
        model20_Tall5->getPhysicObject()->registerPhysicObject();
        model21_Small5->getPhysicObject()->registerPhysicObject();

        b_TSmall->translate(-16.f,0.1f,8.f);
        b_TSmall->rotate(90.f,0.f,1.f,0.f);
        b_TMiddle->translate(-16.f,0.1f,16.f);
        b_TMiddle->rotate(90.f,0.f,1.f,0.f);
        b_TTall->translate(8.0f,0.1f,-8.f);
        b_TSmall2->translate(-8.f,0.1f,0.f);
        b_TMiddle2->translate(5.f,0.1f,13.f);
        b_TTall2->translate(-8.f,0.1f,24.f);
        b_TTall3->translate(0.f,0.1f,24.f);
        b_TTall4->translate(8.f,0.1f,24.f);
        b_TSmall3->translate(16.f,0.1f,-8.f);
        b_TSmall4->translate(24.f,0.1f,0.f);
        b_TMiddle3->translate(24.f,0.1f,8.f);
        b_TTall5->translate(24.f,0.1f,16.f);
        b_TSmall5->translate(16.f,0.1f,24.f);


    //Player
        Drawable* v_Ball;
        ModelTransformation* v_Transformation;

        // Zweiter Ball der gesteuert werden kann und den eine Kamera verfolgt
        v_Ball = new Drawable(new SimpleSphere(0.3f));
        v_Transformation = v_Ball->getProperty<ModelTransformation>();
        v_Transformation->translate(0.f, 0.5f, 0.f);
        v_Transformation->rotate(180,0.f,1.f,0.f);
        root->addChild(new Node(v_Ball));

        // Character Objekt erzeugen mit einer Verfolgerkamera
        DynamicCharacterWithCam* v_CharacterWithCam = v_PhysicEngine->createNewDynamicCharacterWithCam(v_Ball);
        // Kamera anhängen, die bestimmung der kameraposition wird nun komplett von dem character übernommen,  allein
        // die x achsendrehung kann noch beeinflusst werden
        v_CharacterWithCam->setCam(dynamic_cast<PhysicAccessableCamera*>(SceneManager::instance()->getActiveContext()->getCamera()));
        // Relative Kameraposition zum Drawable setzen
        v_CharacterWithCam->setRelativeCamPosition(0.f, 4.0f, 6.0f);
        //v_CharacterWithCam->setUpDownView(15.0F);
        v_CharacterWithCam->setUpDownView(-35.0F);
        v_Ball->getPhysicObject()->registerPhysicObject();

        new Spieler (v_CharacterWithCam);


    //Boden
        Drawable* v_Plane = new Drawable(new SimplePlane(200.f));
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
        AudioEngine::instance().init(AudioEngineType::OpenAL3D);
        //Node *lSource1Node = new Node(gSoundSource1);

        //NatureAmbience ist Stereo und ändert daher als ambienter Sound seine "Position" nicht
        gSoundSource1 = new SoundSource(new SoundFile(path+QString("/sound/RollerMobster_edit.wav")));
      //  gAmbientSoundSource->setLooping(true);
        gSoundSource1->play();

    //Textur
        t = v_Plane->getProperty<Texture>();
        t->loadPicture(path + QString("/modelstextures/Boden_re.jpg"));
        v_Plane->setShader(s);

        t = model1_Fish->getProperty<Texture>();
        t->loadPicture(path + QString("/modelstextures/Pufferfish_2.jpg"));
        model1_Fish->setShader(s);

        t = model4_Spawn->getProperty<Texture>();
        t->loadPicture(path + QString("/modelstextures/image.jpg"));
        model4_Spawn->setShader(s);

        t = model5_Small->getProperty<Texture>();
        t->loadPicture(path + QString("/modelstextures/image.jpg"));
        model5_Small->setShader(s);

        t = model6_Middle->getProperty<Texture>();
        t->loadPicture(path + QString("/modelstextures/image.jpg"));
        model6_Middle->setShader(s);



    //Baum
        root->addChild(gAudioListenerNode);
        root->addChild(new Node(v_Plane));
        root->addChild(transformationEnvironment);
        transformationEnvironment->addChild(new Node(model2));
        root->addChild(transformationEnvironment1);
        transformationEnvironment1->addChild(new Node(model3));
        root->addChild(transformationFish);
        transformationFish->addChild(new Node(model1_Fish));
        root->addChild(transformationBuildingSpawn);
        transformationBuildingSpawn->addChild(new Node(model4_Spawn));
        root->addChild(transformationBuilding1);
        transformationBuilding1->addChild(new Node(model5_Small));
        root->addChild(transformationBuilding2);
        transformationBuilding2->addChild(new Node(model6_Middle));
        root->addChild(transformationBuilding3);
        transformationBuilding3->addChild(new Node(model7_Tall));
        root->addChild(transformationBuildingSpawn2);
        transformationBuildingSpawn2->addChild(new Node(model8_Spawn2));
        root->addChild(transformationBuildingSpawn3);
        transformationBuildingSpawn3->addChild(new Node(model9_Spawn3));
        root->addChild(transformationBuildingSpawn4);
        transformationBuildingSpawn4->addChild(new Node(model10_Spawn4));
        transformationBuildingSpawn3->addChild(transformationBuildingSpawn5);
        transformationBuildingSpawn5->addChild(new Node(model11_SDoor));
       // transformationBuildingSpawn5->addChild(new Node(gSoundSource1));
        root->addChild(transformationBuilding4);
        transformationBuilding4->addChild(new Node(model12_Small2));
        root->addChild(transformationBuilding5);
        transformationBuilding5->addChild(new Node(model13_Middle2));
        root->addChild(transformationBuilding6);
        transformationBuilding6->addChild(new Node(model14_Tall2));
        root->addChild(transformationBuilding7);
        transformationBuilding7->addChild(new Node(model15_Tall3));
        root->addChild(transformationBuilding8);
        transformationBuilding8->addChild(new Node(model16_Tall4));
        root->addChild(transformationBuilding9);
        transformationBuilding9->addChild(new Node(model17_Small3));
        root->addChild(transformationBuilding10);
        transformationBuilding10->addChild(new Node(model18_Small4));
        root->addChild(transformationBuilding11);
        transformationBuilding11->addChild(new Node(model19_Middle3));
        root->addChild(transformationBuilding12);
        transformationBuilding12->addChild(new Node(model20_Tall5));
        root->addChild(transformationBuilding13);
        transformationBuilding13->addChild(new Node(model21_Small5));



    return root;
}
