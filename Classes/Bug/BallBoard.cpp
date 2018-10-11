//
//  BallBoard.cpp
//  BugsKiller
//
//  Created by 张长浩 on 2018/10/10.
//

#include "BallBoard.hpp"

USING_NS_CC;
using namespace std;

BallBoard* BallBoard::create()
{
    BallBoard *board = new BallBoard();
    if (board && board->initWithFile("res/ballboard.png"))
    {
        board->autorelease();
        return board;
    }
    CC_SAFE_DELETE(board);
    return nullptr;
}
