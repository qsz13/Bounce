/*
 * ShortenItem.cpp
 *
 *  Created on: Sep 26, 2013
 *      Author: daniel
 */

#include "ShortenItem.h"

ShortenItem::ShortenItem() {
	function = "shorten";

}

ShortenItem::~ShortenItem() {
	// TODO Auto-generated destructor stub
}

ShortenItem* ShortenItem::getShortenItem(){

	ShortenItem* shortenItem =new ShortenItem();
	if(shortenItem && shortenItem->initWithFile("GameLayer/Items/shortenItem.png")){
		shortenItem->setScale(0.2);
		//shortenItem->autorelease();
		return shortenItem;
	}
	CC_SAFE_DELETE(shortenItem);
	return NULL;
}
