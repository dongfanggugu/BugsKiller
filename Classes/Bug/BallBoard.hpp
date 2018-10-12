//
//  BallBoard.hpp
//  BugsKiller
//
//  Created by 张长浩 on 2018/10/10.
//

#ifndef BallBoard_hpp
#define BallBoard_hpp

#include <stdio.h>
#include <cocos2d.h>
#include <cocos-ext.h>
#include "Box2D/Box2D.h"
#include "Constant.h"

class BallBoard : public cocos2d::extension::PhysicsSprite
{
public:
    static BallBoard* create(b2World *world, float ptm, float width, float height);
    
private:
    //property
    PointerPropertyBuilderByName(b2World, world, private);
    PropertyBuilderByName(float, width, private);
    PropertyBuilderByName(float, height, private);
    //method
    void addB2Body();
    ~BallBoard();
};

#endif /* BallBoard_hpp */
