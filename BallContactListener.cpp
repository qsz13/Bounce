/*
 * BallContactListener.cpp
 *
 *  Created on: Sep 28, 2013
 *      Author: daniel
 */

#include "BallContactListener.h"
#include "cocos2d.h"
using namespace cocos2d;

void BallContactListener::BeginContact(b2Contact* contact) {
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();
	if (bodyA->GetUserData() != NULL && bodyB->GetUserData() != NULL) {
		CCSprite* spriteA = (CCSprite*) bodyA->GetUserData();
		CCSprite* spriteB = (CCSprite*) bodyB->GetUserData();
		if ((spriteA->getTag() == 0 && spriteB->getTag() == 1)
				|| (spriteA->getTag() == 1 && spriteB->getTag() == 0)) {
			ScoreData::defendScore();

		}
	}
}

void BallContactListener::EndContact(b2Contact* contact) {

}

