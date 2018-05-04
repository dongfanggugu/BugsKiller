//
//  BaseBullet.hpp
//  TestGame
//
//  Created by 张长浩 on 2018/5/4.
//

#ifndef BaseBullet_hpp
#define BaseBullet_hpp

#include <stdio.h>
#include "cocos2d.h"

class BaseBullet : public cocos2d::Ref
{

private:
    cocos2d::Sprite *sprite;
    float damage;
    float speed;

};

#endif /* BaseBullet_hpp */
