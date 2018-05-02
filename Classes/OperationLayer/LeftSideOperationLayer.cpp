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

#define winSize Director::getInstance()->getWinSize()

bool LeftSideOperationLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    this->setContentSize(Size(200, winSize.height));
    this->addTouchListener();
    return true;
}

void LeftSideOperationLayer::addTouchListener()
{
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [&](Touch *touch, Event *event)
    {
        auto pos = touch->getLocation();
        this->startPoint = pos;
        log("begin");
        if (this->moveProtocol)
        {
            this->moveProtocol->onMove(pos.y);
        }

        return true;
    };

    touchListener->onTouchMoved = [&](Touch *touch, Event *event)
    {
        auto pos = touch->getLocation();
        if (this->moveProtocol)
        {
            this->moveProtocol->onMove(pos.y);
        }
        log("x: %f, y: %f", pos.x, pos.y);
    };

    touchListener->onTouchEnded = [](Touch *touch, Event *event)
    {
        auto pos = touch->getLocation();
        log("end");
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

LeftSideOperationLayer::~LeftSideOperationLayer()
{
    delete this->moveProtocol;
}
