/*
 * ReverseYItem.cpp
 *
 *  Created on: Sep 25, 2013
 *      Author: daniel
 */

#include "ReverseYItem.h"

ReverseYItem::ReverseYItem() {
		function = "reverseY";
}

ReverseYItem::~ReverseYItem() {
	// TODO Auto-generated destructor stub
}

ReverseYItem* ReverseYItem::createReverseYItem(){

	ReverseYItem* reverseYItem =new ReverseYItem();
	if(reverseYItem && reverseYItem->initWithFile("GameLayer/Items/reverseYItem.png")){
		reverseYItem -> setScale(0.3);
		return reverseYItem;
	}
	CC_SAFE_DELETE(reverseYItem);
	return NULL;
}
