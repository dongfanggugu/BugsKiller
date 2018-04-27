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

class LeftSideOperationLayer : public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(LeftSideOperationLayer);
    
private:
    void addTouchListener();
};

#endif /* LeftSideOperationLayer_hpp */
