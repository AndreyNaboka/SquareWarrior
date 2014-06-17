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
    mVisibleSize = Director::getInstance()->getVisibleSize();
    mOrigin      = Director::getInstance()->getVisibleOrigin();
    
    mField.reset(new Field(this));
    
    // Start update
    srand(static_cast<unsigned int>(time(0)));
    schedule(schedule_selector(MainGameScene::update));
    
    
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan=std::bind(&MainGameScene::onTouchesBegan, this, std::placeholders::_1, std::placeholders::_2);
    listener->onTouchesMoved=std::bind(&MainGameScene::onTouchesMoved, this, std::placeholders::_1, std::placeholders::_2);
    listener->onTouchesEnded=std::bind(&MainGameScene::onTouchesEnded, this, std::placeholders::_1, std::placeholders::_2);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 100);
    
    mPrevTouch = cocos2d::Vec2(mOrigin.x + (mVisibleSize.width / 2), mOrigin.y + (mVisibleSize.height / 2));
    
    return true;
}

void MainGameScene::proceedTouches(const std::vector<cocos2d::Touch *> &touches)
{
    
    if ((*touches.begin())->getLocation().distance(mPrevTouch) < 20.0f)
        return;

    
    const cocos2d::Vec2 centerOfScreen = cocos2d::Vec2(mOrigin.x + (mVisibleSize.width / 2), mOrigin.y + (mVisibleSize.height / 2));
    
    
    cocos2d::Vec2 upDirection(mOrigin.x + (mVisibleSize.width / 2.0), mOrigin.y + mVisibleSize.height);
    cocos2d::Vec2 upDirectionN = centerOfScreen - upDirection;
    upDirectionN.normalize();

    cocos2d::Vec2 downDirection(mOrigin.x + (mVisibleSize.width / 2.0), mOrigin.y);
    cocos2d::Vec2 downDirectionN = centerOfScreen - downDirection;
    downDirectionN.normalize();

    cocos2d::Vec2 leftDirection(mOrigin.x, mOrigin.y + (mVisibleSize.height / 2.0));
    cocos2d::Vec2 leftDirectionN = centerOfScreen - leftDirection;
    leftDirectionN.normalize();

    cocos2d::Vec2 rightDirection(mOrigin.x + mVisibleSize.width, mOrigin.y + (mVisibleSize.height / 2.0));
    cocos2d::Vec2 rightDirectionN = centerOfScreen - rightDirection;
    rightDirectionN.normalize();



    cocos2d::Vec2 touch = (*touches.begin())->getLocation();
    cocos2d::Vec2 touchToPrevTouch = mPrevTouch - touch;
    touchToPrevTouch.normalize();
    mPrevTouch = touch;
    
    float angleBetweenUp    = acos(cocos2d::Vec2::dot(upDirectionN, touchToPrevTouch));
    float angleBetweenDown  = acos(cocos2d::Vec2::dot(downDirectionN, touchToPrevTouch));
    float angleBetweenLeft  = acos(cocos2d::Vec2::dot(leftDirectionN, touchToPrevTouch));
    float angleBetweenRight = acos(cocos2d::Vec2::dot(rightDirectionN, touchToPrevTouch));

    
    
    if (angleBetweenDown < angleBetweenUp && angleBetweenDown < angleBetweenLeft && angleBetweenDown < angleBetweenRight)
    {
        mDirection = Field::MOVE_DIRECTION::BOTTOM;
        
    } else if (angleBetweenUp < angleBetweenDown && angleBetweenUp < angleBetweenLeft && angleBetweenUp < angleBetweenRight)
    {
        mDirection = Field::MOVE_DIRECTION::TOP;
    
    } else if (angleBetweenLeft < angleBetweenDown && angleBetweenLeft < angleBetweenRight && angleBetweenLeft < angleBetweenUp)
    {
        mDirection = Field::MOVE_DIRECTION::LEFT;
    
    } else if (angleBetweenRight < angleBetweenDown && angleBetweenRight < angleBetweenLeft && angleBetweenRight < angleBetweenUp)
    {
        mDirection = Field::MOVE_DIRECTION::RIGHT;
    }
    
    std::cout << "Direction: " << Field::directionToString(mDirection) << std::endl;
}

void MainGameScene::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
}

void MainGameScene::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
    proceedTouches(touches);
}

void MainGameScene::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
}

void MainGameScene::update(const float delta)
{
    mField->update(delta);
}