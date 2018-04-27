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
    virtual ~BackgroundLayer();
   
     static int currentBgImageIndex;
     void addBackground();
     static int rollTime;
     void startRollbg();
     void stop();

     bool isFastRoll = false;
};

#endif // BackgroundLayer_h
