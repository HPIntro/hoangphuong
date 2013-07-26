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
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld* layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//Game over
	mLives = 3;
	double curTime = getTimeTick();
	mGameOverTime = curTime + 30000;
	mGameOver = false;
	//srand(time(0));

	mNextAsteroid = 0;
	mNextShipLaser = 0;
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

	#define KNUMASTEROIDS 15
	mAsteroids = new CCArray();
	for(int i = 0; i < KNUMASTEROIDS; ++i) {
		CCSprite* asteroid = CCSprite::createWithSpriteFrameName("asteroid.png");
		asteroid->setVisible(false);
		mBatchNode->addChild(asteroid);
		mAsteroids->addObject(asteroid);
	}

	#define KNUMLASERS 2
	mShipLasers = new CCArray();
	for ( int i = 0; i < KNUMLASERS; ++i){
		CCSprite* shipLaser = CCSprite::createWithSpriteFrameName("laserbeam_blue.png");
		shipLaser->setVisible(false);
		mBatchNode->addChild(shipLaser);
		mShipLasers->addObject(shipLaser);
	}

	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("SpaceGame.wav",true);
	SimpleAudioEngine::sharedEngine()->preloadEffect("explosion_large.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("laser_ship.wav");

	this->setTouchEnabled(true);
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
	for ( int ii = 0; ii < spaceDusts->count(); ii++ ) {
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
	/*CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	float maxY = winSize.height - mShip->getContentSize().height/2;
	float minY = mShip->getContentSize().height/2;
	float diff = (mShipPointsPerSecY * pDt);
	float newY = mShip->getPosition().y + diff;
	newY = MIN(MAX(newY, minY), maxY);
	mShip->setPosition(ccp(mShip->getPosition().x, newY));*/

	//Stone
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	float curTimeMillis = getTimeTick();
	if (curTimeMillis > mNextAsteroidSpawn) {
 
		float randSecs = randomValueBetween(0.20,1.0) * 1000;
		mNextAsteroidSpawn = randSecs + curTimeMillis;
 
		float randY = randomValueBetween(0.0,winSize.height);
		float randDuration = randomValueBetween(2.0,20.0) * 3;
 
		CCSprite* asteroid = (CCSprite *)mAsteroids->objectAtIndex(mNextAsteroid);

		mNextAsteroid++;
		//CCLog("%d", mNextAsteroid);

		if (mNextAsteroid >= mAsteroids->count())
			mNextAsteroid = 0;
	
        asteroid->stopAllActions();
		asteroid->setVisible(true);
		asteroid->setPosition( ccp(winSize.width+asteroid->getContentSize().width/2, randY));

		asteroid->runAction(CCSequence::create(CCMoveBy::create(randDuration, 
			ccp(-winSize.width-asteroid->getContentSize().width * 4, randY)), 
			CCCallFuncN::create(this, callfuncN_selector(HelloWorld::setInvisible)),
			NULL
		 ));     
 
	}

	CCObject* asteroids;
	CCObject* shipLaze;

	CCARRAY_FOREACH(mAsteroids, asteroids){
		if( !((CCSprite*)asteroids)->isVisible() ){
			continue;
		}
		CCARRAY_FOREACH(mShipLasers, shipLaze){
			if( !((CCSprite*)shipLaze)->isVisible()){
				continue;
			}
			if( ((CCSprite*)shipLaze)->boundingBox().intersectsRect( ((CCSprite*)asteroids)->boundingBox() ) ){
				((CCSprite*)shipLaze)->setVisible(false);
				((CCSprite*)asteroids)->setVisible(false);
				SimpleAudioEngine::sharedEngine()->playEffect("explosion_large.wav");
				continue;
			}
		}

		if(mShip->boundingBox().intersectsRect( ((CCSprite*)asteroids)->boundingBox() )){
			((CCSprite*)asteroids)->setVisible(false);
			mShip->runAction( CCBlink::create(1.0, 9));
			mLives--;
		}
	}

	if (mLives <= 0) {
		mShip->stopAllActions();
		mShip->setVisible(false);
		this->endScene(KENDREASONLOSE);
	} else if (curTimeMillis  >= mGameOverTime) {
		this->endScene(KENDREASONWIN);
	}

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
	/*float rangeY= pHigh - pLow;
	float ran = ( (float)rand() / rangeY) + pLow;
	retur*///n  rand();
	
	return (((float) rand() / 0xFFFFFFu) * (pHigh - pLow)* (pHigh - pLow)) + pLow;

}

float HelloWorld::getTimeTick()
{
	timeval time;
	gettimeofday(&time, NULL);
	unsigned long millisecs = (time.tv_sec * 1000) + (time.tv_usec/1000);
    return (float) millisecs;
}

void HelloWorld::setInvisible(CCNode * pNode) {
    pNode->setVisible(false);
}



//void HelloWorld::ccTouchesBegan(cocos2d::CCSet* pTouches, cocos2d::CCEvent* pEvent)
//{
//	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
//
//	CCSprite* shipLaser = (CCSprite*)mShipLasers->objectAtIndex(mNextShipLaser++);
//	if( mNextShipLaser >= mShipLasers->count() )
//		mNextShipLaser = 0;
//
//	shipLaser->setPosition( ccpAdd( mShip->getPosition(), ccp(shipLaser->getContentSize().width/2, 0)));
//    shipLaser->setVisible(true);
//    shipLaser->stopAllActions();
//    shipLaser->runAction(CCSequence::create(CCMoveBy::create(0.5,ccp(winSize.width, 0)), 
//		CCCallFuncN::create(this, callfuncN_selector(HelloWorld::setInvisible)), 
//		NULL  
//    ));
//}



void HelloWorld::ccTouchesMoved(cocos2d::CCSet* pTouches, cocos2d::CCEvent* pEvent)
{
	SimpleAudioEngine::sharedEngine()->playEffect("laser_ship.wav");

	//Move Ship
	CCTouch* touch = (CCTouch*) pTouches->anyObject();
	CCPoint locat = touch->getLocationInView();

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	float maxY = winSize.height - mShip->getContentSize().height/2;
	float minY = mShip->getContentSize().height/2;
	float diff = (mShipPointsPerSecY * locat.y);
	float newY = mShip->getPosition().y + diff;
	newY = MIN(MAX(newY, minY), maxY);

	mShip->setPosition(ccp(mShip->getPosition().x, winSize.height - locat.y));

	//Fire
	CCSprite* shipLaser = (CCSprite*)mShipLasers->objectAtIndex(mNextShipLaser++);
	if( mNextShipLaser >= mShipLasers->count() )
		mNextShipLaser = 0;

	shipLaser->setPosition( ccpAdd( mShip->getPosition(), ccp(shipLaser->getContentSize().width/2, 0)));
    shipLaser->setVisible(true);
    shipLaser->stopAllActions();
    shipLaser->runAction(CCSequence::create(CCMoveBy::create(0.5,ccp(winSize.width, 0)), 
		CCCallFuncN::create(this, callfuncN_selector(HelloWorld::setInvisible)), 
		NULL  
    ));
}

void HelloWorld::restartTapped(CCObject* pObj)
{
	CCDirector::sharedDirector()->replaceScene(
		CCTransitionZoomFlipX::create(0.5, this->scene() ));
	this->scheduleUpdate();
}

void HelloWorld::endScene( EndReason endReason)
{
	if( mGameOver)
		return;
	mGameOver = true;
	
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	char message[10] = "You Win";
	if( endReason == KENDREASONLOSE) 
		strcpy(message, "YOU LOSE");

	CCLabelBMFont* label;
	label = CCLabelBMFont::create(message, "Arial.fnt");
	label->setScale(0.1);

	label->setPosition( ccp(winSize.width/2, winSize.height * 0.4));
	this->addChild(label);

	CCLabelBMFont* restartLabel;
	strcpy(message, "Restart");
	restartLabel = CCLabelBMFont::create(message, "Arial.fnt");

	CCMenuItemLabel* restartItem = CCMenuItemLabel::create(restartLabel, this,
		menu_selector(HelloWorld::restartTapped) );

	restartItem->setScale(0.1);
	restartItem->setPosition( ccp(winSize.width/2, winSize.height * 0.6));

	//add menu
	CCMenu* menu = CCMenu::create(restartItem, NULL);
	menu->setPosition(CCPointZero);
	this->addChild(menu);

	restartItem->runAction(CCScaleTo::create(0.5, 1.0) );
	label->runAction(CCScaleTo::create(0.5, 1.0) );

	this->unscheduleUpdate();



}