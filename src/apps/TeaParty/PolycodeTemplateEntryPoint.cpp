//
// Polycode template. Write your code here.
// 

#include "PolycodeTemplateEntryPoint.h"

PolycodeTemplateEntryPoint::PolycodeTemplateEntryPoint(PolycodeView *view) :
    core(new POLYCODE_CORE(view, 960, 540,false,false, 0,0,60))
{
//    Polycode::CoreServices::getInstance()->getResourceManager()->addArchive("/Users/adn/Desktop/default.pak");
//    Polycode::CoreServices::getInstance()->getResourceManager()->addDirResource("default");

	// Write your code here!
//   CoreServices::getInstance()->getRenderer()->setTextureFilteringMode(Renderer::TEX_FILTERING_NEAREST);
//	Screen *screen = new Screen();
//    mScene = new Scene(Scene::SCENE_2D);
//    mScene->getActiveCamera()->setOrthoSize(640, 480);
//    mScene->rootEntity.setPosition(-50, -100);
//    //mScene->getActiveCamera()->setProjectionMode(Polycode::Camera::ORTHO_SIZE_VIEWPORT);
//
//    auto scene2 = new Scene(Scene::SCENE_2D_TOPLEFT);
//    //scene2->getActiveCamera()->setOrthoSize(100, 100);
//    auto label2 = new Polycode::SceneLabel("Hello, Polycode!", 32);
//    scene2->addChild(label2);
//        
//	//SceneSprite *sprite = new SceneSprite("Resources/sprite_sheet.png", 93, 78);
//	//sprite->setScale(6,6);
//	//scene->addChild(sprite);
//	//sprite->addAnimation("ExampleAnimation", "0-29,29x6", 0.03);
//	//sprite->playAnimation("ExampleAnimation", 0, false);
//    
//	//SceneSprite *sprite = new SceneSprite(new SpriteSet("/Users/adn/Desktop/halal.xml"));
//	//sprite->setPosition(35,15);
//	////sprite->setScale(1,1);
//	//mScene->addChild(sprite);
//
//    auto label = new Polycode::SceneLabel("Hello, Polycode!", 32);
//    mScene->addChild(label);
//	//sprite->addAnimation("ExampleAnimation", "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,
//	//	22,23,24,25,26,27,28,29,29,29,29,29,29,29,29,29,29", 0.04);
//	//sprite->playAnimation("ExampleAnimation", 0, false);
//
//    //SceneImage *image = new SceneImage("/Users/adn/Desktop/dice.png");
//    //mScene->addChild(image);
//
//    SpriteSet *sprite = new SpriteSet("/Users/adn/Desktop/sprite_set.xml");
//    SceneSprite *sceneSprite = new SceneSprite(sprite);
//    sceneSprite->setSpriteByName("Explosion");
//    sceneSprite->setSpriteStateByName("default", 0, false);
//    //sceneSprite->setScale(4, 4);
//    mScene->addEntity(sceneSprite);
}

PolycodeTemplateEntryPoint::~PolycodeTemplateEntryPoint()
{
    
}

bool PolycodeTemplateEntryPoint::Update()
{
    mGame.update();
    return core->updateAndRender();
}