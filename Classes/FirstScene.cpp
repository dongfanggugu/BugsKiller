//
//  FirstScene.cpp
//  TestGame-mobile
//
//  Created by 张长浩 on 2018/4/23.
//

#include "FirstScene.h"
#include "Layers/BackgroundLayer.h"
#include "Constant.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

#define ArrowInitY 40
#define BgMargin 100
#define ArrowHeight 80

#define RowAbility 10.0
#define RowCount 5

#define BallWH 20.0

#define BoardW (WinSize.width / (RowAbility - 2))
#define BoardH 16.0

#define PTM_RADIO 10

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
    initWorld();
    initGround();
    addBackgroundLayer();
    addBallBoard();
    addOpLayer();
    addRotationLayer();
    addLeftOperationLayer();
    addBricks();
    addBall();
    ballSpeed = 10;
    ballAngle = 60;
    scheduleUpdate();
//    this->addBugsLayer();
    this->addCloseBtn();
//    this->addSprite();
//    this->addRightBtn();
//    this->addFireBtn();
//    this->addTouchFireListener();
    return true;
}

void FirstScene::addBallBoard()
{
    auto board = BallBoard::create(mWorld, PTM_RADIO, BoardW, BoardH);
    float width = WinSize.width;
    board->setPosition(Vec2(width / 2, 15));
    board->setContentSize(Size(BoardW, BoardH));
    mBoard = board;
    this->addChild(board);
}

void FirstScene::addOpLayer()
{
    auto layer = RightSideOperationLayer::create(40, WinSize.height / 2);
    layer->settag(1);
    layer->setmoveProtocol(this);
    layer->setPosition(Vec2(10, 50));
    this->addChild(layer);
}

void FirstScene::addRotationLayer()
{
    auto layer = RightSideOperationLayer::create(40, WinSize.height / 2);
    layer->settag(2);
    layer->setmoveProtocol(this);
    layer->setPosition(Vec2(WinSize.width - 10 - 40, 50));
    this->addChild(layer);
}

Vec2 FirstScene::calBrickPos(int index, Size size)
{
    int row = index / int(RowAbility);
    int column = index % int(RowAbility);
    float x = BgMargin / 2 + (size.width + 1) * column + size.width / 2;
    float y = WinSize.height - ((size.height + 1) * row + size.height / 2);
    return Vec2(x, y);
}

void FirstScene::addBricks()
{
    for (int i = 0; i < RowCount * RowAbility; i++)
    {
        auto brick = genBrick(i);
        Vec2 pos = calBrickPos(i, brick->getContentSize());
        brick->setPosition(pos);
        this->addChild(brick);
    }
}

Brick* FirstScene::genBrick(int index)
{
    //calcue the height and width of brick
    auto brick = Brick::create();
    brick->setPTMRatio(PTM_RADIO);
    auto size = brick->getContentSize();
    float width = (WinSize.width - 9 - BgMargin) / RowAbility;
    float scale = width / size.width;
    float height = size.height * scale;
    
    b2BodyDef b2BodyDef;
    b2BodyDef.type = b2_staticBody;
    b2Body *body = mWorld->CreateBody(&b2BodyDef);
    
    b2PolygonShape shape;
    shape.SetAsBox(width / 2 / PTM_RADIO, height / 2 /PTM_RADIO);
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 20;
    fixtureDef.friction = 0;
    fixtureDef.restitution = 0;
    body->CreateFixture(&fixtureDef);
    body->SetUserData(brick);
    brick->setB2Body(body);
   
    brick->setContentSize(Size(width, height));
    return brick;
}

void FirstScene::addBall()
{
    mBall = Ball::create();
    //定义一个物体
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    b2Body *body = mWorld->CreateBody(&bodyDef);
    
    //设置物体形状
    b2CircleShape dynamicCircle;
    dynamicCircle.m_radius = BallWH / 2 / PTM_RADIO;
    
    //设置物理属性
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicCircle;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = 1.0f;
    body->CreateFixture(&fixtureDef);
    body->ApplyLinearImpulse(body->GetMass() * b2Vec2(20, 20), body->GetWorldCenter(), false);
    mBall->setB2Body(body);
    
    mBall->setPTMRatio(PTM_RADIO);
    mBall->setContentSize(Size(BallWH, BallWH));
    auto pos = mBoard->getPosition();
    float x = pos.x;
    float y = pos.y + BoardH / 2 + BoardH / 2;
    mBall->setPosition(Vec2(x, y));
    addChild(mBall);
}

void FirstScene::addBugsLayer()
{
    ////auto layer = MosquitomLayer::create();
    //layer->setPosition(Vec2::ZERO);
    //this->addChild(layer);
    //this->bugsLayer = layer;
}

void FirstScene::addRightBtn()
{
   /* auto btn = this->genBtn("right ->", "res/button.png", CC_CALLBACK_1(FirstScene::moveRight, this));
    btn->setContentSize(Size(80, 30));
    btn->setPosition(Vec2(winSize.width - 40 - 8, winSize.height - 15 - 50));
    this->addChild(btn);*/
}

void FirstScene::moveRight(Ref *sender)
{
   /* MoveBy * moveBy;
    moveBy = MoveBy::create(0.2, Vec2(5, 0));
    this->sprite->runAction(moveBy);*/
}

void FirstScene::addFireBtn()
{
   /* auto btn = this->genBtn("FIRE", "res/button_fire.png", CC_CALLBACK_1(FirstScene::fireArrow, this));
    btn->setContentSize(Size(30, 30));
    btn->setPosition(Vec2(winSize.width - 100, winSize.height / 2));
    this->addChild(btn);*/
}

void FirstScene::fireArrow(Ref *sender)
{
    //auto point = this->arrowTopPoint();
//    auto pos = this->sprite->getPosition();
//    auto size = this->sprite->getContentSize();
//    auto moveTo = MoveTo::create(0.5, Vec2(0, winSize.height + size.height));
//    this->sprite->runAction(moveTo);
}

void FirstScene::update(float delta)
{
    int velocityIterations = 8;
    int positionIterations = 1;
    
    mWorld->Step(1.0 / 60.0, velocityIterations, positionIterations);
    
    //remove brick needed to remove
    removeBricks();
}

void FirstScene::removeBricks()
{
    for (Vector<Brick *>::iterator it = mVector.begin(); it != mVector.end(); it++)
    {
        Brick *sp = *it;
        mWorld->DestroyBody(sp->getB2Body());
        sp->removeFromParent();
    }
    mVector.clear();
}

Vec2 FirstScene::nextBallPositon(float timeDelta)
{
    auto cPos = mBall->getPosition();
    float x = ballSpeed * timeDelta * cos(ballAngle / M_PI);
    float y = ballSpeed * timeDelta * sin(ballAngle / M_PI);
    return Vec2(cPos.x + x, cPos.y + y);
}

Button* FirstScene::genBtn(const std::string &title,
                                        const std::string &icon,
                                        const cocos2d::ui::Button::ccWidgetClickCallback &callback)
{
    auto btn = cocos2d::ui::Button::create();
    btn->setScale9Enabled(true);
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
    director->popScene();
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
}

void FirstScene::addCloseBtn()
{
    auto btn = this->genBtn("", "res/back.png", &close);
    btn->setContentSize(Size(45, 45));
    btn->setPosition(Vec2(35, WinSize.height - 35));
    this->addChild(btn);
}

void FirstScene::addSprite()
{
    /*this->sprite = Sprite::create();
    this->sprite->setTexture("res/arrow.png");
    this->sprite->setContentSize(Size(15, 80));
    auto size = this->sprite->getContentSize();
    this->sprite->setPosition(Vec2(winSize.width - SideWidth, -40));
    this->addChild(this->sprite);*/
}

void FirstScene::addBackgroundLayer()
{
    auto layer = BackgroundLayer::create("res/background.PNG", WinSize.width - BgMargin, WinSize.height);
    layer->setPosition(Vec2(WinSize.width / 2 , WinSize.height / 2));
    this->addChild(layer);
}

void FirstScene::loadPackageImage()
{
   /* SpriteFrameCache *frameCache = SpriteFrameCache::getInstance();
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
    this->sprite->runAction(action);*/
}

void FirstScene::move1(Ref *sender)
{
//    auto moveBy = MoveBy::create(8, Vec2(980, 0));
//    auto moveTo = MoveTo::create(8, Vec2(500, 0));
////    auto ac = moveBy->reverse();
//    this->sprite->runAction(moveTo);
}

void FirstScene::checkCollison()
{
   /* auto rect = this->bugsLayer->getBugBoundBoxing();
    auto pos = this->bugsLayer->getPosition();
    auto newRect = Rect(rect.getMinX() + pos.x, rect.getMinY() + pos.y, rect.size.width, rect.size.height);
    
    auto arrowPoint = arrowTopPoint();
    if (newRect.containsPoint(arrowTopPoint()))
    {
        this->bugsLayer->bugDie();
        resetArrow();
    }*/
}

void FirstScene::addLeftOperationLayer()
{
    auto layer = LeftSideOperationLayer::create();
    layer->moveProtocol = this;
    layer->setContentSize(WinSize);
    this->addChild(layer);
}

void FirstScene::onMove(float delta)
{
//    mBoard->setRotation(0);
    auto pos = mBoard->getPosition();
    auto size = mBoard->getContentSize();
    float x = pos.x + delta;
    x = MIN(x, WinSize.width - size.width / 2);
    x = MAX(x, size.width / 2);
    auto newPos = Vec2(x, pos.y);
    mBoard->setPosition(newPos);
}

FirstScene::~FirstScene()
{
    log("dealloc %s", typeid(this).name());
}

float opRadio()
{
    return (WinSize.width - BgMargin) / (WinSize.height / 2);
}

void FirstScene::onTouch(unsigned tag)
{
   if (1 == tag)
   {
       //left
       rotationBoard(15);
   }
   else if (2 == tag)
   {
       //right
       rotationBoard(-15);
   }
}

void FirstScene::onMove(float delta, unsigned tag)
{
    
}

void FirstScene::rotationBoard(float angle)
{
    float curAngle = mBoard->getRotation();
    float newAngle = curAngle + angle;
    if (curAngle != 0)
    {
        newAngle = 0;
    }
    mBoard->setRotation(newAngle);
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
    /*auto start = Vec2(winSize.width - SideWidth, 0);
    auto angle = this->calAngle(start, pos);
    this->sprite->setRotation(angle);
    auto fPos = this->calFinal(start, pos);
    auto moveTo = MoveTo::create(1, fPos);
    this->sprite->runAction(moveTo);*/
}

//float FirstScene::calAngle(cocos2d::Vec2 start, cocos2d::Vec2 end)
//{
//   /* if (end.x == start.x)
//    {
//        return 0;
//    }
//    
//    if (end.y  == start.y)
//    {
//        return -90;
//    }
//    
//    float tanAngle = (end.x - start.x) / (end.y - start.y);
//    float anglePI = atan(tanAngle);
//    return anglePI * 180 / M_PI;*/
//}

//cocos2d::Vec2 FirstScene::calFinal(cocos2d::Vec2 start, cocos2d::Vec2 end)
//{
//   /* float angle = this->calAngle(start, end);
//    float anglePI = angle * M_PI / 180;
//    if (0 == anglePI)
//    {
//        return Vec2(start.x, winSize.height + ArrowHeight / 2);
//    }
//    
//    if (-M_PI_2 == anglePI)
//    {
//        return Vec2(-ArrowHeight / 2, start.y);
//    }
//    
//    float x = -(winSize.height + ArrowHeight / 2) * tan(anglePI);
//    if (x > (ArrowHeight / 2 + winSize.width - SideWidth))
//    {
//        return Vec2(-ArrowHeight / 2, -(ArrowHeight / 2 + winSize.width - SideWidth) / tan(anglePI));
//    }
//    else
//    {
//        return Vec2((winSize.height + ArrowHeight / 2) * tan(anglePI) + (winSize.width - SideWidth), winSize.height + ArrowHeight / 2);
//    }*/
//}

//Vec2 FirstScene::arrowTopPoint()
//{
//   /* auto pos = this->sprite->getPosition();
//    auto size = this->sprite->getContentSize();
//    auto angle = this->sprite->getRotation();
//    auto anglePI = angle * M_PI / 180;
//    auto offSetX = size.height / 2 * cos(anglePI);
//    auto offSetY = size.height / 2 * sin(anglePI);
//    return Vec2(pos.x - offSetX, pos.y - offSetY);*/
//}

void FirstScene::resetArrow()
{
   /* this->sprite->stopAllActions();
    this->sprite->setPosition(Vec2(winSize.width - SideWidth, -ArrowHeight / 2));
    this->sprite->setRotation(0);*/
}

void FirstScene::initWorld()
{
    b2Vec2 gravity = b2Vec2(0, 0);
    mWorld = new b2World(gravity);
    mWorld->SetContactListener(this);
    setB2boxDebug();
}

void FirstScene::initGround()
{
    b2BodyDef b2BodyDef;
    b2Body *groundBody = mWorld->CreateBody(&b2BodyDef);
    
    b2EdgeShape groundBox;
    //left
    groundBox.Set(b2Vec2(50 / PTM_RADIO, 0), b2Vec2(50 / PTM_RADIO, WinSize.height / PTM_RADIO));
    groundBody->CreateFixture(&groundBox, 0);
    //top
    groundBox.Set(b2Vec2(50 / PTM_RADIO, WinSize.height / PTM_RADIO),
                  b2Vec2((WinSize.width - 50) / PTM_RADIO, WinSize.height / PTM_RADIO));
    groundBody->CreateFixture(&groundBox, 0);
    //right
    groundBox.Set(b2Vec2((WinSize.width - 50) / PTM_RADIO, 0),
                  b2Vec2((WinSize.width - 50) / PTM_RADIO, WinSize.height / PTM_RADIO));
    groundBody->CreateFixture(&groundBox, 0);
    //bottom
    groundBox.Set(b2Vec2(50 / PTM_RADIO, 0),
                  b2Vec2((WinSize.width - 50) / PTM_RADIO, 0));
    groundBody->CreateFixture(&groundBox, 0);
}

void FirstScene::BeginContact(b2Contact *contact)
{
    b2Body *bodyA = contact->GetFixtureA()->GetBody();
    b2Body *bodyB = contact->GetFixtureB()->GetBody();
    auto userDataA = bodyA->GetUserData();
    auto userDataB = bodyB->GetUserData();
    if (userDataA)
    {
        auto sp = static_cast<Brick *>(userDataA);
        mVector.pushBack(sp);
    }
    
    if (userDataB)
    {
        auto sp = static_cast<Brick *>(userDataB);
        mVector.pushBack(sp);
    }
}

void FirstScene::EndContact(b2Contact *contact)
{
    
}

void FirstScene::setB2boxDebug()
{
    //auto debugDraw = new GLESDebugDraw(PTM_RADIO);
    //uint32 flags = 0;
    //flags += b2Draw::e_shapeBit;
    //flags += b2Draw::e_jointBit;
    //flags += b2Draw::e_centerOfMassBit;
    //debugDraw->SetFlags(flags);
    //mWorld->SetDebugDraw(debugDraw);
}

//void FirstScene::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags)
//{
//    GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION);
//    mWorld->DrawDebugData();
//    CHECK_GL_ERROR_DEBUG();
//}

