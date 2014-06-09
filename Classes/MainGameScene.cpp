#include "MainGameScene.h"

USING_NS_CC;

Scene* MainGameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainGameScene::create();
    scene->addChild(layer);
    return scene;
}

bool MainGameScene::init()
{
    mField.reset(new Field(this));
    
    // Start update
    srand(static_cast<unsigned int>(time(0)));
    schedule(schedule_selector(MainGameScene::update));
    
    return true;
}

void MainGameScene::update(const float delta)
{
    
    mField->update(delta);
}