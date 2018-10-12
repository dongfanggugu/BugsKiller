//
//  Brick.hpp
//  BugsKiller
//
//  Created by 张长浩 on 2018/10/11.
//

#ifndef Brick_hpp
#define Brick_hpp

#include <stdio.h>
#include <cocos2d.h>
#include "cocos-ext.h"


class Brick : public cocos2d::extension::PhysicsSprite
{
public:
    static Brick* create();
    
private:
    ~Brick();
};

#endif /* Brick_hpp */
