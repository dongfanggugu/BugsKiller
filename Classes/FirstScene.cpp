//
//  FirstScene.cpp
//  TestGame-mobile
//
//  Created by 张长浩 on 2018/4/23.
//

#include "FirstScene.h"
#include "BackgroundLayer.h"
#include "MosquitomLayer.hpp"
#include "Bug/BallBoard.hpp"
#include "OperationLayer/RightSideOperationLayer.hpp"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

#define winSize Director::getInstance()->getWinSize()
#define ArrowInitY 40
#define SideWidth 100
#define ArrowHeight 80

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
    this->addBackgroundLayer();
    this->addBallBoard();
    this->addOpLayer();
//    this->addBugsLayer();
//    this->scheduleUpdate();
//    this->addCloseBtn();
//    this->addSprite();
//    this->addRightBtn();
//    this->addFireBtn();
//    this->addTouchFireListener();
    return true;
}

void FirstScene::addBallBoard()
{
    auto board = BallBoard::create("res/ballboard.png");
    float width = WinSize.width;
    board->setPosition(Vec2(width / 2, 15));
    this->sprite = board;
    this->addChild(board);
}

void FirstScene::addOpLayer()
{
    auto layer = RightSideOperationLayer::create();
    layer->moveProtocol = this;
    layer->setContentSize(Size(40, 300));
    layer->setPosition(Vec2(WinSize.width - 50, WinSize.height / 2 - 150));
    this->addChild(layer);
}

void FirstScene::addBugsLayer()
{
    auto layer = MosquitomLayer::create();
    layer->setPosition(Vec2::ZERO);
    this->addChild(layer);
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
    auto point = this->arrowTopPoint();
//    auto pos = this->sprite->getPosition();
//    auto size = this->sprite->getContentSize();
//    auto moveTo = MoveTo::create(0.5, Vec2(0, winSize.height + size.height));
//    this->sprite->runAction(moveTo);
}

void FirstScene::update(float delta)
{
    checkCollison();
    auto pos = this->sprite->getPosition();
    auto size = this->sprite->getContentSize();
    if ((pos.y >= winSize.height + size.height / 2) || (pos.x <= -size.width / 2))
    {
        resetArrow();
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
    this->sprite->setPosition(Vec2(winSize.width - SideWidth, -40));
    this->addChild(this->sprite);
}

void FirstScene::addBackgroundLayer()
{
    auto layer = BackgroundLayer::create();
    layer->setPosition(Vec2(winSize.width / 2 , winSize.height / 2));
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
    
    auto arrowPoint = arrowTopPoint();
    if (newRect.containsPoint(arrowTopPoint()))
    {
        this->bugsLayer->bugDie();
        resetArrow();
    }
}

void FirstScene::addLeftOperationLayer()
{
//    auto layer = LeftSideOperationLayer::create();
//    layer->moveProtocol = this;
//    this->addChild(layer);
}

FirstScene::~FirstScene()
{
    log("dealloc");
}

void FirstScene::onMove(float delta)
{
    auto pos = this->sprite->getPosition();
    auto size = this->sprite->getContentSize();
    float x = pos.x + delta;
    x = MIN(x, WinSize.width - size.width / 2);
    x = MAX(x, size.width / 2);
    auto newPos = Vec2(x, pos.y);
    this->sprite->setPosition(newPos);
}

void FirstScene::addTouchFireListener()
{
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [&](Touch *touch, Event *event)
    {
        auto target = static_cast<FirstScene *>(event->getCurrentTarget());
        if (target)
        {
            auto pos = touch->getLocation();
            this->fireToPos(pos);
        }
        
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void FirstScene::fireToPos(Vec2 pos)
{
    auto start = Vec2(winSize.width - SideWidth, 0);
    auto angle = this->calAngle(start, pos);
    this->sprite->setRotation(angle);
    auto fPos = this->calFinal(start, pos);
    auto moveTo = MoveTo::create(1, fPos);
    this->sprite->runAction(moveTo);
}

float FirstScene::calAngle(cocos2d::Vec2 start, cocos2d::Vec2 end)
{
    if (end.x == start.x)
    {
        return 0;
    }
    
    if (end.y  == start.y)
    {
        return -90;
    }
    
    float tanAngle = (end.x - start.x) / (end.y - start.y);
    float anglePI = atan(tanAngle);
    return anglePI * 180 / M_PI;
}

cocos2d::Vec2 FirstScene::calFinal(cocos2d::Vec2 start, cocos2d::Vec2 end)
{
    float angle = this->calAngle(start, end);
    float anglePI = angle * M_PI / 180;
    if (0 == anglePI)
    {
        return Vec2(start.x, winSize.height + ArrowHeight / 2);
    }
    
    if (-M_PI_2 == anglePI)
    {
        return Vec2(-ArrowHeight / 2, start.y);
    }
    
    float x = -(winSize.height + ArrowHeight / 2) * tan(anglePI);
    if (x > (ArrowHeight / 2 + winSize.width - SideWidth))
    {
        return Vec2(-ArrowHeight / 2, -(ArrowHeight / 2 + winSize.width - SideWidth) / tan(anglePI));
    }
    else
    {
        return Vec2((winSize.height + ArrowHeight / 2) * tan(anglePI) + (winSize.width - SideWidth), winSize.height + ArrowHeight / 2);
    }
}

Vec2 FirstScene::arrowTopPoint()
{
    auto pos = this->sprite->getPosition();
    auto size = this->sprite->getContentSize();
    auto angle = this->sprite->getRotation();
    auto anglePI = angle * M_PI / 180;
    auto offSetX = size.height / 2 * cos(anglePI);
    auto offSetY = size.height / 2 * sin(anglePI);
    return Vec2(pos.x - offSetX, pos.y - offSetY);
}

void FirstScene::resetArrow()
{
    this->sprite->stopAllActions();
    this->sprite->setPosition(Vec2(winSize.width - SideWidth, -ArrowHeight / 2));
    this->sprite->setRotation(0);
}
