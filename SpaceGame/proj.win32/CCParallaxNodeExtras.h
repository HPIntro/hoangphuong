/***************************************************************************
*
* ___CCParallaxNodeExtras.h___
* ___SpaceGame___
*
* Created by ___NguyenHoangPhuong___ on ___25/07/2013___.
*
* Copyright Vinova Pte. Ltd. All rights reserved.
***************************************************************************
*/

#ifndef Cocos2DxFirstIosSample_CCParallaxNodeExtras_h
#define Cocos2DxFirstIosSample_CCParallaxNodeExtras_h

#include "cocos2d.h"



USING_NS_CC;

class CCParallaxNodeExtras : public CCParallaxNode
{
public:
	CCParallaxNodeExtras();

	static CCParallaxNodeExtras* node();

	void incrementOffset(CCPoint pOffset, CCNode* pNode); 
};
#endif
