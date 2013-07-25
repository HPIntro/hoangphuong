/***************************************************************************
*
* ___HelloWorldScene.cpp___
* ___SpaceGame___
*
* Created by ___NguyenHoangPhuong___ on ___25/07/2013___.
*
* Copyright Vinova Pte. Ltd. All rights reserved.
***************************************************************************
*/

#include "HelloWorldScene.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
 //   //////////////////////////////
 //   // 1. super init first
 //   if ( !CCLayer::init() )
 //   {
 //       return false;
 //   }
 //   
 //   CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
 //   CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

 //   /////////////////////////////
 //   // 2. add a menu item with "X" image, which is clicked to quit the program
 //   //    you may modify it.

 //   // add a "close" icon to exit the progress. it's an autorelease object
 //   CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
 //                                       "CloseNormal.png",
 //                                       "CloseSelected.png",
 //                                       this,
 //                                       menu_selector(HelloWorld::menuCloseCallback));
 //   
	//pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
 //                               origin.y + pCloseItem->getContentSize().height/2));

 //   // create menu, it's an autorelease object
 //   CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
 //   pMenu->setPosition(CCPointZero);
 //   this->addChild(pMenu, 1);

 //   /////////////////////////////
 //   // 3. add your codes below...

 //   // add a label shows "Hello World"
 //   // create and initialize a label
 //   
 //   CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
 //   
 //   // position the label on the center of the screen
 //   pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
 //                           origin.y + visibleSize.height - pLabel->getContentSize().height));

 //   // add the label as a child to this layer
 //   this->addChild(pLabel, 1);

 //   // add "HelloWorld" splash screen"
 //   CCSprite* pSprite = CCSprite::create("HelloWorld.png");

 //   // position the sprite on the center of the screen
 //   pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

 //   // add the sprite as a child to this layer
 //   this->addChild(pSprite, 0);
 //   
 //   return true;

	

	//Sprite
	mBatchNode = CCSpriteBatchNode::create("Sprites.pvr.ccz");
	this->addChild(mBatchNode);
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Sprites.plist");

	mShip = CCSprite::createWithSpriteFrameName("SpaceFlier_sm_1.png");
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	mShip->setPosition( ccp(winSize.width * 0.1, winSize.height * 0.5));
	mBatchNode->addChild(mShip, 1);

	//create CCParallaxNode
	mBackgroundNode = CCParallaxNodeExtras::node();
	

	//create sprite
	mSpacedust1 = CCSprite::create("bg_front_spacedust.png");
	mSpacedust2 = CCSprite::create("bg_front_spacedust.png");
	mPlanetsunrise = CCSprite::create("bg_planetsunrise.png");
	mGalaxy = CCSprite::create("bg_galaxy.png");
	mSpacialanomaly = CCSprite::create("bg_spacialanomaly.png");
	mSpacialanomaly2 = CCSprite::create("bg_spacialanomaly2.png");

	//Movement speed
	CCPoint duslSpeed = ccp(0.1, 0.1);
	CCPoint bgSpeed   = ccp(0.05, 0.05);

	//children of CCParallaxNode
	mBackgroundNode->addChild(mSpacedust1, 0, duslSpeed, ccp(0, winSize.height/2) );
	mBackgroundNode->addChild(mSpacedust2, 0, duslSpeed,
		ccp(mSpacedust1->getContentSize().width, winSize.height/2));
	mBackgroundNode->addChild(mGalaxy, -1, bgSpeed,
		ccp(0, winSize.height * 0.7));
	mBackgroundNode->addChild(mPlanetsunrise, -1, bgSpeed,
		ccp(600, winSize.height * 0));
	mBackgroundNode->addChild(mSpacialanomaly, -1, bgSpeed, 
		ccp(900, winSize.height * 0.3));
	mBackgroundNode->addChild(mSpacialanomaly2, -1, bgSpeed,
		ccp(1500, winSize.height * 0.9));

	this->addChild(mBackgroundNode, -1);

	HelloWorld::addChild(CCParticleSystemQuad::create("Stars1.plist"));
	HelloWorld::addChild(CCParticleSystemQuad::create("Stars2.plist"));
	HelloWorld::addChild(CCParticleSystemQuad::create("Stars3.plist"));

	this->scheduleUpdate();
	this->setAccelerometerEnabled(true);

	return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::update(float pDt)
{
	CCPoint backgroundScrollVert = ccp(-1000, 0);
	mBackgroundNode->setPosition(ccpAdd(mBackgroundNode->getPosition(),
		ccpMult(backgroundScrollVert, pDt) ));

	//update
	CCArray* spaceDusts = CCArray::createWithCapacity(2);
	spaceDusts->addObject(mSpacedust1);
	spaceDusts->addObject(mSpacedust2);
	for ( int ii = 0; ii <spaceDusts->count(); ii++ ) {
		CCSprite* spaceDust = (CCSprite*)(spaceDusts->objectAtIndex(ii));
		float xPosition = mBackgroundNode->convertToWorldSpace(spaceDust->getPosition()).x;
		float size = spaceDust->getContentSize().width;
		if ( xPosition < -size/2 ) {
			mBackgroundNode->incrementOffset(ccp(spaceDust->getContentSize().width*2,0),spaceDust); 
		}                                   
	}
 
	CCArray* backGrounds = CCArray::createWithCapacity(4);
	backGrounds->addObject(mGalaxy);
	backGrounds->addObject(mPlanetsunrise);
	backGrounds->addObject(mSpacialanomaly);
	backGrounds->addObject(mSpacialanomaly2);
	for ( int ii = 0; ii <backGrounds->count(); ii++ ) {
		CCSprite* background = (CCSprite *)(backGrounds->objectAtIndex(ii));
		float xPosition = mBackgroundNode->convertToWorldSpace(background->getPosition()).x;
		float size = background->getContentSize().width;
		if ( xPosition < -size ) {
			mBackgroundNode->incrementOffset(ccp(2000,0),background); 
		}
	}

	//Moving the Ship
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	float maxY = winSize.height - mShip->getContentSize().height/2;
	float minY = mShip->getContentSize().height/2;
	float diff = (mShipPointsPerSecY * pDt);
	float newY = mShip->getPosition().y + diff;
	newY = MIN(MAX(newY, minY), maxY);
	mShip->setPosition(ccp(mShip->getPosition().x, newY));


}

void HelloWorld::didAccelerate(CCAcceleration* pAccelerationValue)
{
	  #define KFILTERINGFACTOR 0.1
	  #define KRESTACCELX -0.6
	  #define KSHIPMAXPOINTSPERSEC (winSize.height*0.5)        
	  #define KMAXDIFFX 0.2
 
	  double rollingX;

	  pAccelerationValue->x = pAccelerationValue->y;
	  rollingX = (pAccelerationValue->x * KFILTERINGFACTOR) + (rollingX * (1.0 - KFILTERINGFACTOR));    
	  float accelX = pAccelerationValue->x - rollingX;
	  CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	  float accelDiff = accelX - KRESTACCELX;
	  float accelFraction = accelDiff / KMAXDIFFX;
	  mShipPointsPerSecY = KSHIPMAXPOINTSPERSEC * accelFraction;   
}

float HelloWorld::randomValueBetween(float pLow, float pHigh)
{
	return (((float) rand() / 0xFFFFFFFFu) * (pHigh - pLow)) + pLow;

}

float HelloWorld::getTimeTick()
{
	timeval time;
	gettimeofday(&time, NULL);
	unsigned long millisecs = (time.tv_sec * 1000) + (time.tv_usec/1000);
    return (float) millisecs;
}