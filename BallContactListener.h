/*
 * BallContactListener.h
 *
 *  Created on: Sep 28, 2013
 *      Author: daniel
 */

#ifndef BALLCONTACTLISTENER_H_
#define BALLCONTACTLISTENER_H_
#include "Box2D.h"


class BallContactListener : public b2ContactListener{
private:
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
};


#endif /* BALLCONTACTLISTENER_H_ */
