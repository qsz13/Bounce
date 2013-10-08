/*
 * ShortenItem.h
 *
 *  Created on: Sep 26, 2013
 *      Author: daniel
 */

#ifndef SHORTENITEM_H_
#define SHORTENITEM_H_

#include "cocos2d.h"
#include "Item.h"
using namespace cocos2d;

class ShortenItem: public Item {
public:
	ShortenItem();
	virtual ~ShortenItem();
	static ShortenItem* createShortenItem();

};

#endif /* SHORTENITEM_H_ */
