/*
 * FreezeItem.cpp
 *
 *  Created on: Sep 26, 2013
 *      Author: daniel
 */

#include "FreezeItem.h"

FreezeItem::FreezeItem() {
	function = "freeze";

}

FreezeItem::~FreezeItem() {
	// TODO Auto-generated destructor stub
}


FreezeItem* FreezeItem::getFreezeItem(){

	FreezeItem* freezeItem =new FreezeItem();
	if(freezeItem && freezeItem->initWithFile("GameLayer/Items/freezeItem.png")){
		freezeItem -> setScale(0.3);
		return freezeItem;
	}
	CC_SAFE_DELETE(freezeItem);
	return NULL;


}