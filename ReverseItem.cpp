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

	ReverseItem* reverseItem =new ReverseItem();
	if(reverseItem && reverseItem->initWithFile("reverseItem.png")){
		reverseItem -> setScale(0.3);
		return reverseItem;
	}
	CC_SAFE_DELETE(reverseItem);
	return NULL;
}
