/*
 * Item.cpp
 *
 *  Created on: Sep 23, 2013
 *      Author: daniel
 */

#include "Item.h"

int Item::itemNum = 0;

Item::Item() {
	// TODO Auto-generated constructor stub

}

Item::~Item() {
	// TODO Auto-generated destructor stub
}

CCRect Item::rect(){

	CCSize s = this->getContentSize();
	return CCRectMake(this->getPosition().x, this->getPosition().y, s.width/2, s.height/2);
	 
}
       
