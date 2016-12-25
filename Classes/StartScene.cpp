#include "StartScene.h"
#include "GameScene.h"
USING_NS_CC;

Scene* Start::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Start::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Start::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

////////////////////////
	//create menuitems
	auto startItem = MenuItemFont::create("Start",CC_CALLBACK_1(Start::startItemCallback,this));
	startItem->setPosition(Vec2(origin.x+origin.x + (visibleSize.width-80)/3*1.5+40,
								origin.y + visibleSize.height/8+(startItem->getContentSize().height)*2));

	
	auto settingItem = MenuItemFont::create("Setings",CC_CALLBACK_1(Start::settingItemCallback,this));
	settingItem->setPosition(Vec2(origin.x + (visibleSize.width-80)/3*0.5+40 ,
                                origin.y + visibleSize.height/8));


	auto infoItem = MenuItemFont::create("Info",CC_CALLBACK_1(Start::infoItemCallback,this));
	infoItem->setPosition(Vec2(origin.x+origin.x + (visibleSize.width-80)/3*1.5+40,
								origin.y + visibleSize.height/8));


    auto closeItem = MenuItemFont::create("Exit",CC_CALLBACK_1(Start::menuCloseCallback, this));
    closeItem->setPosition(Vec2(origin.x+origin.x + (visibleSize.width-80)/3*2.5+40,
								origin.y + visibleSize.height/8));
/////////////////////////

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem,settingItem,infoItem,startItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...


	/////////////////////////////
   
	//add Caption label
    auto label = LabelTTF::create("Super Trial", "Arial", 24);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);

    // add logo picture
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y)+Vec2(0,visibleSize.height/10));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}


void Start::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

//Get to the Setting Scene
void Start::settingItemCallback(cocos2d::Ref* pSender)
{
	log("Setting button called");
}

//Get to the Info Scene 
void Start::infoItemCallback(cocos2d::Ref* pSender)
{
	log("Info button called");
}

//Get to the Game Scene
void Start::startItemCallback(cocos2d::Ref* pSender)
{
	log("Start button called");
	auto scene = Game::createScene();
    Director::getInstance()->pushScene(scene);
}