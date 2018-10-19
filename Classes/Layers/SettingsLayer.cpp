//
//  SettingsLayer.cpp
//  BugsKiller
//
//  Created by 张长浩 on 2018/10/13.
//

#include "SettingsLayer.hpp"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

bool SettingsLayer::init()
{
    if (!LayerColor::initWithColor(Color4B::BLUE))
    {
        return false;
    }
    
    return true;
}

