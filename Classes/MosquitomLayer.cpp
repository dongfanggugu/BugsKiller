//
//  MosquitomLayer.cpp
//  TestGame
//
//  Created by 张长浩 on 2018/4/26.
//

#include "MosquitomLayer.hpp"
USING_NS_CC;
#define winSize Director::getInstance()->getWinSize()
#define SPEED 1024 / 5


bool MosquitomLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    scheduleUpdate();
    addSprite();
    return true;
}

void MosquitomLayer::addSprite()
{
    sprite = Sprite::create("res/mosquitom.png");
    sprite->setContentSize(Size(40, 40));
    sprite->setPosition(Vec2(-20, winSize.height - 40));
    this->towards = Right;
    addChild(sprite);
}

void MosquitomLayer::update(float delta)
{
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
    
    if (pos.x > winSize.width + size.width / 2)
    {
        this->sprite->setScale(-1, 1);
        this->towards = Left;
    }
    
    if (pos.x < -size.width / 2)
    {
        this->sprite->setScale(-1, 1);
        this->towards = Right;
    }
}


