/*
 * Item.cpp
 *
 *  Created on: Sep 23, 2013
 *      Author: daniel
 */

#include "Item.h"

//int Item::itemNum = 0;

Item::Item() {
	frameLasted = 0;
}

Item::~Item() {
	
}

CCRect Item::rect() {
	CCSize s = this->boundingBox().size;
	return CCRectMake(this->getPosition().x - s.width / 2,
			this->getPosition().y - s.height / 2, s.width, s.height);

}

void Item::frameAddOne() {
	frameLasted++;
}

int Item::getFrameLasted() {
	return frameLasted;
}

string Item::getFunction() {
	return function;
}
