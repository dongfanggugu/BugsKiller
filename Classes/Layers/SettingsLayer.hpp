//
//  SettingsLayer.hpp
//  BugsKiller
//
//  Created by 张长浩 on 2018/10/13.
//

#ifndef SettingsLayer_hpp
#define SettingsLayer_hpp

#include <stdio.h>
#include <cocos2d.h>
#include <cocos-ext.h>

class SettingsLayer : public cocos2d::LayerColor
{
public:
    bool init();
    CREATE_FUNC(SettingsLayer);
};

#endif /* SettingsLayer_hpp */
