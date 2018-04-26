//
//  FirstScene.cpp
//  TestGame-mobile
//
//  Created by 张长浩 on 2018/4/23.
//

#include "FirstScene.h"
#include "BackgroundLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

Scene* FirstScene::createScene()
{
    return FirstScene::create();
}

bool FirstScene::init()
{
    auto layer = BackgroundLayer::create();
    this->addChild(layer);
    //LayerColor *bgColor = LayerColor::create(Color4B(255, 255, 255, 255));
    //bgColor->setContentSize(Size(1000, 760));
    //bgColor->setPosition(0, 0);
    //bgColor->setAnchorPoint(Vec2(0, 0));

    //this->addChild(bgColor);

    this->addCloseBtn();
    this->addSprite();
    this->addRightBtn();
    return true;
}

Size winSize();

void FirstScene::addRightBtn()
{
    auto btn = this->genBtn("right ->", "res/button.png", CC_CALLBACK_1(FirstScene::moveRight, this));
    btn->setContentSize(Size(80, 30));
    btn->setPosition(Vec2(winSize().width / 2 + 40 + 8, winSize().height - 8 - 15));
    this->addChild(btn);
}

void FirstScene::moveRight(Ref *sender)
{
    loadPackageImage();
    MoveBy * moveBy;
    moveBy = MoveBy::create(0.2, Vec2(10, 0));
    this->sprite->runAction(moveBy);
}

Size winSize()
{
    auto direct = Director::getInstance();
    return direct->getWinSize();
}

cocos2d::ui::Button* FirstScene::genBtn(const std::string &title,
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
}

void FirstScene::addCloseBtn()
{
    auto btn = this->genBtn("", "CloseNormal.png", &close);
    btn->setContentSize(Size(80, 20));
    btn->setPosition(Vec2(winSize().width - 80, winSize().height -20));
    this->addChild(btn);
}


void FirstScene::addSprite()
{
    this->sprite = Sprite::create();
    sprite->setAnchorPoint(Vec2(0, 0));
    this->sprite->setTexture("res/a1.png");
    this->sprite->setPosition(Vec2(0, 0));
    this->setContentSize(Size(40, 40));
    this->sprite->setScale(1);
    this->addChild(this->sprite);
    this->loadPackageImage();

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


FirstScene::~FirstScene()
{
    log("dealloc");
}
