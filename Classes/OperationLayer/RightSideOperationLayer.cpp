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

RightSideOperationLayer* RightSideOperationLayer::create(float width, float height)
{
    RightSideOperationLayer *layer = new RightSideOperationLayer();
    if (layer && layer->init(width, height))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

bool RightSideOperationLayer::init(float width, float height)
{
    if (!LayerColor::initWithColor(Color4B::RED))
    {
        return false;
    }
    setContentSize(Size(width, height));
    startPoint = Point::ZERO;
    addBackground(width, height);
    addTouchListener();
    return true;
}

void RightSideOperationLayer::addBackground(float width, float height)
{
    auto sp = Sprite::create("res/op_roll.png");
    sp->setStretchEnabled(true);
    sp->setContentSize(Size(width, height));
    sp->setPosition(width / 2, height / 2);
    addChild(sp);
}

void RightSideOperationLayer::addTouchListener()
{
    auto touchListener = EventListenerTouchOneByOne::create();
//    touchListener->setSwallowTouches(true);
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
            moveProtocol->onMove(deltaY, gettag());
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
