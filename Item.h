/*
 * Item.h
 *
 *  Created on: Sep 23, 2013
 *      Author: daniel
 */

#ifndef ITEM_H_
#define ITEM_H_

#include "cocos2d.h"
 #include <string>
#define PTM_RATIO 32.0


using namespace cocos2d;
using namespace std;
class Item :public CCSprite {
public:
	//static int itemNum;
	Item();
	virtual ~Item();

	CCRect rect();
	void frameAddOne();
	int getFrameLasted();
	string getFunction();
protected:
	int frameLasted;
	string function;


	//int MAX_ITEM = 3;
};

#endif /* ITEM_H_ */
