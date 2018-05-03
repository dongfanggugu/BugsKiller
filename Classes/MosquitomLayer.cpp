//
//  MosquitomLayer.cpp
//  TestGame
//
//  Created by 张长浩 on 2018/4/26.
//

#include "MosquitomLayer.hpp"
USING_NS_CC;
using namespace std;
#define winSize Director::getInstance()->getWinSize()
#define SPEED 1024 / 5


bool MosquitomLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    this->setContentSize(Size(winSize.width - 200, winSize.height));
    scheduleUpdate();
    addSprite();
    return true;
}


void MosquitomLayer::addSprite()
{
    auto size = getContentSize();
    sprite = Sprite::create("res/mosquitom.png");
    sprite->setContentSize(Size(40, 40));
    sprite->setPosition(Vec2(-20, winSize.height - 40));
    this->towards = Right;
    sprite->retain();
    addChild(sprite);
}

void MosquitomLayer::update(float delta)
{
    auto sizeThis = this->getContentSize();
    auto pos = this->sprite->getPosition();
    auto size = this->sprite->getContentSize();
    if (Right == this->towards)
    {
        this->sprite->setPosition(Vec2(pos.x + SPEED * delta, pos.y));
    }
    else
    {
        this->sprite->setPosition(Vec2(pos.x - SPEED * delta, pos.y));
    }
    

    if (pos.x > sizeThis.width + size.width / 2)
    {
        this->sprite->setScale(-1, 1);
        this->towards = Left;
    }
    
    if (pos.x < -size.width / 2)
    {
        this->sprite->setScale(1, 1);
        this->towards = Right;
    }
    
}

Rect MosquitomLayer::getBugBoundBoxing()
{
    return this->sprite->getBoundingBox();
}

void MosquitomLayer::bugDie()
{
    this->sprite->setTexture("res/bang.png");
    sprite->setContentSize(Size(40, 40));
    
    scheduleOnce(schedule_selector(MosquitomLayer::dismissBug), 0.4f);
    scheduleOnce(schedule_selector(MosquitomLayer::resetBug), 1.0f);
}

void MosquitomLayer::dismissBug(float delta)
{
    this->sprite->removeFromParent();
}

void MosquitomLayer::resetBug(float delta)
{
    this->sprite->setTexture("res/mosquitom.png");
    sprite->setContentSize(Size(40, 40));
    sprite->setPosition(Vec2(-20, winSize.height - 40));
    this->towards = Right;
    this->addChild(this->sprite);
}


