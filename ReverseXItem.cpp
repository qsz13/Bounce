/*
 * ReverseXItem.cpp
 *
 *  Created on: Sep 25, 2013
 *      Author: daniel
 */

#include "ReverseXItem.h"

ReverseXItem::ReverseXItem() {
	function = "reverseX";

}

ReverseXItem::~ReverseXItem() {
	// TODO Auto-generated destructor stub
}


ReverseXItem* ReverseXItem::getReverseXItem(){

	ReverseXItem* reverseXItem =new ReverseXItem();
	if(reverseXItem && reverseXItem->initWithFile("GameLayer/Items/reverseXItem.png")){
		reverseXItem -> setScale(0.3);
		return reverseXItem;
	}
	CC_SAFE_DELETE(reverseXItem);
	return NULL;
}