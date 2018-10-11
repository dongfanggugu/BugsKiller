//
//  Brick.cpp
//  BugsKiller
//
//  Created by 张长浩 on 2018/10/11.
//

#include "Brick.hpp"
USING_NS_CC;
using namespace std;

Brick* Brick::create()
{
    Brick *brick = new Brick();
    if (brick && brick->initWithFile("res/button.png"))
    {
        brick->autorelease();
        return brick;
    }
    CC_SAFE_DELETE(brick);
    return nullptr;
}
