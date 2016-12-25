#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#define safeMargin 20
#define SPEED 			3.5
#define REBONCE         0.6
#define ACRATE          0.5
#define BALLTAG 101

class Game : public cocos2d::Layer
{
	cocos2d::__Array *list;
	cocos2d::Vec2 Position0,Position1;
	cocos2d::Size spriteSize;
	double dt,Speed;
	std::string filename;
public:
	cocos2d::__Array *boomList;
	cocos2d::Sprite *healthtag;
	bool ifcalled,ifcalled1,iftap;
	Game();
	~Game();
	int i;
	cocos2d::Vec2 collisionPoint;
	double VelocityX,VelocityY;
    static cocos2d::Scene* createScene();
    virtual bool init();  
	virtual void update(float dt);
	void randomize();
	bool generateSeed();
	void getDuringTime();
	void run(int type);
	void cleanSprite(cocos2d::Ref *pSender);
	bool isTap(cocos2d::Node *node,cocos2d::Vec2 position);
	virtual void onEnter();
	virtual void onExit();
	virtual void onAcceleration(cocos2d::Acceleration* acc, cocos2d::Event *unused_event);
	void gameOver();
	void showResult();
	void dynamicGeneration();
	void toZero();
	void showHealth();
	void healthDeduction();
	void minusHealth(cocos2d::Ref* pSender);
	//static long int time;
    CREATE_FUNC(Game);
	
};

#endif // __HELLOWORLD_SCENE_H__

