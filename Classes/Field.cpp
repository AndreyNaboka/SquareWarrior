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
    
    

    
    for (int w = 0; w < FIELD_WIDTH; ++w)
    {
        for (int h = 0; h < FIELD_HEIGHT; ++h)
        {
            mField[w][h] = Piece::COLORS::BLACK;
            
            mFieldMap[w][h] = cocos2d::Sprite::create(Piece::colorToSpriteName(Piece::COLORS::BLACK));
            const float cellSpriteWidth = mFieldMap[w][h]->getContentSize().width;
            const float cellSpriteHeight = mFieldMap[w][h]->getContentSize().height;

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
            mFieldMap[w][h]->setTexture(Piece::colorToSpriteName(mField[w][h]));
        }
    }
}

/**********************************************************/
void Field::moveLeft()
{
    std::vector<std::pair<Field::coord, Field::coord> > listOfPairs;
    collectHorizontalPairs(listOfPairs);
    
    combineHorizontalPairs(listOfPairs);

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
                const int index = std::distance(pieces.begin(), piece);
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
    
    combineHorizontalPairs(listOfPairs);
    
    
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
                const int index = FIELD_WIDTH - std::distance(pieces.rbegin(), piece) - 1;
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
    
    combineVerticalPairs(listOfPairs);
    
    
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
    
    combineVerticalPairs(listOfPairs);
    
    
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
            int index = 0;
            for (auto piece = pieces.rbegin(); piece != pieces.rend(); ++piece, index++)
            {
                mField[w][FIELD_WIDTH - 1 - index] = *piece;
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
        return;
    
    
    int randomIndex = rand() % freePieces.size();
    const int x = freePieces.at(randomIndex).x;
    const int y = freePieces.at(randomIndex).y;
    mField[x][y] = Piece::COLORS::WHITE;
    mFieldMap[x][y]->setTexture(Piece::colorToSpriteName(Piece::WHITE));
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
                    if (mField[w][relativeH] == mField[w][h])
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
                    if (mField[relativeW][h] == mField[w][h])
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
void Field::combineHorizontalPairs(const std::vector<std::pair<Field::coord, Field::coord> > &listOfPairs)
{
    if (listOfPairs.size())
    {
        // Adding pairs
        for (auto pair = listOfPairs.begin(); pair != listOfPairs.end(); ++pair)
        {
            mField[pair->second.w][pair->second.h] = Piece::getNextColor(mField[pair->second.w][pair->second.h]);
            mField[pair->first.w][pair->first.h] = Piece::COLORS::BLACK;
        }
    }
}

/**********************************************************/
void Field::combineVerticalPairs(const std::vector<std::pair<Field::coord, Field::coord> > &listOfPairs)
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







