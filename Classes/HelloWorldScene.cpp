#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"
#include "FirstScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        this->addTouchEvent(sprite);
        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
    this->addBtn();
    this->keyboardTest();
    
    return true;
}

void HelloWorld::addBtn()
{
    auto btn = cocos2d::ui::Button::create();
    btn->setTitleText("Start");
    btn->setColor(Color3B::RED);
    btn->setOpacity(100);
    btn->setPosition(Vec2(400, 100));
    auto direct = Director::getInstance();
    direct->getWinSize();
    btn->addClickEventListener(std::bind(&HelloWorld::clickBtn, this, std::placeholders::_1));
    this->addChild(btn);
}


void HelloWorld::addTouchEvent(cocos2d::Sprite *sprite)
{
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [&](Touch *touch, Event *event)
    {
        auto touchPos = touch->getLocation();
        auto target = static_cast<Sprite *>(event->getCurrentTarget());
        auto pos = target->getPosition();
        auto size = target->getContentSize();
        auto rect = Rect(pos.x - size.width / 2, pos.y - size.height / 2, size.width, size.height);
        if (rect.containsPoint(touchPos))
        {
            this->clickBtn(nullptr);
            return  true;
        }

        return false;
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, sprite);
}


//void HelloWorld::onKeyPressed(Eventboard::KeyCode keyCode, Event *event)
//{
//    log("key %d pressed", keyCode);
//}

void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event)
{
    log("key %d pressed", keyCode);
}

void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event)
{
    log("key %d released", keyCode);
}

void HelloWorld::keyboardTest()
{
    auto s = Director::getInstance()->getWinSize();
//    auto label = Label::create("keyboard test", "Arial", 28);
//    this->addChild(label, 0);
//    label->setPosition(Point(80, 80));
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = &onKeyPressed;
    listener->onKeyReleased = &onKeyReleased;
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

//void HelloWorld::onKeyReleased(Eventboard::KeyCode, Event *event)
//{
//    log("key %d released", keyCode);
//}

void HelloWorld::clickBtn(Ref *sender)
{
    log("click btn");
    auto director = Director::getInstance();
	director->pushScene(FirstScene::createScene());
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
