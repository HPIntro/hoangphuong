#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::CCLayerColor
{
protected:
	int _projectilesDestroyed;

protected:
	cocos2d::CCArray* _targets;
	cocos2d::CCArray* _projectiles;

public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
   

	void addTarget();
	void spriteMoveFinished(CCNode* sender);
	void gameLogic(float dt);
	void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
	void update(float dt);
	~HelloWorld();
	HelloWorld();

	CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
