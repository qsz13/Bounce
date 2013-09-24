/*
 * EnlargeItem.cpp
 *
 *  Created on: Sep 23, 2013
 *      Author: daniel
 */

#include "EnlargeItem.h"

EnlargeItem::EnlargeItem() {
	// TODO Auto-generated constructor stub

}

EnlargeItem::~EnlargeItem() {
	// TODO Auto-generated destructor stub
}

EnlargeItem* EnlargeItem::getEnlargeItem(){

	EnlargeItem* enlargeItem =new EnlargeItem();
	if(enlargeItem && enlargeItem->initWithFile("CloseNormal.png")){
		//enlargeItem->myInit();
		//enlargeItem->autorelease();
			return enlargeItem;
	}
	CC_SAFE_DELETE(enlargeItem);
	return NULL;
}
