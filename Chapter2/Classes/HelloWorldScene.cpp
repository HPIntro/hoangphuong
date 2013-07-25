#include "HelloWorldScene.h"
#include "proj.win32\GameOverScene.h"
//#include "GameOverScene.h"
#include "SimpleAudioEngine.h"



USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene* scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld* mLayer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(mLayer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
		"background-music-aac.wav", true);


	mTargets = new CCArray;
	mProjectiles = new CCArray;

	
    //////////////////////////////
	/*bool bRet= false;
	do
	{
		CC_BREAK_IF(! CCLayer::init());

		CCMenuItemImage* pCloseItem= CCMenuItemImage::create(
			"CloseNormal.png",
			"CloseSelected.png",
			this,
			menu_selector(HelloWorld::menuCloseCallback));
		
		CC_BREAK_IF(! pCloseItem);
		pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

		CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
		pMenu->setPosition(CCPointZero);
		CC_BREAK_IF(! pMenu);

		this->se
		this->addChild(pMenu, 1);

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCSprite *player= CCSprite::create("Player.png", CCRectMake(0, 0, 27, 40));
		
		player->setPosition( ccp(player->getContentSize().width/2, winSize.height/2) );
		this->addChild(player);

		bRet= true;
	} while (0);

	return bRet;*/

	if( !CCLayerColor::initWithColor(ccc4(255, 255, 255, 255)) )
	{
		return false;
	}

	if ( CCLayerColor::initWithColor(ccc4(255, 255, 255, 255)) )
	{
		CCSize winSize= CCDirector::sharedDirector()->getWinSize();
		CCSprite* player= CCSprite::create("Player.png", CCRectMake(0, 0, 27, 40) );
		player->setPosition( ccp(player->getContentSize().width/2, 
			winSize.height/2) );
		this->addChild(player);

		
	}
	
	this->setTouchEnabled(true);
	this->schedule( schedule_selector(HelloWorld::gameLogic), 1.0);
	this->schedule( schedule_selector(HelloWorld::update) );

    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::addTarget()
{
	//add targets to array


	CCSprite* target= CCSprite::create("Target.png",
		CCRectMake(0, 0, 27, 40) );
	target->setTag(1);
	mTargets->addObject(target);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	int minY = target->getContentSize().height/2;
	int maxY = winSize.height - 
		target->getContentSize().height/2;
	int rangeY = maxY - minY;

	int actualY = ( rand() % rangeY) + minY;

	target->setPosition(
		ccp(winSize.width + (target->getContentSize().width/2),
		actualY) );
	this->addChild(target);

	int minDuration = (int)2.0;
	int maxDuration = (int)4.0;
	int rangeDuration = maxDuration - minDuration;

	int actualDuration = ( rand() % rangeDuration )
		+minDuration;

	//create action
	CCFiniteTimeAction* actionMove = 
		CCMoveTo::create( (float)actualDuration, //actualDuration 
		ccp(0 - target->getContentSize().width/2, actualY) );
	CCFiniteTimeAction* actionMoveDone = 
		CCCallFuncN::create( this, 
		callfuncN_selector(HelloWorld::spriteMoveFinished));
	target->runAction( CCSequence::create(actionMove,
		actionMoveDone, NULL) );

}

void HelloWorld::spriteMoveFinished(CCNode* pSender)
{
	CCSprite* sprite = (CCSprite *)pSender;
	this->removeChild(sprite, true);

	if (sprite->getTag() == 1)
	{
	    // cpp with cocos2d-x
		GameOverScene *mGameOverScene = GameOverScene::create();
		mGameOverScene->getLayer()->getLabel()->setString("You Lose :)))");
		CCDirector::sharedDirector()->replaceScene(mGameOverScene);    
		mTargets->removeObject(sprite);
	}
	else if (sprite->getTag() == 2)
	{
		mProjectiles->removeObject(sprite);
	}
}

void HelloWorld::gameLogic(float pDt)
{
	this->addTarget();
}

void HelloWorld::ccTouchesEnded(CCSet* pTouches, CCEvent* pEvent)
{
	//music when fired
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
		"background-music-aac.wav", true);

	//touch
	CCTouch* touch = (CCTouch*)( pTouches->anyObject() );
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);

	//initial location for projectile
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite *projectile = CCSprite::create("Projectile.png",
		CCRectMake(0, 0, 20, 20));
	
    //add to projectiles array
	projectile->setTag(2);
	mProjectiles->addObject(projectile);

	projectile->setPosition( ccp(20, winSize.height/2) );

	//
	int offX = location.x - projectile->getPosition().x;
	int offY = location.y - projectile->getPosition().y;

	if (offX <= 0) return;

	this->addChild(projectile);

	int realX = winSize.width + (projectile->getContentSize().width/2);
	float ratio = (float)offY / (float)offX;
	int realY = (realX * ratio) + projectile->getPosition().y;
	CCPoint realDest = ccp(realX, realY);

	int offRealX = realX - projectile->getPosition().x;
	int offRealY = realY - projectile->getPosition().y;
	float length = sqrtf((offRealX * offRealX) + (offRealY * offRealY));

	float veloctiy = 480/1; //480pixels/1s
	float realMoveDuration = length/veloctiy;

	projectile ->runAction( CCSequence::create(
		CCMoveTo::create(realMoveDuration, realDest),
		CCCallFuncN::create(this, 
		callfuncN_selector(HelloWorld::spriteMoveFinished)), NULL) );



}

HelloWorld::~HelloWorld()
{
	if (mTargets)
	{
		mTargets->release();
		mTargets = NULL;
	}

	if(mProjectiles)
	{
		mProjectiles->release();
		mProjectiles = NULL;
	}
}
HelloWorld::HelloWorld()

	
	:mTargets(NULL)
	,mProjectiles(NULL)
{
	nProjectilesDestroyed = 0;
}

void HelloWorld::update(float pDt)
{
	CCArray* projectilesToDelete = new CCArray;
	CCArray* targetsToDelete     = new CCArray;
	CCObject* it = NULL;
	CCObject* jt = NULL;

	CCARRAY_FOREACH(mProjectiles, it)
	{
		CCSprite* projectile = dynamic_cast<CCSprite*>(it);
		CCRect projectileRect = CCRectMake(
			projectile->getPosition().x - (projectile->getContentSize().width/2),
			projectile->getPosition().y - (projectile->getContentSize().height/2),
			projectile->getContentSize().width,
			projectile->getContentSize().height);

		CCARRAY_FOREACH(mTargets, jt)
		{
			CCSprite* target = dynamic_cast<CCSprite*>(jt);
			CCRect    targetRect = CCRectMake(
				target->getPosition().x - (target->getContentSize().width/2),
				target->getPosition().y - (target->getContentSize().height/2),
				target->getContentSize().width,
				target->getContentSize().height);
			if (projectileRect.intersectsRect(targetRect))
			{
				targetsToDelete->addObject(target);
				projectilesToDelete->addObject(projectile);
			}
		}

	}

	CCARRAY_FOREACH(targetsToDelete, jt)
	{
		CCSprite* target = dynamic_cast<CCSprite*>(jt);
		mTargets->removeObject(target);
		this->removeChild(target, true);

		//diem
		nProjectilesDestroyed++;
		if (nProjectilesDestroyed >= 5)
		{
			GameOverScene* mGameOverScene = GameOverScene::create();
			mGameOverScene->getLayer()->getLabel()->setString("YOU WIN!");
			CCDirector::sharedDirector()->replaceScene(mGameOverScene);
		}
	}

	CCARRAY_FOREACH(projectilesToDelete, it)
	{
		CCSprite* projectile = dynamic_cast<CCSprite*>(it);
		mProjectiles->removeObject(projectile);
		this->removeChild(projectile, true);
	}

	projectilesToDelete->release();
	targetsToDelete->release();
}