//
//  BaseBug.hpp
//  BugsKiller-mobile
//
//  Created by 张长浩 on 2018/5/5.
//

#ifndef BaseBug_hpp
#define BaseBug_hpp

#include <stdio.h>

enum BugState
{
    BugStateAlive,
    BugStateDead
};

class BaseBug : public cocos2d::Ref
{
    PointerPropertyBuilderByName(cocos2d::Sprite, BugSprite, private)
    PropertyBuilderByName(float, BugLife, private)
    PropertyBuilderByName(BugState, BugState, private)
    PropertyBuilderByName(float, BugSpeed, private)
    PropertyBuilderByName(float, BugDamage, private)
    PropertyBuilderByName(float, BugToward, private)
    PropertyBuilderByName(cocos2d::Size, BugSize, private);
    
private:
    cocos2d::Vec2 mBugPos;
public:
    void setBugPos(cocos2d::Vec2 pos);
    cocos2d::Vec2 getBugPos();
};

#endif /* BaseBug_hpp */
