/***************************************************************************
*
* ___HelloWorldScene.h___
* ___SpaceGame___
*
* Created by ___NguyenHoangPhuong___ on ___25/07/2013___.
*
* Copyright Vinova Pte. Ltd. All rights reserved.
***************************************************************************
*/

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "proj.win32\CCParallaxNodeExtras.h"

USING_NS_CC;

class HelloWorld : public cocos2d::CCLayer
{
private:
	CCParallaxNodeExtras* mBackgroundNode;
	CCSprite* mSpacedust1;
	CCSprite* mSpacedust2;
	CCSprite* mPlanetsunrise;
	CCSprite* mGalaxy;
	CCSprite* mSpacialanomaly;
	CCSprite* mSpacialanomaly2;

	cocos2d::CCSpriteBatchNode* mBatchNode;
	cocos2d::CCSprite* mShip;

	void update(float pDt);

	float mShipPointsPerSecY;

	CCArray* mAsteroids;
	int mNextAsteroids;
	float mNextAsteroidSpawn;


public:
	float randomValueBetween(float pLow, float pHigh);
	void  setInvisible(CCNode* node);
	float getTimeTick();
	virtual void didAccelerate(CCAcceleration* pAccelerationValue);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
