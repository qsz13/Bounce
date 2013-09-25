/*
 * EnlargeItem.cpp
 *
 *  Created on: Sep 23, 2013
 *      Author: daniel
 */

#include "EnlargeItem.h"

EnlargeItem::EnlargeItem() {
	function = "enlarge";

}

EnlargeItem::~EnlargeItem() {
	// TODO Auto-generated destructor stub
}

EnlargeItem* EnlargeItem::getEnlargeItem(){

	EnlargeItem* enlargeItem =new EnlargeItem();
<<<<<<< HEAD
	if(enlargeItem && enlargeItem->initWithFile("enlargeItem.png")){
=======
	if(enlargeItem && enlargeItem->initWithFile("GameLayer/Items/enlargeItem.png")){
>>>>>>> hst
		enlargeItem->setScale(0.2);
		//enlargeItem->autorelease();
		return enlargeItem;
	}
	CC_SAFE_DELETE(enlargeItem);
	return NULL;
}

