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
    SceneSwitcher* lSwitch = new SceneSwitcher();
    Camera* cam = new Camera();
    CameraController* camController = new MouseKeyboardCameraController(cam);
    Q_UNUSED(camController);
    RenderingContext* myContext = new RenderingContext(cam);
    unsigned int myContextNr = SceneManager::instance()->addContext(myContext);
    myScene = SceneManager::instance()->addScene(initScene1());
    sortedRenderer = new ScreenRenderer(myContextNr, myScene);
    Q_UNUSED(lSwitch);

    //Vorsicht: Die Szene muss initialisiert sein, bevor das Fenster verändert wird (Fullscreen)
    SceneManager::instance()->setActiveScene(myScene);
    SceneManager::instance()->setActiveContext(myContextNr);
    SceneManager::instance()->setFullScreen();
}


Node *initScene1()
{
    //Deklaration
    srand (time(NULL));
    QString path(SRCDIR);
    QString shaderPath(path+"/");
    MapGen Gen;
    std::vector<std::vector<int>>Koord{3,std::vector<int>(20)};


/*
    int tx = rand() % 5 + 1;
    int tz = rand() % 5 + 1;
    int t_tx = 1;
    int t_tz = 1;
    const int ty = 0;
    bool status = false;
*/
    //Nodes
    Node* transformationFish = new Node(Gen.f_TPuffer);
    Node* transformationPlaneNode = new Node(Gen.v_TransformationPlane);
    Node* transformationEnvironment = new Node (Gen.e_TCoral);
    Node* root=new Node();


    //Funktionen
  /*
   *  t = Gen.model1->getProperty<Texture>();
    t->loadPicture(path + QString("/modelstextures/ogrehead_diffuse.png"));
   * Koord.at(0) = {tx,ty,tz};
    Koord.at(0).at(0);//X-Koordinate. Bei Eintrag 0, Y-Koordinate (bei 2.at) (1)
    Koord.at(0).at(1);
    do
    {
        Koord.emplace_back(tx,ty,tz);
        e_Coral->translate(tx,ty,tz);
        t_tx = tx;
        t_tz = tz;

        do
        {
            tx = rand () % 10 + 1;
            tz = rand () % 10 + 1;
        }
        while(t_tx == tx || t_tz == tz);


        status = true;
    }
    while(status != true);
*/


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
