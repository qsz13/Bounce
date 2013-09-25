/*
 * DoubleItem.cpp
 *
 *  Created on: Sep 25, 2013
 *      Author: daniel
 */

#include "DoubleItem.h"

DoubleItem::DoubleItem() {
	// TODO Auto-generated constructor stub

}

DoubleItem::~DoubleItem() {
	// TODO Auto-generated destructor stub
}


DoubleItem* DoubleItem::getDoubleItem(){

	DoubleItem* doubleItem =new DoubleItem();
	if(doubleItem && doubleItem->initWithFile("doubleItem.png")){
		doubleItem -> setScale(0.3);
		return doubleItem;
	}
	CC_SAFE_DELETE(doubleItem);
	return NULL;
}

