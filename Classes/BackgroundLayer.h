#ifndef BackgroundLayer_h
#define BackgroundLayer_h

#include <stdio.h>
#include "cocos2d.h"

#pragma once
class BackgroundLayer : public cocos2d::Layer
{
public:
    
    static BackgroundLayer* create(const std::string &filename, float width, float height);
    
private:
    
    bool init(const std::string &filename, float width, float height);
    //property
    static int currentBgImageIndex;
    bool isFastRoll = false;
    static int rollTime;
    //method
    
    void addBackground(const std::string &filename);
    void startRollbg();
    void stop();
    
};

#endif // BackgroundLayer_h
