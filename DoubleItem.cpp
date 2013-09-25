/*
 * DoubleItem.cpp
 *
 *  Created on: Sep 25, 2013
 *      Author: daniel
 */

#include "DoubleItem.h"

DoubleItem::DoubleItem() {
	function = "double";
}

DoubleItem::~DoubleItem() {
	// TODO Auto-generated destructor stub
}


DoubleItem* DoubleItem::getDoubleItem(){

	DoubleItem* doubleItem =new DoubleItem();
	if(doubleItem && doubleItem->initWithFile("GameLayer/Items/doubleItem.png")){
		doubleItem -> setScale(0.5);
		return doubleItem;
	}
	CC_SAFE_DELETE(doubleItem);
	return NULL;
}

