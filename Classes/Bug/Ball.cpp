//
//  Ball.cpp
//  BugsKiller
//
//  Created by 张长浩 on 2018/10/11.
//

#include "Ball.hpp"
USING_NS_CC;
using namespace std;

Ball* Ball::create()
{
    Ball *ball = new Ball();
    if (ball && ball->initWithFile("res/ball.png"));
    {
        ball->autorelease();
        return ball;
    }
    
    CC_SAFE_DELETE(ball);
    return nullptr;
}
