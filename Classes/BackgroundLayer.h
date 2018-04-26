#ifndef BackgroundLayer_h
#define BackgroundLayer_h

#include <stdio.h>
#include "cocos2d.h"

#pragma once
class BackgroundLayer : public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(BackgroundLayer);
   
     static int currentBgImageIndex;
     cocos2d::ui::Scale9Sprite* createBackground(cocos2d::Vec2 pos);
     static int rollTime;
     void startRollbg();
     void stop();

     bool isFastRoll = false;
};

#endif // BackgroundLayer_h
