/***************************************************************************
*
* ___GameOverScene.cpp___
* ___Chapter2___
*
* Created by ___NguyenHoangPhuong___ on ___25/7/2013___.
*
* Copyright Vinova Pte. Ltd. All rights reserved.
***************************************************************************
*/

#include "GameOverScene.h"
#include "HelloWorldScene.h"

using namespace cocos2d;

bool GameOverScene::init()
{
	if( CCScene::init() )
	{
		this->mLayer = GameOverLayer::create();
		this->mLayer->retain();
		this->addChild(mLayer);

		return true;

	}	
	else
	{
		return false;
	}
}



GameOverScene::~GameOverScene()
{
	if (mLayer)
	{
		mLayer->release();
		mLayer = NULL;
	}
}

bool GameOverLayer::init()
{
	if ( CCLayerColor::initWithColor ( ccc4(255, 255, 255, 255) ))
	{
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		this->mLabel = CCLabelTTF::create("", "Artial", 32);
		mLabel->retain();
		mLabel->setColor( ccc3(0, 0, 0) );
		mLabel->setPosition(ccp(winSize.width/2, winSize.height/2));
		this->addChild(mLabel);

		this->runAction( CCSequence::create(
			CCDelayTime::create(3),
			CCCallFunc::create(this,
			callfunc_selector(GameOverLayer::gameOverDone)),
			NULL));

		return true;
	}
	else
	{
		return false;
	}
}

void GameOverLayer::gameOverDone()
{
	CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}

GameOverLayer::~GameOverLayer()
{
	if(mLabel)
	{
		mLabel->release();
		mLabel = NULL;
	}
}


