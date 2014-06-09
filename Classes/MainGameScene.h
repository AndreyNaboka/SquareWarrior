#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Field.h"

class MainGameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void update(const float delta);
    CREATE_FUNC(MainGameScene);
    
private:
    FieldPtr mField;
};

#endif // __HELLOWORLD_SCENE_H__
