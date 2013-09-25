/*
 * ReverseItem.cpp
 *
 *  Created on: Sep 25, 2013
 *      Author: daniel
 */

#include "ReverseItem.h"

ReverseItem::ReverseItem() {
	function = "reverse";

}

ReverseItem::~ReverseItem() {
	// TODO Auto-generated destructor stub
}


ReverseItem* ReverseItem::getReverseItem(){

	ReverseItem* enlargeItem =new ReverseItem();
	if(enlargeItem && enlargeItem->initWithFile("reverseItem.png")){
		//enlargeItem->myInit();
		//enlargeItem->autorelease();
			return enlargeItem;
	}
	CC_SAFE_DELETE(enlargeItem);
	return NULL;
}
