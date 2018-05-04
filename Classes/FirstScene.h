//
//  FirstScene.hpp
//  TestGame-mobile
//
//  Created by 张长浩 on 2018/4/23.
//

#ifndef FirstScene_hpp
#define FirstScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "./OperationLayer/LeftSideOperationLayer.hpp"
#include "MosquitomLayer.hpp"

class FirstScene : public cocos2d::Scene, public LeftSideMoveProtocol
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    virtual void update(float delta);
    virtual void onMove(float length);
    CREATE_FUNC(FirstScene);
    virtual ~FirstScene();
    
private:
    cocos2d::ui::Button* genBtn(const std::string &title,
                                const std::string &icon,
                                const cocos2d::ui::Button::ccWidgetClickCallback &callback);
    void addKeyboardTest();
    void addSprite();
    cocos2d::Sprite *sprite;
    MosquitomLayer *bugsLayer;
    
    void move1(Ref *sender);
    void loadPackageImage();
    void addCloseBtn();
    void addLeftBtn();
    void addRightBtn();
    void addFireBtn();
    void moveRight(Ref *sender);
    void moveLeft(Ref *sender);
    void fireArrow(Ref *sender);
    void addBugsLayer();
    void checkCollison();
    void addBackgroundLayer();
    void addLeftOperationLayer();
};

#endif /* FirstScene_hpp */
