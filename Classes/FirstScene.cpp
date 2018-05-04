//
//  FirstScene.cpp
//  TestGame-mobile
//
//  Created by 张长浩 on 2018/4/23.
//

#include "FirstScene.h"
#include "BackgroundLayer.h"
#include "MosquitomLayer.hpp"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

#define winSize Director::getInstance()->getWinSize()
#define ArrowInitY 40

Scene* FirstScene::createScene()
{
    return FirstScene::create();
}

bool FirstScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    this->scheduleUpdate();
    this->addBackgroundLayer();
    this->addCloseBtn();
    this->addSprite();
    this->addRightBtn();
    this->addFireBtn();
    this->addBugsLayer();
    this->addLeftOperationLayer();
    return true;
}

void FirstScene::addBugsLayer()
{
    auto layer = MosquitomLayer::create();
    layer->setPosition(Vec2(100, 0));
    this->addChild(layer);
//    this->mosSprite = layer->sprite;
    this->bugsLayer = layer;
}

void FirstScene::addRightBtn()
{
    auto btn = this->genBtn("right ->", "res/button.png", CC_CALLBACK_1(FirstScene::moveRight, this));
    btn->setContentSize(Size(80, 30));
    btn->setPosition(Vec2(winSize.width - 40 - 8, winSize.height - 15 - 50));
    this->addChild(btn);
}

void FirstScene::moveRight(Ref *sender)
{
    MoveBy * moveBy;
    moveBy = MoveBy::create(0.2, Vec2(5, 0));
    this->sprite->runAction(moveBy);
}

void FirstScene::addFireBtn()
{
    auto btn = this->genBtn("FIRE", "res/button_fire.png", CC_CALLBACK_1(FirstScene::fireArrow, this));
    btn->setContentSize(Size(30, 30));
    btn->setPosition(Vec2(winSize.width - 100, winSize.height / 2));
    this->addChild(btn);
}

void FirstScene::fireArrow(Ref *sender)
{
    auto pos = this->sprite->getPosition();
    auto size = this->sprite->getContentSize();
    auto moveTo = MoveTo::create(0.5, Vec2(pos.x, winSize.height + size.height));
    this->sprite->runAction(moveTo);
}

void FirstScene::update(float delta)
{
    this->checkCollison();
    auto pos = this->sprite->getPosition();
    auto size = this->sprite->getContentSize();
    if ((pos.y + size.height) > winSize.height)
    {
        this->sprite->stopAllActions();
        this->sprite->setPosition(Vec2(pos.x, 40));
    }
}

Button* FirstScene::genBtn(const std::string &title,
                                        const std::string &icon,
                                        const cocos2d::ui::Button::ccWidgetClickCallback &callback)
{
    auto btn = cocos2d::ui::Button::create();
    if (title.length() > 0)
    {
        btn->setTitleText(title);
    }
    if (icon.length() > 0)
    {
        btn->loadTextureNormal(icon);
    }
    btn->addClickEventListener(callback);
    return btn;
}

void close(Ref *sender)
{
    auto director = Director::getInstance();
    director->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void FirstScene::addCloseBtn()
{
    auto btn = this->genBtn("", "CloseNormal.png", &close);
    btn->setContentSize(Size(30, 30));
    btn->setPosition(Vec2(winSize.width - 15, winSize.height - 15));
    this->addChild(btn);
}

void FirstScene::addSprite()
{
    this->sprite = Sprite::create();
    this->sprite->setTexture("res/arrow.png");
    this->sprite->setContentSize(Size(15, 80));
    auto size = this->sprite->getContentSize();
    //this->sprite
    this->sprite->setPosition(Vec2(winSize.width / 2, 40));
    this->addChild(this->sprite);

//    auto animation = Animation::create();
//
//    for (int i = 1; i <= 15; i++)
//    {
//        std::string name = StringUtils::format("res/run/run%d.png", i);
//        animation->addSpriteFrameWithFile(name);
//    }
//    animation->setDelayPerUnit(0.05);
//    animation->setLoops(-1);
//    auto animate = Animate::create(animation);
//    sprite->runAction(animate);
}

void FirstScene::addBackgroundLayer()
{
    auto layer = BackgroundLayer::create();
    layer->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    this->addChild(layer);
}

void FirstScene::loadPackageImage()
{
    SpriteFrameCache *frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("res/run/boys.plist", "res/run/boys.png");
    int iFrameNum = 15;
    SpriteFrame *frame = NULL;
    Vector<SpriteFrame *> frameVec;
    for (int i = 1; i <= iFrameNum; i++)
    {
        frame = frameCache->getSpriteFrameByName(StringUtils::format("run%d.png", i));
        frameVec.pushBack(frame);
    }
    auto animation = Animation::createWithSpriteFrames(frameVec);
    animation->setLoops(-1);
    animation->setDelayPerUnit(0.1f);
    auto action = Animate::create(animation);
    action->setTag(1001);
    this->sprite->runAction(action);
}

void FirstScene::move1(Ref *sender)
{
//    auto moveBy = MoveBy::create(8, Vec2(980, 0));
    auto moveTo = MoveTo::create(8, Vec2(500, 0));
//    auto ac = moveBy->reverse();
    this->sprite->runAction(moveTo);
}

void FirstScene::checkCollison()
{
    auto rect = this->bugsLayer->getBugBoundBoxing();
    auto pos = this->bugsLayer->getPosition();
    auto newRect = Rect(rect.getMinX() + pos.x, rect.getMinY() + pos.y, rect.size.width, rect.size.height);
    auto arrowRect = this->sprite->getBoundingBox();
    if (arrowRect.intersectsRect(newRect))
    {
        this->bugsLayer->bugDie();
    }
}

void FirstScene::addLeftOperationLayer()
{
    auto layer = LeftSideOperationLayer::create();
    layer->moveProtocol = this;
    this->addChild(layer);
}

FirstScene::~FirstScene()
{
    log("dealloc");
}

void FirstScene::onMove(float length)
{
    auto pos = this->sprite->getPosition();
    if (pos.y != ArrowInitY)
    {
        return;
    }
    this->sprite->setPosition(200 + length, pos.y);
}
