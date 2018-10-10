//
//  RightSideOperationLayer.cpp
//  BugsKiller
//
//  Created by 张长浩 on 2018/10/10.
//

#include "RightSideOperationLayer.hpp"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

bool RightSideOperationLayer::init()
{
    if (!LayerColor::initWithColor(Color4B::RED))
    {
        return false;
    }
    startPoint = Point::ZERO;
    addTouchListener();
    return true;
}

void RightSideOperationLayer::addTouchListener()
{
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = [&](Touch *touch, Event *event) {
        auto pos = touch->getLocation();
        auto target = static_cast<RightSideOperationLayer *>(event->getCurrentTarget());
        log("%s", typeid(target).name());
        if (target->getBoundingBox().containsPoint(pos))
        {
            startPoint = pos;
        }
        return true;
    };
    
    touchListener->onTouchMoved = [&](Touch *touch, Event *event) {
        auto pos = touch->getLocation();
        auto target = static_cast<RightSideOperationLayer *>(event->getCurrentTarget());
        if (!target->getBoundingBox().containsPoint(pos))
        {
            startPoint = Point::ZERO;
            return true;
        }
        if (!moveProtocol)
        {
            return true;
        }
        if (startPoint.isZero())
        {
            startPoint = pos;
        }
        else
        {
            float deltaY = pos.y - startPoint.y;
            moveProtocol->onMove(deltaY);
            startPoint = pos;
        }
        return true;
    };
    
    touchListener->onTouchEnded = [&](Touch *touch, Event *event) {
        startPoint = Point::ZERO;
        return true;
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}
