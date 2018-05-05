#include "BackgroundLayer.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define DEF_ROLL_SPEED 8

int BackgroundLayer::rollTime = DEF_ROLL_SPEED;

#define winSize Director::getInstance()->getWinSize()

bool BackgroundLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    this->setContentSize(Size(winSize.width - 100, winSize.height));
    this->setAnchorPoint(Vec2(0.5, 0.5));
    this->addBackground();
    return true;
}

void BackgroundLayer::addBackground()
{
    auto aa = getAnchorPoint();
    auto background = Scale9Sprite::create("res/background.PNG");
    background->setScale9Enabled(true);
    background->setContentSize(this->getContentSize());
    background->setPosition(Vec2::ZERO);
    this->addChild(background);
}

void BackgroundLayer::startRollbg()
{
   /* auto bg = createBackground(Vec2::ZERO);
    auto bg2 = createBackground(Vec2(0, winSize.height));

    auto mt = MoveBy::create(rollTime, Vec2(0, -winSize.height));
    auto ta = TargetedAction::create(bg, mt);
    auto ta2 = TargetedAction::create(bg2, mt->clone());
    auto spawn = Spawn::createWithTwoActions(ta, ta2);

    auto rf = RepeatForever::create(Sequence::createWithTwoActions(spawn, CallFunc::create([=]()
    {
        bg->setPositionY(0);
        bg2->setPositionY(winSize.height);
    })));
    this->runAction(rf);*/
}

void BackgroundLayer::stop()
{
    this->stopAllActions();
}

BackgroundLayer::~BackgroundLayer()
{
    log("backgroundlayer dealloc");
}
