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

class FirstScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(FirstScene);
    virtual ~FirstScene();
    
private:
    cocos2d::ui::Button* genBtn(const std::string &title,
                                const std::string &icon,
                                const cocos2d::ui::Button::ccWidgetClickCallback &callback);
    void addKeyboardTest();
    void addSprite();
    cocos2d::Sprite *sprite;
    void move1(Ref *sender);
    void loadPackageImage();
    void addCloseBtn();
    void addLeftBtn();
    void addRightBtn();
    void addJumpBtn();
    void moveRight(Ref *sender);
    void moveLeft(Ref *sender);
};

#endif /* FirstScene_hpp */
