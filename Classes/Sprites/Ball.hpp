//
//  Ball.hpp
//  BugsKiller
//
//  Created by 张长浩 on 2018/10/11.
//

#ifndef Ball_hpp
#define Ball_hpp

#include <stdio.h>
#include <cocos2d.h>
#include <cocos-ext.h>

class Ball : public cocos2d::extension::PhysicsSprite
{
public:
    static Ball* create();
    ~Ball();
};

#endif /* Ball_hpp */
