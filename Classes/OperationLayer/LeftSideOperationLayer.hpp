//
//  LeftSideOperationLayer.hpp
//  TestGame
//
//  Created by 张长浩 on 2018/4/27.
//

#ifndef LeftSideOperationLayer_hpp
#define LeftSideOperationLayer_hpp

#include <stdio.h>
#include "cocos2d.h"

class LeftSideMoveProtocol
{
public:
    virtual void onMove(float length) = 0;
};

class LeftSideOperationLayer : public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(LeftSideOperationLayer);
    LeftSideMoveProtocol *moveProtocol;
    virtual ~LeftSideOperationLayer();
    
private:
    void addTouchListener();
    cocos2d::Vec2 startPoint;
};

#endif /* LeftSideOperationLayer_hpp */
