//
//  BallBoard.cpp
//  BugsKiller
//
//  Created by 张长浩 on 2018/10/10.
//

#include "BallBoard.hpp"

USING_NS_CC;
using namespace std;

BallBoard* BallBoard::create(b2World *world, float ptm, float width, float height)
{
    BallBoard *board = new BallBoard();
    if (board && board->initWithFile("res/ballboard.png"))
    {
        board->setwidth(width);
        board->setheight(height);
        board->setworld(world);
        board->setPTMRatio(ptm);
        board->addB2Body();
        board->autorelease();
        return board;
    }
    CC_SAFE_DELETE(board);
    return nullptr;
}

void BallBoard::addB2Body()
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    b2Body *body = _world->CreateBody(&bodyDef);
    
    b2PolygonShape shape;
    shape.SetAsBox(getwidth() / 2 / getPTMRatio(), getheight() / 2 / getPTMRatio());

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.friction = 0;
    fixtureDef.restitution = 1;
    body->CreateFixture(&fixtureDef);
    setB2Body(body);
}

BallBoard::~BallBoard()
{
    log("dealloc %s", typeid(this).name());
}
