#include "GameLayer.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

GameLayer* GameLayer::layer;
Ball* GameLayer::ball;
Ball* GameLayer::ghostBall;
MyPaddle* GameLayer::myPaddle;
EnemyPaddle* GameLayer::enemyPaddle;

CCScene* GameLayer::scene() {
	CCScene *scene = CCScene::create();
	layer = GameLayer::create();
	scene->addChild(layer);
	return scene;
}

GameLayer* GameLayer::getLayer() {
	return layer;
}

void GameLayer::initBackground() {
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	//Background
	CCSprite* gameLayerBackground = CCSprite::create(
			"GameLayer/GameSceneBackground.png");
	gameLayerBackground->setPosition(ccp(size.width / 2, size.height / 2));
	this->addChild(gameLayerBackground, 0);
}

void GameLayer::initTopBar() {

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	//Pause Button
	CCMenuItemImage *pauseButtonImage = CCMenuItemImage::create(
			"GameLayer/Pause.png", "GameLayer/Pause_Pressed.png", this,
			menu_selector(GameLayer::pause));
	pauseButtonImage->setPosition(ccp(0, 0));
	pauseButton = CCMenu::create(pauseButtonImage, NULL);
	pauseButton->setPosition(ccp(size.width / 4, size.height + 50));
	this->addChild(pauseButton, 3);

	//Scores Label
	scoresLabel = CCSprite::create("GameLayer/ScoresLabel.png");
	scoresLabel->setPosition(ccp(size.width * 3 / 4, size.height + 50));
	this->addChild(scoresLabel, 3);

	//Scores
	char temp[10];
	sprintf(temp, "%d", ScoreData::getScore());
	scores = CCLabelTTF::create(temp, "Designer-Notes.ttf", 65);
	scores->setPosition(ccp(size.width * 3 / 4 + 80, size.height + 65));
	this->addChild(scores, 3);
}

bool GameLayer::init() {
	initBackground();
	initTopBar();
	if (ScoreData::gameIsOver) {
		ScoreData::setScoreTo0();
	}
	ghostBall = NULL;
	freezeMode = false;
	gameIsPaused = true;
	gameIsEnded = false;
	isSkweing = false;
	ScoreData::gameIsOver = false;
	newGame = true;
	srand (time(NULL));setKeypadEnabled
	(true);
	setTouchPriority(kCCMenuHandlerPriority + 1);
	if (!CCLayer::init()) {
		return false;
	}

	if (SettingLayer::getControlMode() == SettingLayer::GRAVITY) {
		setAccelerometerEnabled(true);
		setTouchEnabled(false);

	} else {
		setTouchEnabled(true);
		setAccelerometerEnabled(false);
	}

	winSize = CCDirector::sharedDirector()->getWinSize();

	b2Vec2 gravity(0.0f, 0.0f);
	world = new b2World(gravity);

	BallContactListener* contactListener = new BallContactListener();
	world->SetContactListener(contactListener);

	buildGround();
	buildBall();
	buildMyPaddle();
	buildEnemyPaddle();
	restrictPaddleMovement();

	schedule(schedule_selector(GameLayer::doStep));
	schedule(schedule_selector(GameLayer::dropItem));
	schedule(schedule_selector(GameLayer::itemIntersects));
	schedule(schedule_selector(GameLayer::paddleTimer));
	schedule(schedule_selector(GameLayer::ghostBallTimer));
	schedule(schedule_selector(GameLayer::freezeTimer));
	schedule(schedule_selector(GameLayer::skewTimer));

	return true;
}

void GameLayer::onEnterTransitionDidFinish() {

	CCLayer::onEnterTransitionDidFinish();
	if (SettingLayer::getControlMode() == SettingLayer::GRAVITY) {
		setAccelerometerEnabled(true);
		setTouchEnabled(false);

	} else {
		setTouchEnabled(true);
		setAccelerometerEnabled(false);
		b2Vec2 gravity(0, 0);
		world->SetGravity(gravity);
	}

	CCActionInterval* actionTo1 = CCMoveTo::create(0.3,
			ccp(winSize.width / 4, winSize.height - 50));
	CCActionInterval* actionTo2 = CCMoveTo::create(0.4,
			ccp(winSize.width * 3 / 4, winSize.height - 50));
	CCActionInterval* actionTo3 = CCMoveTo::create(0.5,
			ccp(winSize.width * 3 / 4 + 80, winSize.height - 65));
	pauseButton->runAction(actionTo1);
	scoresLabel->runAction(actionTo2);
	scores->runAction(actionTo3);

	ball->runAction(CCSequence::create(CCFadeIn::create(1.0f), NULL));
	myPaddle->runAction(CCSequence::create(CCFadeIn::create(1.0f), NULL));
	enemyPaddle->runAction(CCSequence::create(CCFadeIn::create(1.0f), NULL));
	if (ghostBall != NULL) {
		ghostBall->runAction(CCSequence::create(CCFadeIn::create(1.0f), NULL));
	}

	if (!itemList.empty()) {

		for (list<Item *>::iterator it = itemList.begin(); it != itemList.end();
				it++) {
			(*it)->runAction(CCSequence::create(CCFadeIn::create(1.0f), NULL));
		}

	}

	if (newGame) {
		if (ScoreData::gameIsOver) {
			ScoreData::setScoreTo0();
			scores->setString("0");
		}
		countDown();
	} else {
		resume();
	}

}

void GameLayer::countDown() {

	CCSprite *countDown3 = CCSprite::create(
			"GameLayer/CountDown/countDown3.png");
	CCSprite *countDown2 = CCSprite::create(
			"GameLayer/CountDown/countDown2.png");
	CCSprite *countDown1 = CCSprite::create(
			"GameLayer/CountDown/countDown1.png");
	countDown3->setPosition(ccp(winSize.width / 2, winSize.height - 542));
	countDown2->setPosition(ccp(winSize.width / 2, winSize.height - 542));
	countDown1->setPosition(ccp(winSize.width / 2, winSize.height - 542));
	this->addChild(countDown3);
	this->addChild(countDown2);
	this->addChild(countDown1);
	countDown3->setOpacity(0);
	countDown2->setOpacity(0);
	countDown1->setOpacity(0);
	CCActionInterval* fadeIn = CCFadeIn::create(0.5f);
	countDown3->runAction(
			CCSequence::create(fadeIn, CCDelayTime::create(0.5),
					CCFadeOut::create(0.0f), NULL));
	countDown2->runAction(
			CCSequence::create(CCDelayTime::create(1), fadeIn,
					CCDelayTime::create(0.5), CCFadeOut::create(0.0f), NULL));
	countDown1->runAction(
			CCSequence::create(CCDelayTime::create(2), fadeIn,
					CCDelayTime::create(0.5), CCFadeOut::create(0.0f),
					CCCallFunc::create(this,
							callfunc_selector(GameLayer::resume)), NULL));
}

void GameLayer::buildGround() {
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);

	groundBody = world->CreateBody(&groundBodyDef);
	b2EdgeShape groundEdge;

	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;

	//wall definitions
	// left
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(0, winSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	// right
	groundEdge.Set(
			b2Vec2(winSize.width / PTM_RATIO, winSize.height / PTM_RATIO),
			b2Vec2(winSize.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

}

void GameLayer::buildBall() {
	ball = Ball::createBall();
	ball->setTag(0);
	ball->setPosition(ccp(winSize.width / 2, (winSize.height - 100) / 2));
	ball->setOpacity(0);
	this->addChild(ball, 2, 0);

	//ball body
	b2BodyDef ballBodyDef;
	ballBodyDef.type = b2_dynamicBody;
	ballBodyDef.position.Set(ball->getPosition().x / PTM_RATIO,
			ball->getPosition().y / PTM_RATIO);
	ballBodyDef.userData = ball;
	ballBodyDef.gravityScale = 0.0f;
	ball->setBallBody(world->CreateBody(&ballBodyDef));
	ball->getBallBody()->SetUserData(ball);
//circle shape

	b2CircleShape circle;
	circle.m_radius = ball->getRadius() / PTM_RATIO;

//ball shape
	b2FixtureDef ballFixtureDef;
	ballFixtureDef.shape = &circle;
	ballFixtureDef.density = 1.0f;
	ballFixtureDef.friction = 0.0f;
	ballFixtureDef.restitution = 1.0f;
	b2Fixture *ballFixture = ball->getBallBody()->CreateFixture(
			&ballFixtureDef);
	b2Vec2 v = b2Vec2(ball->getVelocity().x, ball->getVelocity().y);
	ball->getBallBody()->SetLinearVelocity(v);

}

void GameLayer::buildMyPaddle() {

//my paddle;
	myPaddle = MyPaddle::createMyPaddle();
	myPaddle->setTag(1);
	myPaddle->setPosition(
			ccp(winSize.width / 2, myPaddle->getTextureRect().getMidY() + 50));
	myPaddle->setOpacity(0);
	this->addChild(myPaddle, 2, 1);

//my paddle body
	b2BodyDef myPaddleBodyDef;
	myPaddleBodyDef.type = b2_dynamicBody;
	myPaddleBodyDef.position.Set(myPaddle->getPosition().x / PTM_RATIO,
			myPaddle->getPosition().y / PTM_RATIO);
	myPaddleBodyDef.userData = myPaddle;
	myPaddle->setMyPaddleBody(world->CreateBody(&myPaddleBodyDef));

//my paddle fixture
	b2FixtureDef myPaddleFixtureDef;
	b2PolygonShape myPaddleShape;
	myPaddleShape.SetAsBox(myPaddle->getWidth() / 2 / PTM_RATIO,
			myPaddle->getHeight() / 2 / PTM_RATIO);
	myPaddleFixtureDef.shape = &myPaddleShape;
	myPaddleFixtureDef.density = 10.0f;
	myPaddleFixtureDef.friction = 0.4f;
	myPaddleFixtureDef.restitution = 0.02f;

	myPaddleFixture = myPaddle->getMyPaddleBody()->CreateFixture(
			&myPaddleFixtureDef);

}

void GameLayer::buildEnemyPaddle() {

//enemy paddle;
	enemyPaddle = EnemyPaddle::createEnemyPaddle();

	enemyPaddle->setOpacity(0);
	enemyPaddle->setPosition(ccp(winSize.width / 2, winSize.height - 150));
	this->addChild(enemyPaddle, 2);

//enemy paddle body
	b2BodyDef enemyPaddleBodyDef;
	enemyPaddleBodyDef.type = b2_dynamicBody;
	enemyPaddleBodyDef.position.Set(enemyPaddle->getPosition().x / PTM_RATIO,
			enemyPaddle->getPosition().y / PTM_RATIO);
	enemyPaddleBodyDef.userData = enemyPaddle;
	enemyPaddleBodyDef.gravityScale = 0.0f;
	enemyPaddle->setEnemyPaddleBody(world->CreateBody(&enemyPaddleBodyDef));

//enemy paddle fixture
	b2FixtureDef enemyPaddleFixtureDef;
	b2PolygonShape enemyPaddleShape;
	enemyPaddleShape.SetAsBox(enemyPaddle->getWidth() / 2 / PTM_RATIO,
			enemyPaddle->getHeight() / 2 / PTM_RATIO);
	enemyPaddleFixtureDef.shape = &enemyPaddleShape;
	enemyPaddleFixtureDef.density = 10.0f;
	enemyPaddleFixtureDef.friction = 0.4f;
	enemyPaddleFixtureDef.restitution = 0.02f;
	enemyPaddleFixture = enemyPaddle->getEnemyPaddleBody()->CreateFixture(
			&enemyPaddleFixtureDef);

}

void GameLayer::restrictPaddleMovement() {
	//restrict paddle's movement
	b2PrismaticJointDef jointDef;
	b2Vec2 worldAxis(1.0f, 0.0f);
	jointDef.collideConnected = true;
	jointDef.Initialize(myPaddle->getMyPaddleBody(), groundBody,
			myPaddle->getMyPaddleBody()->GetWorldCenter(), worldAxis);
	world->CreateJoint(&jointDef);
	jointDef.Initialize(enemyPaddle->getEnemyPaddleBody(), groundBody,
			enemyPaddle->getEnemyPaddleBody()->GetWorldCenter(), worldAxis);
	world->CreateJoint(&jointDef);

}

Ball* GameLayer::getBall() {
	return ball;
}
Ball* GameLayer::getGhostBall() {
	return ghostBall;
}
MyPaddle* GameLayer::getMyPaddle() {
	return myPaddle;
}
EnemyPaddle* GameLayer::getEnemyPaddle() {
	return enemyPaddle;
}

void GameLayer::doStep(float delta) {
	if (!gameIsPaused) {

		world->Step(delta, 10, 10);
		for (b2Body *b = world->GetBodyList(); b; b = b->GetNext()) {
			if (b->GetUserData() != NULL) {
				CCSprite *sprite = (CCSprite *) b->GetUserData();
				sprite->setPosition(
						ccp(b->GetPosition().x * PTM_RATIO,
								b->GetPosition().y * PTM_RATIO));
				b2Fixture* f = b->GetFixtureList();
				switch (f->GetType()) {
				case b2Shape::e_circle: {
					b2CircleShape* circle = (b2CircleShape*) f->GetShape();
				}
					break;

				case b2Shape::e_polygon: {
					b2PolygonShape* poly = (b2PolygonShape*) f->GetShape();
					CCRect rect = sprite->boundingBox();
					poly->SetAsBox(rect.size.width / 2 / PTM_RATIO,
							rect.size.height / 2 / PTM_RATIO);
				}
					break;
				}

			}
		}

		enemyPaddle->move(ball, ghostBall);
		char temp[10];
		sprintf(temp, "%d", ScoreData::getScore());
		scores->setString(temp);
		avoidUnwantedSituation();

		if (!gameIsEnded) {
			if (ball->getPosition().y < -ball->getHeight() / 2) {

				CCSprite *bg = CCSprite::create(
						"GameLayer/Continue & Restart/RestartBackground.png");
				bg->setPosition(ccp(winSize.width / 2, winSize.height / 2));
				this->addChild(bg, 1, 0);
				gameIsEnded = true;
				newGame = false;
				ScoreData::gameIsOver = true;
				setHighScore();
				ball->removeFromParentAndCleanup(true);
				if (ghostBall != NULL) {
					ghostBall->removeFromParentAndCleanup(true);
					ghostBall = NULL;
				}
			} else if (ball->getPosition().y
					> winSize.height - 100 + ball->getHeight() / 2) {
				CCSprite *bg = CCSprite::create(
						"GameLayer/Continue & Restart/ContinueBackground.png");
				bg->setPosition(ccp(winSize.width / 2, winSize.height / 2));
				this->addChild(bg, 1, 0);
				gameIsEnded = true;
				ScoreData::gameIsOver = false;

				newGame = false;
				ScoreData::winRound();
				ball->removeFromParentAndCleanup(true);
				if (ghostBall != NULL) {
					ghostBall->removeFromParentAndCleanup(true);
					ghostBall = NULL;
				}
			}

			if (ghostBall != NULL) {
				if (ghostBall->getPosition().y < ball->getHeight() / 2) {

					CCSprite *bg =
							CCSprite::create(
									"GameLayer/Continue & Restart/RestartBackground.png");
					bg->setPosition(ccp(winSize.width / 2, winSize.height / 2));
					this->addChild(bg, 1, 0);
					gameIsEnded = true;
					setHighScore();
					newGame = false;
					ScoreData::gameIsOver = true;
					ball->removeFromParentAndCleanup(true);
				} else if (ghostBall->getPosition().y
						> winSize.height - 100 + ball->getHeight() / 2) {
					ScoreData::winRound();
					CCSprite *bg =
							CCSprite::create(
									"GameLayer/Continue & Restart/ContinueBackground.png");
					bg->setPosition(ccp(winSize.width / 2, winSize.height / 2));
					this->addChild(bg, 1, 0);
					gameIsEnded = true;
					ScoreData::gameIsOver = false;
					newGame = false;
					ball->removeFromParentAndCleanup(true);

				}
			}
			restartConfirm();
		}

	} else {
		char temp[10];
		sprintf(temp, "%d", ScoreData::getScore());
		scores->setString(temp);
	}

}

void GameLayer::restartConfirm() {
	if (gameIsEnded) {

		if (ScoreData::gameIsOver) {
			CCMenuItemImage *restartButton = CCMenuItemImage::create(
					"GameLayer/Continue & Restart/Restart.png",
					"GameLayer/Continue & Restart/Restart_Pressed.png", this,
					menu_selector(GameLayer::restart));
			restartButton->setPosition(ccp(0, 0));
			CCMenu* pMenusSetting = CCMenu::create(restartButton, NULL);
			pMenusSetting->setPosition(
					ccp(winSize.width / 2, winSize.height - 789.5));
			this->addChild(pMenusSetting, 1);

		} else {
			CCMenuItemImage *restartButton = CCMenuItemImage::create(
					"GameLayer/Continue & Restart/Continue.png",
					"GameLayer/Continue & Restart/Continue_Pressed.png", this,
					menu_selector(GameLayer::restart));
			restartButton->setPosition(ccp(0, 0));
			CCMenu* pMenusSetting = CCMenu::create(restartButton, NULL);
			pMenusSetting->setPosition(
					ccp(winSize.width / 2, winSize.height - 789.5));
			this->addChild(pMenusSetting, 1);
		}
	}
}

void GameLayer::restart() {
	CCDirector::sharedDirector()->replaceScene(GameLayer::scene());
	newGame = true;
}

void GameLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *event) {
	if (SettingLayer::getControlMode() == SettingLayer::DRAG) {
		if (_mouseJoint != NULL)
			return;

		CCTouch *myTouch = (CCTouch*) pTouches->anyObject();
		CCPoint location = myTouch->getLocationInView();

		location = CCDirector::sharedDirector()->convertToGL(location);
		b2Vec2 locationWorld = b2Vec2(location.x / PTM_RATIO,
				location.y / PTM_RATIO);

		if (myPaddleFixture->TestPoint(locationWorld)) {
			b2MouseJointDef md;
			md.bodyA = groundBody;
			md.bodyB = myPaddle->getMyPaddleBody();
			md.target = locationWorld;
			md.collideConnected = true;
			md.maxForce = 1000.0f * myPaddle->getMyPaddleBody()->GetMass();
			_mouseJoint = (b2MouseJoint *) world->CreateJoint(&md);
		}
	} else if (SettingLayer::getControlMode() == SettingLayer::TOUCH) {
		CCTouch *myTouch = (CCTouch*) pTouches->anyObject();
		CCPoint touchPosition = myTouch->getLocation();
		if (touchPosition.x < winSize.width / 2) {
			b2Vec2 v = b2Vec2(-20, 0);
			myPaddle->getMyPaddleBody()->SetLinearVelocity(v);
		} else {
			b2Vec2 v = b2Vec2(20, 0);
			myPaddle->getMyPaddleBody()->SetLinearVelocity(v);
		}

	}

}

void GameLayer::ccTouchesMoved(CCSet *pTouches, CCEvent* event) {
	if (SettingLayer::getControlMode() == SettingLayer::DRAG) {

		CCTouch* myTouch = (CCTouch*) pTouches->anyObject();

		CCPoint location = myTouch->getLocationInView();
		location = CCDirector::sharedDirector()->convertToGL(location);
		b2Vec2 locationWorld = b2Vec2(location.x / PTM_RATIO,
				location.y / PTM_RATIO);
		if (_mouseJoint) 
			_mouseJoint->SetTarget(locationWorld);
	} else if (SettingLayer::getControlMode() == SettingLayer::TOUCH) {
		CCTouch *myTouch = (CCTouch*) pTouches->anyObject();
		CCPoint touchPosition = myTouch->getLocation();
		if (touchPosition.x < winSize.width / 2) {
			b2Vec2 v = b2Vec2(-20, 0);
			myPaddle->getMyPaddleBody()->SetLinearVelocity(v);
		} else {
			b2Vec2 v = b2Vec2(20, 0);
			myPaddle->getMyPaddleBody()->SetLinearVelocity(v);
		}
	}

}

void GameLayer::ccTouchesEnded(CCSet *pTouches, CCEvent* event) {
	if (SettingLayer::getControlMode() == SettingLayer::DRAG) {
		if (_mouseJoint)
		{
			world->DestroyJoint(_mouseJoint);
			_mouseJoint = NULL;
		}
	} else if (SettingLayer::getControlMode() == SettingLayer::TOUCH) {
		b2Vec2 v = b2Vec2(0, 0);
		myPaddle->getMyPaddleBody()->SetLinearVelocity(v);
	}
}

void GameLayer::didAccelerate(CCAcceleration* pAccelerationValue) {

	if (pAccelerationValue->x > 0.03) {
		b2Vec2 v = b2Vec2(0.08 * SettingLayer::getSensitivity(), 0);
		myPaddle->getMyPaddleBody()->SetLinearVelocity(v);
	} else if (pAccelerationValue->x < -0.03) {
		b2Vec2 v = b2Vec2(-0.08 * SettingLayer::getSensitivity(), 0);
		myPaddle->getMyPaddleBody()->SetLinearVelocity(v);
	} else {
		b2Vec2 v = b2Vec2(0, 0);
		myPaddle->getMyPaddleBody()->SetLinearVelocity(v);
	}
}

void GameLayer::dropItem() {

	int drop = rand() % 300;

	if (!gameIsEnded && !gameIsPaused && itemList.size() < MAX_ITEM) {
		if (drop == 0) {
			int type = rand() % 8;
			if (type == 0) {
				item = EnlargeItem::createEnlargeItem();

			} else if (type == 1) {
				item = ReverseXItem::createReverseXItem();
			} else if (type == 2) {
				item = DoubleItem::createDoubleItem();
			} else if (type == 3) {
				item = ReverseYItem::createReverseYItem();
			} else if (type == 4) {
				item = FreezeItem::createFreezeItem();
			} else if (type == 5) {
				item = ShortenItem::createShortenItem();
			} else if (type == 6) {
				item = StealthItem::createStealthItem();
			} else if (type <= 7) {
				item = SkewingItem::createSkewingItem();
			}

			while (true) {

				int x = 40 + rand() % ((int) winSize.width - 80);
				int y = (winSize.height - 100) / 2 - 350 + rand() % 700;
				item->setPosition(ccp(x, y));
				bool positionCorrect = true;

				if (!itemList.empty()) {

					for (list<Item *>::iterator it = itemList.begin();
							it != itemList.end(); it++) {

						if ((*it)->rect().intersectsRect(item->rect())) {
							positionCorrect = false;
							break;
						}
					}
					if (positionCorrect) {
						break;
					}
				} else {
					break;
				}

			}
			addChild(item, 1, 0);
			itemList.push_back(item);

		}
	}
}

void GameLayer::itemIntersects() {

	if (!gameIsEnded && !gameIsPaused && itemList.size() > 0) {

		for (list<Item *>::iterator it = itemList.begin(); it != itemList.end();
				) {

			(*it)->frameAddOne();

			bool exrtaBallIntersects;
			if (ghostBall != NULL) {
				exrtaBallIntersects = (*it)->rect().intersectsRect(
						ghostBall->rect());
			} else {
				exrtaBallIntersects = false;
			}

			if ((*it)->getFrameLasted() > 600) {
				((*it)->removeFromParentAndCleanup(true));
				it = itemList.erase(it);
			} else if ((*it)->rect().intersectsRect(ball->rect())
					&& (*it)->getFrameLasted() > 20) {
				ScoreData::itemScore();
				if ((*it)->getFunction() == "enlarge") {
					enlargePaddle(ball);
				} else if ((*it)->getFunction() == "reverseX") {
					reverseBallXVelocity();
				} else if ((*it)->getFunction() == "reverseY") {
					reverseBallYVelocity();
				} else if ((*it)->getFunction() == "double") {
					doubleBall();
				} else if ((*it)->getFunction() == "freeze") {
					freezeBall();
				} else if ((*it)->getFunction() == "shorten") {
					shortenPaddle(ball);
				} else if ((*it)->getFunction() == "stealth") {
					stealthBall();
				} else if ((*it)->getFunction() == "magnet") {
					skewBall();
				}

				((*it)->removeFromParentAndCleanup(true));
				it = itemList.erase(it);

			} else {
				it++;
			}
		}

	}

}

void GameLayer::enlargePaddle(Ball* ball) {
	CCActionInterval* actionBy = CCScaleBy::create(0.5f, 2.0f, 1.0f);
	b2Vec2 v = ball->getBallBody()->GetLinearVelocity();
	CCRect myRect = myPaddle->boundingBox();
	CCRect enemyRect = enemyPaddle->boundingBox();
	if (v.y < 0) {
		if (enemyRect.size.width <= enemyPaddle->getWidth()) {
			enemyPaddle->runAction(actionBy);
			if (enemyPaddle->getLengthState() == Paddle::shortPaddle) {
				enemyPaddle->setLengthState(Paddle::normalPaddle);
			} else if (enemyPaddle->getLengthState() == Paddle::normalPaddle) {
				enemyPaddle->setLengthState(Paddle::longPaddle);
			}
		}
	}

	else if (v.y > 0) {

		if (myRect.size.width <= myPaddle->getWidth()) {
			myPaddle->runAction(actionBy);
			if (myPaddle->getLengthState() == Paddle::shortPaddle) {
				myPaddle->setLengthState(Paddle::normalPaddle);
			} else if (myPaddle->getLengthState() == Paddle::normalPaddle) {
				myPaddle->setLengthState(Paddle::longPaddle);
			}
		}
	}
}

void GameLayer::shortenPaddle(Ball *ball) {
	CCActionInterval* actionBy = CCScaleBy::create(0.5f, 0.5f, 1.0f);
	b2Vec2 v = ball->getBallBody()->GetLinearVelocity();
	CCRect myRect = myPaddle->boundingBox();
	CCRect enemyRect = enemyPaddle->boundingBox();
	if (v.y > 0) {
		if (enemyRect.size.width >= enemyPaddle->getWidth()) {
			enemyPaddle->runAction(actionBy);
			enemyPaddle->setFrameLastedTo0();
			if (enemyPaddle->getLengthState() == Paddle::normalPaddle) {
				enemyPaddle->setLengthState(Paddle::shortPaddle);
			} else if (enemyPaddle->getLengthState() == Paddle::longPaddle) {
				enemyPaddle->setLengthState(Paddle::normalPaddle);
			}
		}
	} else if (v.y < 0) {

		if (myRect.size.width >= myPaddle->getWidth()) {
			myPaddle->runAction(actionBy);
			myPaddle->setFrameLastedTo0();
			if (myPaddle->getLengthState() == Paddle::normalPaddle) {
				myPaddle->setLengthState(Paddle::shortPaddle);
			} else if (myPaddle->getLengthState() == Paddle::longPaddle) {
				myPaddle->setLengthState(Paddle::normalPaddle);
			}
		}
	}
}

void GameLayer::paddleTimer() {
	if (!gameIsPaused) {

		if (myPaddle->getLengthState() == Paddle::longPaddle) {
			CCActionInterval* shortenActionBy = CCScaleBy::create(0.5f, 0.5f,
					1.0f);
			if (myPaddle->getFrameLasted() > 600) {
				myPaddle->setFrameLastedTo0();
				myPaddle->setLengthState(Paddle::normalPaddle);
				myPaddle->runAction(shortenActionBy);
			} else {
				myPaddle->frameAddOne();

			}

		} else if (myPaddle->getLengthState() == Paddle::shortPaddle) {
			CCActionInterval* enlargeActionBy = CCScaleBy::create(0.5f, 2.0f,
					1.0f);
			if (myPaddle->getFrameLasted() > 600) {
				myPaddle->setFrameLastedTo0();
				myPaddle->setLengthState(Paddle::normalPaddle);
				myPaddle->runAction(enlargeActionBy);
			} else {
				myPaddle->frameAddOne();

			}

		}

		if (enemyPaddle->getLengthState() == Paddle::longPaddle) {
			CCActionInterval* shortenActionBy = CCScaleBy::create(0.5f, 0.5f,
					1.0f);
			if (enemyPaddle->getFrameLasted() > 600) {
				enemyPaddle->setFrameLastedTo0();
				enemyPaddle->setLengthState(Paddle::normalPaddle);
				enemyPaddle->runAction(shortenActionBy);
			} else {
				enemyPaddle->frameAddOne();

			}

		} else if (enemyPaddle->getLengthState() == Paddle::shortPaddle) {
			CCActionInterval* enlargeActionBy = CCScaleBy::create(0.5f, 2.0f,
					1.0f);
			if (enemyPaddle->getFrameLasted() > 600) {
				enemyPaddle->setFrameLastedTo0();
				enemyPaddle->setLengthState(Paddle::normalPaddle);
				enemyPaddle->runAction(enlargeActionBy);
			} else {
				enemyPaddle->frameAddOne();

			}

		}

	}

}

void GameLayer::reverseBallXVelocity() {
	b2Vec2 v = ball->getBallBody()->GetLinearVelocity();
	v.x = -v.x;
	ball->getBallBody()->SetLinearVelocity(v);

}

void GameLayer::reverseBallYVelocity() {

	b2Vec2 v = ball->getBallBody()->GetLinearVelocity();
	v.y = -v.y;
	ball->getBallBody()->SetLinearVelocity(v);

}


void GameLayer::avoidUnwantedSituation() {
	b2Vec2 bv = ball->getBallBody()->GetLinearVelocity();

	float bs = bv.x * bv.x + bv.y * bv.y;

	if (!freezeMode) {
		if (bs < 225) {
			b2Vec2 *bf = new b2Vec2(bv.x, bv.y);
			ball->getBallBody()->ApplyForceToCenter(*bf);
		}
	}

	if (bs > 1000) {
		b2Vec2 *bf = new b2Vec2(-bv.x * 10, -bv.y * 10);

		ball->getBallBody()->ApplyForceToCenter(*bf);
	}

	if (ghostBall != NULL) {
		b2Vec2 gv = ghostBall->getBallBody()->GetLinearVelocity();
		float gs = gv.x * gv.x + gv.y * gv.y;
		if (gs < 225) {
			b2Vec2 *gf = new b2Vec2(gv.x, gv.y);
			ghostBall->getBallBody()->ApplyForceToCenter(*gf);
		}

		else if (bs > 1000) {
			b2Vec2 *gf = new b2Vec2(-gv.x, -gv.y);

			ghostBall->getBallBody()->ApplyForceToCenter(*gf);
		}
	}

	if (bv.y * bv.y < bs / 4) {
		if (bv.y < 0) {
			bv.y = -sqrt(bs) / 2;
		} else {
			bv.y = sqrt(bs) / 2;
		}

		if (bv.x < 0) {
			bv.x = -sqrt(bs - bv.y * bv.y);
		} else {
			bv.x = sqrt(bs - bv.y * bv.y);
		}

	}

	ball->getBallBody()->SetLinearVelocity(bv);

}

void GameLayer::doubleBall() {
	if (ghostBall == NULL) {
		ghostBall = Ball::createGhostBall();
		ghostBall->setTag(0);
		this->addChild(ghostBall, 2, 0);
		ghostBall->setPosition(ccp(winSize.width / 2, winSize.height / 2));

		b2BodyDef ballBodyDef;
		ballBodyDef.type = b2_dynamicBody;
		ballBodyDef.position.Set(ghostBall->getPosition().x / PTM_RATIO,
				ghostBall->getPosition().y / PTM_RATIO);
		ballBodyDef.userData = ghostBall;
		ballBodyDef.gravityScale = 0.0f;
		ghostBall->setBallBody(world->CreateBody(&ballBodyDef));
		ghostBall->getBallBody()->SetUserData(ghostBall);
//circle shape

		b2CircleShape circle;
		circle.m_radius = ghostBall->getRadius() / PTM_RATIO;

//ball shape
		b2FixtureDef ballFixtureDef;
		ballFixtureDef.shape = &circle;
		ballFixtureDef.density = 1.0f;
		ballFixtureDef.friction = 0.0f;
		ballFixtureDef.restitution = 1.0f;
		b2Fixture *ballFixture = ghostBall->getBallBody()->CreateFixture(
				&ballFixtureDef);
		b2Vec2 v = b2Vec2(ghostBall->getVelocity().x,
				ghostBall->getVelocity().y);
		ghostBall->getBallBody()->SetLinearVelocity(v);

	}

}

void GameLayer::freezeBall() {
	if (!freezeMode) {
		b2Vec2 bv = ball->getBallBody()->GetLinearVelocity();
		velocityBeforeFrozen = bv;
		bv.x = 0.2 * bv.x;
		bv.y = 0.2 * bv.y;
		ball->getBallBody()->SetLinearVelocity(bv);
		freezeMode = true;
	}

}

void GameLayer::ghostBallTimer() {

	if (!gameIsPaused) {
		if (ghostBall != NULL) {
			if (ghostBall->getFrameLasted() > 600) {
				ghostBall->removeFromParentAndCleanup(true);
				ghostBall = NULL;
			} else {
				ghostBall->frameAddOne();
			}
		}
	}

}

void GameLayer::stealthBall() {
	CCActionInterval* fadeOut = CCFadeOut::create(2.0f);
	CCActionInterval* fadeOutBack = fadeOut->reverse();

	ball->runAction(
			CCSequence::create(fadeOut, fadeOutBack, fadeOut, fadeOutBack,
					NULL));

}

void GameLayer::freezeTimer() {
	if (!gameIsPaused) {
		if (freezeMode) {
			if (ball->getFrozenFrameLasted() > 200) {
				b2Vec2 currentVelocity =
						ball->getBallBody()->GetLinearVelocity();
				float previousSpeed = velocityBeforeFrozen.x
						* velocityBeforeFrozen.x
						+ velocityBeforeFrozen.y * velocityBeforeFrozen.y;
				float currentSpeed = currentVelocity.x * currentVelocity.x
						+ currentVelocity.y * currentVelocity.y;
				float rate = sqrt(previousSpeed / currentSpeed);
				b2Vec2 newVelocity = ball->getBallBody()->GetLinearVelocity();
				newVelocity.x = currentVelocity.x * rate;
				newVelocity.y = currentVelocity.y * rate;
				ball->getBallBody()->SetLinearVelocity(newVelocity);
				ball->setFrozenFrameTo0();
				freezeMode = false;
			} else {
				ball->frozenFrameAddOne();
			}

		}

	}
}

void GameLayer::skewBall() {
	isSkweing = true;
	if (rand() & 1) {
		skewDirectionIsRight = true;
	} else {
		skewDirectionIsRight = false;
	}
}

void GameLayer::skewTimer() {
	if (!gameIsPaused) {
		if (isSkweing) {
			if (ball->getSkewFrameLasted() > 30) {
				isSkweing = false;
				ball->setSkewFrameLastedTo0();
			} else {
				b2Vec2 v = ball->getBallBody()->GetLinearVelocity();

				b2Vec2 *f;
				if (skewDirectionIsRight) {
					f = new b2Vec2(-v.y, v.x);
				} else {
					f = new b2Vec2(v.y, -v.x);
				}

				(*f) *= 15;
				ball->getBallBody()->ApplyForceToCenter(*f);
				ball->skewFrameAddOne();
			}

		}
	}
}

void GameLayer::pause() {
	if (!gameIsPaused) {
		gameIsPaused = true;
		CCActionInterval* actionTo1 = CCMoveTo::create(0.3,
				ccp(winSize.width / 4, winSize.height + 50));
		CCActionInterval* actionTo2 = CCMoveTo::create(0.3,
				ccp(winSize.width * 3 / 4, winSize.height + 50));
		CCActionInterval* actionTo3 = CCMoveTo::create(0.3,
				ccp(winSize.width * 3 / 4 + 80, winSize.height + 65));

		pauseButton->runAction(actionTo1);
		scoresLabel->runAction(actionTo2);
		scores->runAction(
				CCSequence::create(actionTo3,
						CCCallFunc::create(this,
								callfunc_selector(GameLayer::pushToPauseLayer)),
						NULL));

		ball->runAction(CCSequence::create(CCFadeOut::create(0.3f), NULL));
		myPaddle->runAction(CCSequence::create(CCFadeOut::create(0.3f), NULL));
		enemyPaddle->runAction(
				CCSequence::create(CCFadeOut::create(0.3f), NULL));
		if (ghostBall != NULL) {
			ghostBall->runAction(
					CCSequence::create(CCFadeOut::create(0.3f), NULL));
		}
		if (!itemList.empty()) {

			for (list<Item *>::iterator it = itemList.begin();
					it != itemList.end(); it++) {
				(*it)->runAction(
						CCSequence::create(CCFadeOut::create(0.3f), NULL));
			}

		}

	}
}

void GameLayer::pushToPauseLayer() {
	CCDirector::sharedDirector()->pushScene(PauseLayer::scene());
}

void GameLayer::resume() {
	if (gameIsPaused) {
		gameIsPaused = false;
	}
}

void GameLayer::keyBackClicked() {

	pause();

}

void GameLayer::setHighScore() {


	if (ScoreData::getScore() > ScoreData::highScore) {
		CCUserDefault::sharedUserDefault()->setIntegerForKey("HighScore",
				ScoreData::getScore());
		ScoreData::highScore = ScoreData::getScore();

	}

}

