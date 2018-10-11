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

class BallBoard : public cocos2d::extension::PhysicsSprite
{
public:
    static BallBoard* create(b2World *world);
};

#endif /* BallBoard_hpp */
