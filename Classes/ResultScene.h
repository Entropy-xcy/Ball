#ifndef __RESULT_SCENE_H__
#define __RESULT_SCENE_H__

#include "cocos2d.h"

class Result : public cocos2d::Layer
{
	
public:
	virtual bool init(); 
	static cocos2d::Scene* createScene();
	double VelocityX,VelocityY;
	void restartCallback(cocos2d::Ref* pSender);
	virtual void onEnter();
	virtual void onAcceleration(cocos2d::Acceleration* acc, cocos2d::Event *unused_event);
	virtual void onExit();
	CREATE_FUNC(Result);
};

#endif // __HELLOWORLD_SCENE_H__