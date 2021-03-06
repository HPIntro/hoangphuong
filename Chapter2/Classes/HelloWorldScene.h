/***************************************************************************
*
* ___HelloWorldScene.h___
* ___Chapter2___
*
* Created by ___NguyenHoangPhuong___ on ___25/7/2013___.
*
* Copyright Vinova Pte. Ltd. All rights reserved.
***************************************************************************
*/

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::CCLayerColor
{
protected:
	int nProjectilesDestroyed;

protected:
	cocos2d::CCArray* mTargets;
	cocos2d::CCArray* mProjectiles;

public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
   

	void addTarget();
	void spriteMoveFinished(CCNode* pSender);
	void gameLogic(float pDt);
	void ccTouchesEnded(cocos2d::CCSet* pTouches, cocos2d::CCEvent* pEvent);
	void update(float pDt);
	~HelloWorld();
	HelloWorld();

	CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
