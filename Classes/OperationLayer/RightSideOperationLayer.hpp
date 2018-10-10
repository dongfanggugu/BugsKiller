//
//  RightSideOperationLayer.hpp
//  BugsKiller
//
//  Created by 张长浩 on 2018/10/10.
//

#ifndef RightSideOperationLayer_hpp
#define RightSideOperationLayer_hpp

#include <stdio.h>

class RightSideOpProtocol
{
public:
    virtual void onMove(float delta) = 0;
};

class RightSideOperationLayer : public cocos2d::LayerColor
{
public:
    bool init();
    CREATE_FUNC(RightSideOperationLayer);
    RightSideOpProtocol *moveProtocol;
    
private:
    void addTouchListener();
    cocos2d::Vec2 startPoint;
};

#endif /* RightSideOperationLayer_hpp */
