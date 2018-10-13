//
//  LeftSideOperationLayer.cpp
//  TestGame
//
//  Created by 张长浩 on 2018/4/27.
//

#include "LeftSideOperationLayer.hpp"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

bool LeftSideOperationLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    this->addTouchListener();
    return true;
}

void LeftSideOperationLayer::addTouchListener()
{
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [&](Touch *touch, Event *event)
    {
        auto pos = touch->getLocation();
        auto target = static_cast<LeftSideOperationLayer *>(event->getCurrentTarget());
        if (!moveProtocol)
        {
            startPoint = Point::ZERO;
            return true;
        }
        if (!target->getBoundingBox().containsPoint(pos))
        {
            startPoint = Point::ZERO;
            return true;
        }
        startPoint = pos;
        return true;
    };

    touchListener->onTouchMoved = [&](Touch *touch, Event *event)
    {
        auto pos = touch->getLocation();
        auto target = static_cast<LeftSideOperationLayer *>(event->getCurrentTarget());
        if (!moveProtocol)
        {
            return true;
        }
        
        if (!target->getBoundingBox().containsPoint(pos))
        {
            startPoint = Point::ZERO;
            return true;
        }
        if (startPoint.equals(Point::ZERO))
        {
            startPoint = pos;
        }
        else
        {
            float delta = pos.x - startPoint.x;
            moveProtocol->onMove(delta);
            startPoint = pos;
        }
        return true;
    };

    touchListener->onTouchEnded = [&](Touch *touch, Event *event)
    {
        startPoint = Point::ZERO;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

LeftSideOperationLayer::~LeftSideOperationLayer()
{
}
