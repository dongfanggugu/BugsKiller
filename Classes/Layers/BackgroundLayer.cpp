#include "BackgroundLayer.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

#define DEF_ROLL_SPEED 8

int BackgroundLayer::rollTime = DEF_ROLL_SPEED;

BackgroundLayer* BackgroundLayer::create(const string &filename, float width, float height)
{
    BackgroundLayer *background = new BackgroundLayer();
    if (background && background->init(filename, width, height))
    {
        background->autorelease();
        return background;
    }
    CC_SAFE_DELETE(background);
    return nullptr;
}

bool BackgroundLayer::init(const string &filename, float width, float height)
{
    if (!Layer::init())
    {
        return false;
    }
    this->setContentSize(Size(width, height));
    this->addBackground(filename);
    return true;
}

void BackgroundLayer::addBackground(const string &filename)
{
    auto background = Sprite::create(filename);
//    background->setStretchEnabled(true);
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
//    this->stopAllActions();
}
