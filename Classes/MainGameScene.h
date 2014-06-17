#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Field.h"
#include <iostream>

class MainGameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void update(const float delta);
    CREATE_FUNC(MainGameScene);
    
private:
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void proceedTouches(const std::vector<cocos2d::Touch*>& touches);
    

    
private:
    Field::MOVE_DIRECTION mDirection;
    FieldPtr mField;
    cocos2d::Size mVisibleSize;
    cocos2d::Vec2 mOrigin;
    cocos2d::Vec2 mPrevTouch;
};

#endif // __HELLOWORLD_SCENE_H__
