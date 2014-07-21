//
//  Field.h
//  SquareWarrior
//
//  Created by Andrey Naboka on 09/06/14.
//
//

#ifndef __SquareWarrior__Field__
#define __SquareWarrior__Field__

#include "cocos2d.h"
#include "Piece.h"
#include <vector>

class Field {
public:
    
    enum MOVE_DIRECTION {
        TOP,
        BOTTOM,
        LEFT,
        RIGHT,
        UNKNOWN
    };
    
    static std::string directionToString(const MOVE_DIRECTION& direction);
    
    Field(cocos2d::Layer *layer);
    void update(const float delta);
    void moveField(const MOVE_DIRECTION direction);
    int getTopPosition() const;
    bool isTapIntoAttackArea(const float x, const float y) const;
    int getDamage() const;
    void sendWarriorsToAttack();
    
private:
    void addRandomWarrior(const int num = 1);
    void moveLeft();
    void moveRight();
    void moveTop();
    void moveBottom();
    void redrawField();
    
    
    struct coord
    {
        int w, h;
        coord(const int width, const int height) : w(width), h(height) {}
    };
    void collectHorizontalPairs(std::vector<std::pair<Field::coord, Field::coord> >& listOfPairs);
    void collectVerticalPairs(std::vector<std::pair<Field::coord, Field::coord> >& listOfPairs);
    void combinePairs(const std::vector<std::pair<Field::coord, Field::coord> >& listOfPairs);
private:
    cocos2d::Layer* mLayer;
    int mPiecesTopPosition;
    static const int FIELD_WIDTH = 4;
    static const int FIELD_HEIGHT = 4;
    Piece::COLORS mField[FIELD_WIDTH][FIELD_HEIGHT];
    cocos2d::Sprite* mFieldMap[FIELD_WIDTH][FIELD_HEIGHT];
    
    float mLeftAttackArea;
    float mRightAttackArea;
    float mTopAttackArea;
    float mBottomAttackArea;
};

typedef std::shared_ptr<Field> FieldPtr;


#endif /* defined(__SquareWarrior__Field__) */
