//
//  Field.cpp
//  SquareWarrior
//
//  Created by Andrey Naboka on 09/06/14.
//
//

#include "Field.h"
#include <iostream>

/**********************************************************/
Field::Field(cocos2d::Layer* layer)
    :mLayer(layer)
{
    // Field background
    cocos2d::Sprite* background = cocos2d::Sprite::create("background.png");
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    const float backgroundWidthScale = visibleSize.width / background->getContentSize().width;
    const float backgroundHeightScale = visibleSize.height / background->getContentSize().height;
    background->setScale(backgroundWidthScale, backgroundHeightScale);
    cocos2d::Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    background->setPosition(origin.x + (visibleSize.width/2), origin.y + (visibleSize.height/2));
    mLayer->addChild(background);
    
    // Pieces prepare
    const float cellWidth = visibleSize.width / 4;
    const float cellHeight = cellWidth;
    const float topStartPosY = cellHeight * 4;
    mPiecesTopPosition = topStartPosY;
    
    for (int w = 0; w < FIELD_WIDTH; ++w)
    {
        for (int h = 0; h < FIELD_HEIGHT; ++h)
        {
            mField[w][h] = Piece::COLORS::BLACK;
            
            mFieldMap[w][h] = cocos2d::Sprite::create(Piece::colorToSpriteName(Piece::COLORS::BLACK));
            const float cellSpriteWidth = 64;//mFieldMap[w][h]->getContentSize().width;
            const float cellSpriteHeight = 64;//mFieldMap[w][h]->getContentSize().height;

            mFieldMap[w][h]->setScale(cellWidth / cellSpriteWidth, cellHeight / cellSpriteHeight);
            mFieldMap[w][h]->setPosition(cellWidth * w + (cellWidth/2), topStartPosY - (cellHeight * h) - (cellHeight/2));
            mLayer->addChild(mFieldMap[w][h]);
        }
    }
    
    addRandomWarrior();
    
    redrawField();
}

/**********************************************************/
void Field::update(const float delta)
{
    
}

/**********************************************************/
void Field::moveField(const Field::MOVE_DIRECTION direction)
{
    switch (direction)
    {
        case LEFT:
            moveLeft();
            break;
        case RIGHT:
            moveRight();
            break;
        case TOP:
            moveTop();
            break;
        case BOTTOM:
            moveBottom();
            break;
        default:
            return;
    }
    addRandomWarrior();
    redrawField();
}

/**********************************************************/
void Field::redrawField()
{
    for (int w = 0; w < FIELD_WIDTH; ++w)
    {
        for (int h = 0; h < FIELD_HEIGHT; ++h)
        {
            const std::string newTextureFilename = Piece::colorToSpriteName(mField[w][h]);
            if (newTextureFilename != "unknown")
                mFieldMap[w][h]->setTexture(newTextureFilename);
        }
    }
}

/**********************************************************/
void Field::moveLeft()
{
    std::vector<std::pair<Field::coord, Field::coord> > listOfPairs;
    
    collectHorizontalPairs(listOfPairs);
    
    combinePairs(listOfPairs);

    
    // Move all pieces to left
    for (int h = 0; h < FIELD_HEIGHT; ++h)
    {
        std::vector<Piece::COLORS> pieces;
        for (int w = 0; w < FIELD_WIDTH; ++w)
        {
            if (mField[w][h] != Piece::COLORS::BLACK)
            {
                pieces.push_back(mField[w][h]);
                mField[w][h] = Piece::COLORS::BLACK;
            }
        }
        
        if (pieces.size())
        {
            for (auto piece = pieces.begin(); piece != pieces.end(); ++piece)
            {
                const long index = std::distance(pieces.begin(), piece);
                mField[index][h] = *piece;
            }
        }
    }
}

/**********************************************************/
void Field::moveRight()
{
    std::vector<std::pair<Field::coord, Field::coord> > listOfPairs;
   
    collectHorizontalPairs(listOfPairs);
    
    combinePairs(listOfPairs);
    
    
    // Move right
    for (int h = 0; h < FIELD_HEIGHT; ++h)
    {
        std::vector<Piece::COLORS> pieces;
        for (int w = 0; w < FIELD_WIDTH; ++w)
        {
            if (mField[w][h] != Piece::COLORS::BLACK)
            {
                pieces.push_back(mField[w][h]);
                mField[w][h] = Piece::COLORS::BLACK;
            }
        }
        
        if (pieces.size())
        {
            for (auto piece = pieces.rbegin(); piece != pieces.rend(); ++piece)
            {
                const long index = FIELD_WIDTH - std::distance(pieces.rbegin(), piece) - 1;
                mField[index][h] = *piece;
            }
        }
    }
}

/**********************************************************/
void Field::moveTop()
{
    std::vector<std::pair<Field::coord, Field::coord> > listOfPairs;
    
    collectVerticalPairs(listOfPairs);
    
    combinePairs(listOfPairs);
    
    
    // Move top
    for (int w = 0; w < FIELD_WIDTH; ++w)
    {
        std::vector<Piece::COLORS> pieces;
        for (int h = 0; h < FIELD_HEIGHT; ++h)
        {
            if (mField[w][h] != Piece::COLORS::BLACK)
            {
                pieces.push_back(mField[w][h]);
                mField[w][h] = Piece::COLORS::BLACK;
            }
        }
        
        if (pieces.size())
        {
            int index = 0;
            for (auto piece = pieces.begin(); piece != pieces.end(); ++piece, index++)
            {
                mField[w][index] = *piece;
            }
        }
    }
}

/**********************************************************/
void Field::moveBottom()
{
    std::vector<std::pair<Field::coord, Field::coord> > listOfPairs;
    
    collectVerticalPairs(listOfPairs);
    
    combinePairs(listOfPairs);
    
    
    // Move bottom
    for (int w = 0; w < FIELD_WIDTH; ++w)
    {
        std::vector<Piece::COLORS> pieces;
        for (int h = 0; h < FIELD_HEIGHT; ++h)
        {
            if (mField[w][h] != Piece::COLORS::BLACK)
            {
                pieces.push_back(mField[w][h]);
                mField[w][h] = Piece::COLORS::BLACK;
            }
        }
        
        if (pieces.size())
        {
            for (auto piece = pieces.rbegin(); piece != pieces.rend(); ++piece)
            {
                const long index = FIELD_HEIGHT - std::distance(pieces.rbegin(), piece) - 1;
                mField[w][index] = *piece;
            }
        }
    }
}

/**********************************************************/
void Field::addRandomWarrior(const int num)
{
    std::vector<cocos2d::Vec2> freePieces;
    for (int w = 0; w < FIELD_WIDTH; ++w)
    {
        for (int h = 0; h < FIELD_HEIGHT; ++h)
        {
            if (mField[w][h] == Piece::COLORS::BLACK)
                freePieces.push_back(cocos2d::Vec2(w,h));
        }
    }
    
    if (freePieces.size() == 0)
    {
        std::cout << "GAME OVER" << std::endl;
        return;
    }
    
    
    
    int randomIndex = rand() % freePieces.size();
    const int x = freePieces.at(randomIndex).x;
    const int y = freePieces.at(randomIndex).y;
    mField[x][y] = Piece::COLORS::COLOR_2;
    mFieldMap[x][y]->setTexture(Piece::colorToSpriteName(Piece::COLOR_2));
}

/**********************************************************/
std::string Field::directionToString(const Field::MOVE_DIRECTION &direction)
{
    switch (direction)
    {
        case TOP:
            return "TOP";
            break;
        case LEFT:
            return "LEFT";
            break;
        case BOTTOM:
            return "BOTTOM";
            break;
        case RIGHT:
            return "RIGHT";
            break;
        default:
            return "UNKNOWN";
            break;
    }
}

/**********************************************************/
void Field::collectVerticalPairs(std::vector<std::pair<Field::coord, Field::coord> > &listOfPairs)
{
    for (int w = 0; w < FIELD_WIDTH; ++w)
    {
        for (int h = 0; h < FIELD_HEIGHT; ++h)
        {
            if (mField[w][h] != Piece::COLORS::BLACK)
            {
                for (int relativeH = h+1; relativeH < FIELD_HEIGHT; ++relativeH)
                {
                    // Can't make pair, cause nearest piece have anonther number
                    if (mField[w][relativeH] != mField[w][h] &&
                        mField[w][relativeH] != Piece::COLORS::COLOR_2048 &&
                        mField[w][relativeH] != Piece::COLORS::BLACK)
                    {
                        break;
                    }
                    
                    // Nearest pieces is eqaul - make pair
                    if (mField[w][relativeH] == mField[w][h] &&
                        mField[w][relativeH] != Piece::COLORS::COLOR_2048)
                    {
                        Field::coord c1(w, relativeH);
                        Field::coord c2(w, h);
                        listOfPairs.push_back(std::make_pair(c1, c2));
                        h = relativeH;
                        break;
                    }
                }
            }
        }
    }
}


/**********************************************************/
void Field::collectHorizontalPairs(std::vector<std::pair<Field::coord, Field::coord> >& listOfPairs)
{
    for (int h = 0; h < FIELD_HEIGHT; ++h)
    {
        for (int w = 0; w < FIELD_WIDTH; ++w)
        {
            if (mField[w][h] != Piece::COLORS::BLACK)
            {
                for (int relativeW = w+1; relativeW < FIELD_WIDTH; ++relativeW)
                {
                    if (mField[relativeW][h] != mField[w][h] &&
                        mField[relativeW][h] != Piece::COLORS::COLOR_2048 &&
                        mField[relativeW][h] != Piece::COLORS::BLACK)
                    {
                        break;
                    }
                    
                    if (mField[relativeW][h] == mField[w][h] &&
                        mField[relativeW][h] != Piece::COLORS::COLOR_2048)
                    {
                        Field::coord c1(relativeW, h);
                        Field::coord c2(w, h);
                        listOfPairs.push_back(std::make_pair(c1, c2));
                        w = relativeW;
                        break;
                    }
                }
         
            }
        }
    }
}

/**********************************************************/
void Field::combinePairs(const std::vector<std::pair<Field::coord, Field::coord> > &listOfPairs)
{
    if (listOfPairs.size())
    {
        for (auto pair = listOfPairs.begin(); pair != listOfPairs.end(); ++pair)
        {
            mField[pair->second.w][pair->second.h] = Piece::getNextColor(mField[pair->second.w][pair->second.h]);
            mField[pair->first.w][pair->first.h] = Piece::COLORS::BLACK;
        }
    }
}

/**********************************************************/
int Field::getTopPosition() const
{
    return mPiecesTopPosition;
}





