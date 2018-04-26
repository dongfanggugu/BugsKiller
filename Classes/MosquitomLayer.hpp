//
//  MosquitomLayer.hpp
//  TestGame
//
//  Created by 张长浩 on 2018/4/26.
//

#ifndef MosquitomLayer_hpp
#define MosquitomLayer_hpp

#include <stdio.h>
#include "cocos2d.h"

enum Towards {Left, Right};

class MosquitomLayer : public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(MosquitomLayer);
    virtual void update(float delta);
    cocos2d::Sprite* sprite;
private:
    void addSprite();
    void flying();
    Towards towards;
};

#endif /* MosquitomLayer_hpp */
