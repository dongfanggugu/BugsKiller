//
//  RightSideOperationLayer.hpp
//  BugsKiller
//
//  Created by 张长浩 on 2018/10/10.
//

#ifndef RightSideOperationLayer_hpp
#define RightSideOperationLayer_hpp

#include <stdio.h>
#include <cocos2d.h>
#include "../Constant.h"

class RightSideOpProtocol
{
public:
    virtual void onMove(float delta, unsigned tag) = 0;
    virtual void onTouch(unsigned tag) {};
};

class RightSideOperationLayer : public cocos2d::LayerColor
{
public:
    bool init(float width, float height);
    static RightSideOperationLayer* create(float width, float height);

private:
    void addBackground(float width, float height);
    void addTouchListener();
    void addKeyboardListener();
    cocos2d::Vec2 startPoint;
    PropertyBuilderByName(unsigned int, tag, private);
    PointerPropertyBuilderByName(RightSideOpProtocol, moveProtocol, private);
    ~RightSideOperationLayer();
};

#endif /* RightSideOperationLayer_hpp */
