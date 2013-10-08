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
}

ShortenItem* ShortenItem::createShortenItem() {

	ShortenItem* shortenItem = new ShortenItem();
	if (shortenItem
			&& shortenItem->initWithFile("GameLayer/Items/shortenItem.png")) {
		return shortenItem;
	}
	CC_SAFE_DELETE(shortenItem);
	return NULL;
}
