/***************************************************************************
*
* ___CCParallaxNodeExtras.cpp___
* ___SpaceGame___
*
* Created by ___NguyenHoangPhuong___ on ___25/07/2013___.
*
* Copyright Vinova Pte. Ltd. All rights reserved.
***************************************************************************
*/

#include "CCParallaxNodeExtras.h"

//Access CCPointObject
class CCPointObject  : CCObject {
    CC_SYNTHESIZE(CCPoint, m_tRatio, Ratio)
    CC_SYNTHESIZE(CCPoint, m_tOffset, Offset)
    CC_SYNTHESIZE(CCNode*, m_pChild, Child)	// weak ref
};
 
// Need to provide a constructor 
CCParallaxNodeExtras::CCParallaxNodeExtras() {
    CCParallaxNode(); // call parent constructor
}
 
CCParallaxNodeExtras* CCParallaxNodeExtras::node() {
    return new CCParallaxNodeExtras();       
}
 
void CCParallaxNodeExtras::incrementOffset(CCPoint pOffset,CCNode* pNode){
    for( unsigned int i = 0; i < m_pParallaxArray->num; i++) {
        CCPointObject *point = (CCPointObject *)m_pParallaxArray->arr[i];
        CCNode* curNode = point->getChild();
        if( curNode->isEqual(pNode) ) {
            point->setOffset( ccpAdd(point->getOffset(), pOffset) );
            break;
        }
    }
}