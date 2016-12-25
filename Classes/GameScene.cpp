#include "GameScene.h"
#include"cmath"
#include"ResultScene.h"
#include"golbalVar.h"

USING_NS_CC;

Scene* Game::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool Game::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	ifGenerate=true;
	ifZero=true;
	healthtag=Sprite::create("health1.png");
	this->addChild(healthtag);
	this->list=__Array::createWithCapacity(2000);
	this->list->retain();

	boomList=__Array::createWithCapacity(100);

	if(ifGenerate)
	{
		this->scheduleUpdate();
	}

	if(ifZero)
	{
		toZero();
	}
	//
	//bool a=Game::isTap(bg, Vec2(200,200));
	auto ball = Sprite::create("Ball.png");
	ball->setPosition(origin+Vec2(visibleSize.width/2, visibleSize.height/2));
	addChild(ball, 10, BALLTAG);

    return true;
}

void Game::update(float dt)
{
	frameElapsed++;
	dynamicGeneration();
	showHealth();
	Ref *obj=nullptr;
	//int n=this->list->count();
	iftap=false;
	CCARRAY_FOREACH(this->list, obj)
	{
		Sprite *sprite=(Sprite*)obj;
		Vec2 dot=sprite->getPosition();

		Sprite *ball=(Sprite*)this->getChildByTag(BALLTAG);

		if(isTap(ball,dot))
		{
			collisionPoint=dot;
			healthDeduction();
			iftap=true;
			//gameOver();
		}
	}
	ifcalled=iftap;
}

Game::Game()
{
	this->Speed=0.01;
	this->spriteSize=Size(16,16);
	randomize();
	filename="NormalEnemy.png";
}

bool Game::generateSeed()
{
	short instance2,instance1;
	double P0,P1,P3,P4;

	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size spriteSize=this->spriteSize;

	P0=CCRANDOM_MINUS1_1();
	P1=CCRANDOM_0_1();
	P3=CCRANDOM_MINUS1_1();
	P4=CCRANDOM_0_1();

	if(P0>0)
	{
		if(P0>0.5)
		{
			//instance1
			instance1=1;
			this->Position0.x=origin.x-spriteSize.width-safeMargin;
			this->Position0.y=origin.y+visibleSize.height*P1;
		}
		else
		{
			//instance2
			instance1=2;
			this->Position0.x=origin.x+visibleSize.width*P1;
			this->Position0.y=origin.y+visibleSize.height+spriteSize.height+safeMargin;
		}
	}
	else
	{
		if(P0<-0.5)
		{
			//instance3
			instance1=3;
			this->Position0.x=origin.x+visibleSize.width+spriteSize.width+safeMargin;
			this->Position0.y=origin.y+visibleSize.height*P1;
		}
		else
		{
			//instance4
			instance1=4;
			this->Position0.x=origin.x+visibleSize.width*P1;
			this->Position0.y=origin.y-spriteSize.height-safeMargin;
		}
	}
	
	
	if(P3>0)
	{
		if(P3>0.5)
		{
			//instance1
			instance2=1;
			this->Position1.x=origin.x-spriteSize.width-safeMargin;
			this->Position1.y=origin.y+visibleSize.height*P4;
		}
		else
		{
			//instance2
			instance2=2;
			this->Position1.x=origin.x+visibleSize.width*P4;
			this->Position1.y=origin.y+visibleSize.height+spriteSize.height+safeMargin;
		}
	}
	else
	{
		if(P3<-0.5)
		{
			//instance3
			instance2=3;
			this->Position1.x=origin.x+visibleSize.width+spriteSize.width+safeMargin;
			this->Position1.y=origin.y+visibleSize.height*P4;
		}
		else
		{
			//instance4
			instance2=4;
			this->Position1.x=origin.x+visibleSize.width*P4;
			this->Position1.y=origin.y-spriteSize.height-safeMargin;
		}
	}

	if(instance1==instance2)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Game::randomize()
{
	while(!generateSeed());
	getDuringTime();
}

void Game::getDuringTime()
{
	this->dt=std::sqrt((this->Position1.x-this->Position0.x)*(this->Position1.x-this->Position0.x)+(this->Position0.y-this->Position1.y)*(this->Position0.y-this->Position1.y))*Speed;
}

void Game::run(int type)
{
	switch(type)
	{
	case 0:
			this->Speed=0.01;
			this->spriteSize=Size(16,16);
			filename="NormalEnemy.png";
			scoren+=5;
			break;
	case 1:
			this->Speed=0.005;
			this->spriteSize=Size(16,16);
			filename="HighSpeedEnemyl.png";
			scoren+=6;
			break;
	case 2:
			this->Speed=0.02;
			this->spriteSize=Size(16,16);
			filename="LowSpeedEnemy.png";
			scoren+=7;
			break;
	}
	randomize();
	double a=this->dt;
	auto sprite=Sprite::create(filename);
	sprite->setPosition(this->Position0);
	this->addChild(sprite ,11);
	this->list->addObject(sprite);
	FiniteTimeAction *ac=MoveTo::create(this->dt,this->Position1);
	FiniteTimeAction *acf=CallFuncN::create(CC_CALLBACK_1(Game::cleanSprite,this));
	sprite->runAction(Sequence::create(ac,acf,NULL));
}

void Game::cleanSprite(Ref *pSender)
{
	Sprite *sp=(Sprite*)pSender;
	this->list->removeObject(sp);
	sp->removeFromParentAndCleanup(true);
}

Game::~Game()
{
	this->list->removeAllObjects();
	CC_SAFE_RELEASE_NULL(this->list);
}

bool Game::isTap(Node *node,Vec2 position)
{
	Vec2 locationInNode = node->convertToNodeSpace(position);
	Size s=node->getContentSize();
	Rect rect=Rect(0,0,s.width,s.height);
	//bool b=rect.containsPoint(locationInNode);
	if(rect.containsPoint(locationInNode))
	{
		return true;
	}
	return false;
}

void Game::onEnter()
{
	Layer::onEnter();
	//log("HelloWorld onEnter");
	VelocityX=0;
	VelocityY=0;//set the default velocity
	setAccelerometerEnabled(true);
}

void Game::onAcceleration(Acceleration* acc, Event *unused_event)
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

void Game::onExit()
{
	Layer::onExit();
	//log("HelloWorld onExit");
}

void Game::gameOver()
{
	auto sprite=Sprite::create("Boom.png");
	sprite->setPosition(collisionPoint);
	this->addChild(sprite,200);
	FiniteTimeAction *sa=ScaleTo::create(0.5,2);
	FiniteTimeAction *acf=CallFuncN::create(CC_CALLBACK_0(Game::showResult,this));
	sprite->runAction(Sequence::create(sa,acf,NULL));
}

void Game::showResult()
{
	auto scene = Result::createScene();
    Director::getInstance()->replaceScene(scene);
}

void Game::dynamicGeneration()
{
	i++;
	if(i%20==0)
	{
		run(0);
	}
	if(i%60==0)
	{
		run(1);
	}
	if(i%50==0)
	{
		run(2);
	}
	
}

void Game::toZero()
{
	i=0;
	frameElapsed=0;
	scoren=0;
	health=3;
	ifcalled=false;
}

void Game::showHealth()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	switch (health)
	{
	case 0:
		gameOver();
	case 1:
		healthtag->removeFromParentAndCleanup(true);
		healthtag=Sprite::create("health1.png");
		healthtag->setPosition(Vec2(origin.x+40+healthtag->getContentSize().width/2,
			origin.y+visibleSize.height-40-healthtag->getContentSize().height/2));
		this->addChild(healthtag,102);
		break;

	case 2:
		healthtag->removeFromParentAndCleanup(true);
		healthtag=Sprite::create("health2.png");
		healthtag->setPosition(Vec2(origin.x+40+healthtag->getContentSize().width/2,
			origin.y+visibleSize.height-40-healthtag->getContentSize().height/2));
		this->addChild(healthtag,102);
		break;

	case 3:
		healthtag->removeFromParentAndCleanup(true);
		healthtag=Sprite::create("health3.png");
		healthtag->setPosition(Vec2(origin.x+40+healthtag->getContentSize().width/2,
			origin.y+visibleSize.height-40-healthtag->getContentSize().height/2));
		this->addChild(healthtag,102);
		break;

	}
}

void Game::healthDeduction()
{
	if(!ifcalled)
	{
		auto sprite=Sprite::create("Boom.png");
		sprite->setPosition(collisionPoint);
		this->addChild(sprite,200);
		ifcalled=false;
		FiniteTimeAction *sa=ScaleTo::create(0.5,2);
		FiniteTimeAction *acf=CallFuncN::create(CC_CALLBACK_1(Game::minusHealth,this));
		sprite->runAction(Sequence::create(sa,acf,NULL));
	}
	ifcalled=true;
}

void Game::minusHealth(Ref* pSender)
{
	auto sprite=(Sprite*)pSender;
	sprite->removeFromParentAndCleanup(true);
	health=health-1;
}
