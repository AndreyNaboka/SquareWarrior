#include "MainGameScene.h"

USING_NS_CC;

/**********************************************************/
Scene* MainGameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainGameScene::create();
    scene->addChild(layer);
    return scene;
}

/**********************************************************/
bool MainGameScene::init()
{
    mVisibleSize = Director::getInstance()->getVisibleSize();
    mOrigin      = Director::getInstance()->getVisibleOrigin();
    
    mMovingNow = false;
    
    mField.reset(new Field(this));
    
    /// Start update
    srand(static_cast<unsigned int>(time(0)));
    schedule(schedule_selector(MainGameScene::update));
    
    
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan=std::bind(&MainGameScene::onTouchesBegan, this, std::placeholders::_1, std::placeholders::_2);
    listener->onTouchesMoved=std::bind(&MainGameScene::onTouchesMoved, this, std::placeholders::_1, std::placeholders::_2);
    listener->onTouchesEnded=std::bind(&MainGameScene::onTouchesEnded, this, std::placeholders::_1, std::placeholders::_2);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 100);
    
    
    /// Movement direction
    const cocos2d::Vec2 centerOfScreen = cocos2d::Vec2(mOrigin.x + (mVisibleSize.width / 2), mOrigin.y + (mVisibleSize.height / 2));
    
    mUpDirection = cocos2d::Vec2(mOrigin.x + (mVisibleSize.width / 2.0), mOrigin.y + mVisibleSize.height);
    mUpDirection = centerOfScreen - mUpDirection;
    mUpDirection.normalize();
    
    mDownDirection = cocos2d::Vec2(mOrigin.x + (mVisibleSize.width / 2.0), mOrigin.y);
    mDownDirection = centerOfScreen - mDownDirection;
    mDownDirection.normalize();
    
    mLeftDirection = cocos2d::Vec2(mOrigin.x, mOrigin.y + (mVisibleSize.height / 2.0));
    mLeftDirection = centerOfScreen - mLeftDirection;
    mLeftDirection.normalize();
    
    mRightDirection = cocos2d::Vec2(mOrigin.x + mVisibleSize.width, mOrigin.y + (mVisibleSize.height / 2.0));
    mRightDirection = centerOfScreen - mRightDirection;
    mRightDirection.normalize();
    
    
    createGameObjects();
    
    return true;
}


/**********************************************************/
Field::MOVE_DIRECTION MainGameScene::proceedTouches(const std::vector<cocos2d::Touch *> &touches)
{
    mTouches.push_back((*touches.begin())->getLocation());
    if (mTouches.size() >= 2)
    {
        if (mTouches.at(0).distance(mTouches.at(1)) < 10.0f)
        {
            mTouches.clear();
            return Field::MOVE_DIRECTION::UNKNOWN;
        }

        
        
        cocos2d::Vec2 touch = mTouches.at(1);// (*touches.begin())->getLocation();
        cocos2d::Vec2 touchToPrevTouch = mTouches.at(0) - touch;
        touchToPrevTouch.normalize();
        
        float angleBetweenUp    = acos(cocos2d::Vec2::dot(mUpDirection,    touchToPrevTouch));
        float angleBetweenDown  = acos(cocos2d::Vec2::dot(mDownDirection,  touchToPrevTouch));
        float angleBetweenLeft  = acos(cocos2d::Vec2::dot(mLeftDirection,  touchToPrevTouch));
        float angleBetweenRight = acos(cocos2d::Vec2::dot(mRightDirection, touchToPrevTouch));

        Field::MOVE_DIRECTION direction;

        
        if (angleBetweenDown < angleBetweenUp &&
            angleBetweenDown < angleBetweenLeft &&
            angleBetweenDown < angleBetweenRight)
            direction = Field::MOVE_DIRECTION::BOTTOM;
        
        else if (angleBetweenUp < angleBetweenDown &&
                 angleBetweenUp < angleBetweenLeft &&
                 angleBetweenUp < angleBetweenRight)
            direction = Field::MOVE_DIRECTION::TOP;
        
        else if (angleBetweenLeft < angleBetweenDown &&
                 angleBetweenLeft < angleBetweenRight &&
                 angleBetweenLeft < angleBetweenUp)
            direction = Field::MOVE_DIRECTION::LEFT;
        
        else if (angleBetweenRight < angleBetweenDown &&
                 angleBetweenRight < angleBetweenLeft &&
                 angleBetweenRight < angleBetweenUp)
            direction = Field::MOVE_DIRECTION::RIGHT;
        
        
        mMovingNow = true;
        mTouches.clear();
        return direction;
    }
    return Field::MOVE_DIRECTION::UNKNOWN;
}

/**********************************************************/
void MainGameScene::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
}

/**********************************************************/
void MainGameScene::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
    if (mMovingNow) return;
    
    Field::MOVE_DIRECTION direction = proceedTouches(touches);
    if (direction != Field::UNKNOWN)
        mField->moveField(direction);
}

/**********************************************************/
void MainGameScene::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
    mMovingNow = false;
}

/**********************************************************/
void MainGameScene::update(const float delta)
{
}


void MainGameScene::createGameObjects()
{
    // Enemy prepare
    cocos2d::Sprite* enemy = cocos2d::Sprite::create("boss.png");
    enemy->setScale(((mVisibleSize.width + 2) / enemy->getContentSize().width),
                    (mVisibleSize.height * 0.2) / enemy->getContentSize().height);
    enemy->setPosition((mVisibleSize.width / 2) + (enemy->getContentSize().width / 2),
                       (mField->getTopPosition()) + (enemy->getContentSize().height / 2 * enemy->getScaleY()));
    addChild(enemy);
    
    
    // Create score label
    char scoreText[256];
    snprintf(scoreText, 256, "2048");
    mScoreLabel = cocos2d::Label::createWithSystemFont(std::string(scoreText),
                                                       "",
                                                       50);
    mScoreLabel->setColor(cocos2d::Color3B(255,255,255));
    mScoreLabel->setPosition(mVisibleSize.width / 2,
                             enemy->getPositionY());
    addChild(mScoreLabel);
    
    
}