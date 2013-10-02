/*
 * ScrollLayer.h
 *
 *  Created on: Sep 29, 2013
 *      Author: daniel
 */

#ifndef SCROLLLAYER_H_
#define SCROLLLAYER_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "HelpLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;


class ScrollLayer : public cocos2d::CCLayer ,public CCScrollViewDelegate{
public:
	ScrollLayer();
	virtual ~ScrollLayer();

	bool init();
	CREATE_FUNC(ScrollLayer);

//scrollview滚动的时候会调用
	void scrollViewDidScroll(CCScrollView* view);

//scrollview缩放的时候会调用
	void scrollViewDidZoom(CCScrollView* view);

	virtual void onEnter();
	virtual void onExit();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);





private:

//根据手势滑动的距离和方向滚动图层
	 void adjustScrollView(float offset);
	 CCScrollView *m_pScrollView;
	 CCPoint m_touchPoint;
	 int m_nCurPage;

	

};

#endif /* SCROLLLAYER_H_ */
