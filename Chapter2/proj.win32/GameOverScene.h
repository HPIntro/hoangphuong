/***************************************************************************
*
* ___GameOverScene.h___
* ___Chapter2___
*
* Created by ___NguyenHoangPhuong___ on ___25/7/2013___.
*
* Copyright Vinova Pte. Ltd. All rights reserved.
***************************************************************************
*/

#ifndef _GAME_OVER_SCENE_H_
#define _GAME_OVER_SCENE_H_

#include "cocos2d.h"

class GameOverLayer : public cocos2d::CCLayerColor
{
public:
	GameOverLayer():mLabel(NULL){};
	virtual ~GameOverLayer();
	bool init();
	CREATE_FUNC(GameOverLayer);

	void gameOverDone();

	CC_SYNTHESIZE_READONLY(cocos2d::CCLabelTTF*, mLabel, Label);

};

class GameOverScene : public cocos2d::CCScene
{
public:
	GameOverScene():mLayer(NULL) {};
	~GameOverScene(void);
	bool init();
	CREATE_FUNC(GameOverScene);

	CC_SYNTHESIZE_READONLY(GameOverLayer*, mLayer, Layer);
};

#endif
