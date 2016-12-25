#include "ResultScene.h"
#include "GameScene.h"
#include "golbalVar.h"

USING_NS_CC;

Scene* Result::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Result::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool Result::init()
{
	if ( !Layer::init() )
    {
        return false;
    }

	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto sprite=Sprite::create("GameOver.png");
	sprite->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/5*4));
	this->addChild(sprite, 12);

	__String *score0=__String::createWithFormat("%d",scoren);
	std::string score=score0->getCString();
	score="Score:"+score;
	float time1=frameElapsed/60;
	__String *time0=__String::createWithFormat("%f",time1);
	std::string time=time0->getCString();
	time="Time:"+time+" s";

	auto scoreLabel = LabelTTF::create(score, "Arial", 32);
	auto timeLabel=LabelTTF::create(time,"Arial",32);
	scoreLabel->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/5*3));
	timeLabel->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/5*2));
	this->addChild(scoreLabel);
	this->addChild(timeLabel);

	auto restartItem=MenuItemFont::create("Restart!",CC_CALLBACK_1(Result::restartCallback, this));
	restartItem->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/5*1));

	auto menu = Menu::create(restartItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

	auto ball = Sprite::create("Ball.png");
	ball->setPosition(origin+Vec2(visibleSize.width/2, visibleSize.height/2));
	addChild(ball, 10, BALLTAG);

    return true;
}

void Result::restartCallback(Ref* pSender)
{
	auto scene = Game::createScene();
    Director::getInstance()->replaceScene(scene);
}

void Result::onEnter()
{
	Layer::onEnter();
	//log("HelloWorld onEnter");
	VelocityX=0;
	VelocityY=0;//set the default velocity
	setAccelerometerEnabled(true);
}

void Result::onAcceleration(Acceleration* acc, Event *unused_event)
{
    log("{x = %f, y = %f}", acc->x,acc->y);
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Sprite* ball = (Sprite*)this->getChildByTag(BALLTAG);
    Size s = ball->getContentSize();
    Vec2 p0 = ball->getPosition();

	VelocityX+=ACRATE*acc->x;//The volecity member
	VelocityY+=ACRATE*acc->y;
    
    float p1x =  p0.x + VelocityX * SPEED ;//dt already ignored
    if ((p1x - s.width/2) <0) {
        p1x = s.width/2;
        VelocityX=-REBONCE*VelocityX;
    }
    if ((p1x + s.width / 2) > visibleSize.width) {
        p1x = visibleSize.width - s.width / 2;
        VelocityX=-REBONCE*VelocityX;
    }
    
    float p1y =  p0.y + VelocityY * SPEED ;
    if ((p1y - s.height/2) < 0) {
        p1y = s.height/2;
        VelocityY=-REBONCE*VelocityY;
    }
    if ((p1y + s.height/2) > visibleSize.height) {
        p1y = visibleSize.height - s.height/2;
        VelocityY=-REBONCE*VelocityY;
    }
    ball->runAction(Place::create(Vec2( p1x, p1y))); 

}

void Result::onExit()
{
	Layer::onExit();
	//log("HelloWorld onExit");
}
