#include "GameLayer.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* GameLayer::scene()
{
    CCScene *scene = CCScene::create();
    GameLayer *layer = GameLayer::create();
    scene->addChild(layer);
    return scene;
}


void GameLayer::initBackground()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    //Background
    // 创建图片精灵
    CCSprite* gameLayerBackground = CCSprite::create("GameLayer/GameSceneBackground.png");

    // 设置图片精灵的位置
    gameLayerBackground->setPosition(ccp(size.width/2, size.height/2));

    // 把图片精灵放置在图层中
    this->addChild(gameLayerBackground, 0);
}

void GameLayer::initTopBar()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();

    //Pause Button
    CCMenuItemImage *pauseButtonImage = CCMenuItemImage::create(
                                                          "GameLayer/Pause.png",
                                                          "GameLayer/Pause_Pressed.png",
                                                          this,
                                                          menu_selector(GameLayer::pause));
    pauseButtonImage -> setPosition( ccp(0, 0) );

    CCMenu* pauseButton = CCMenu::create(pauseButtonImage, NULL);
    pauseButton -> setPosition( ccp(size.width / 4, size.height - 50) );
    this -> addChild(pauseButton, 1);

    //Scores Label
    // 创建图片精灵
    CCSprite* scoresLabel = CCSprite::create("GameLayer/ScoresLabel.png");

    // 设置图片精灵的位置
    scoresLabel->setPosition(ccp(size.width*3/4, size.height - 50));

    // 把图片精灵放置在图层中
    this->addChild(scoresLabel, 1);
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{
    initBackground();
    initTopBar();

    extraBall = NULL;

    srand(time(NULL));
    if ( !CCLayer::init() )
    {
        return false;
    }


    if(SettingLayer::getControlMode()==SettingLayer::GRAVITY){
        setAccelerometerEnabled(true);
        setTouchEnabled(false);

    }
    else //if(SettingLayer::getControlMode()==1||
         //   SettingLayer::getControlMode()= 0;)
    {
        setTouchEnabled(true);
        setAccelerometerEnabled(false);
    }


    gameIsPaused = false;
    winSize = CCDirector::sharedDirector()->getWinSize();


    b2Vec2 gravity(0.0f, 0.0f);
    world = new b2World(gravity);

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0,0);


    groundBody = world->CreateBody(&groundBodyDef);
    b2EdgeShape groundEdge;

    b2FixtureDef boxShapeDef;
    boxShapeDef.shape = &groundEdge;

     //wall definitions
     //bottom
    // groundEdge.Set(b2Vec2(0,0), b2Vec2(winSize.width /PTM_RATIO, 0));
    // groundBody->CreateFixture(&boxShapeDef);

     // left
     groundEdge.Set(b2Vec2(0,0), b2Vec2(0,winSize.height/PTM_RATIO));
     groundBody->CreateFixture(&boxShapeDef);

     // top
//     groundEdge.Set(b2Vec2(0, winSize.height/PTM_RATIO),
//     b2Vec2(winSize.width/PTM_RATIO, winSize.height/PTM_RATIO));
//     groundBody->CreateFixture(&boxShapeDef);

     // right
     groundEdge.Set(b2Vec2(winSize.width/PTM_RATIO, winSize.height/PTM_RATIO),
     b2Vec2(winSize.width/PTM_RATIO, 0));
     groundBody->CreateFixture(&boxShapeDef);




    ball = Ball::getBall();
    this->addChild(ball, 1,0);
    ball->setPosition(ccp(winSize.width/2,winSize.height/2));

    //ball body
    b2BodyDef ballBodyDef;
    ballBodyDef.type = b2_dynamicBody;
    ballBodyDef.position.Set(ball->getPosition().x/PTM_RATIO, ball->getPosition().y/PTM_RATIO);
    ballBodyDef.userData = ball;
    ballBodyDef.gravityScale = 0.0f;
    ball->setBallBody(world->CreateBody(&ballBodyDef));
    ball->getBallBody()->SetUserData(ball);
//circle shape

    b2CircleShape circle;
    circle.m_radius = ball->getRadius()/PTM_RATIO;

//ball shape
    b2FixtureDef ballFixtureDef;
    ballFixtureDef.shape = &circle;
    ballFixtureDef.density = 1.0f;
    ballFixtureDef.friction = 0.0f;
    ballFixtureDef.restitution = 1.0f;
    b2Fixture *ballFixture = ball->getBallBody()->CreateFixture(&ballFixtureDef);
    b2Vec2 v = b2Vec2(ball->getVelocity().x,ball->getVelocity().y);
    ball->getBallBody()->SetLinearVelocity(v);



//my paddle;
    myPaddle = MyPaddle::getMyPaddle();
    this->addChild(myPaddle,1);
    myPaddle->setPosition(ccp(winSize.width/2,myPaddle->getTextureRect().getMidY()+50));


//my paddle body
    b2BodyDef myPaddleBodyDef;
	myPaddleBodyDef.type = b2_dynamicBody;
	myPaddleBodyDef.position.Set(myPaddle->getPosition().x/PTM_RATIO,myPaddle->getPosition().y/PTM_RATIO);
	myPaddleBodyDef.userData = myPaddle;
	myPaddle->setMyPaddleBody( world->CreateBody(&myPaddleBodyDef));

//my paddle fixture
	b2FixtureDef myPaddleFixtureDef;
	b2PolygonShape myPaddleShape;
	myPaddleShape.SetAsBox(myPaddle->getWidth()/2/PTM_RATIO,myPaddle->getHeight()/2/PTM_RATIO);
	myPaddleFixtureDef.shape = &myPaddleShape;
	myPaddleFixtureDef.density = 10.0f;
	myPaddleFixtureDef.friction = 0.4f;
	myPaddleFixtureDef.restitution = 0.1f;

	myPaddleFixture = myPaddle->getMyPaddleBody()->CreateFixture(&myPaddleFixtureDef);





//enemy paddle;
    enemyPaddle = EnemyPaddle::getEnemyPaddle();
    this->addChild(enemyPaddle,1);
    enemyPaddle->setPosition(ccp(winSize.width/2,winSize.height-150));


//enemy paddle body
    b2BodyDef enemyPaddleBodyDef;
    enemyPaddleBodyDef.type = b2_dynamicBody;
    enemyPaddleBodyDef.position.Set(enemyPaddle->getPosition().x/PTM_RATIO,enemyPaddle->getPosition().y/PTM_RATIO);
    enemyPaddleBodyDef.userData = enemyPaddle;
    enemyPaddleBodyDef.gravityScale = 0.0f;
    enemyPaddle->setEnemyPaddleBody(world->CreateBody(&enemyPaddleBodyDef));

//enemy paddle fixture
    b2FixtureDef enemyPaddleFixtureDef;
    b2PolygonShape enemyPaddleShape;
    enemyPaddleShape.SetAsBox(enemyPaddle->getWidth()/2/PTM_RATIO,enemyPaddle->getHeight()/2/PTM_RATIO);
    enemyPaddleFixtureDef.shape = &enemyPaddleShape;
    enemyPaddleFixtureDef.density = 10.0f;
    enemyPaddleFixtureDef.friction = 0.4f;
    enemyPaddleFixtureDef.restitution = 0.1f;
   // enemyPaddleFixtureDef.gravityScale = 0.0f;
    enemyPaddleFixture = enemyPaddle->getEnemyPaddleBody()->CreateFixture(&enemyPaddleFixtureDef);




//restrict paddle's movement
    b2PrismaticJointDef jointDef;
    b2Vec2 worldAxis(1.0f, 0.0f);
    jointDef.collideConnected =true;
    jointDef.Initialize(myPaddle->getMyPaddleBody(), groundBody,
    myPaddle->getMyPaddleBody()->GetWorldCenter(), worldAxis);
    world->CreateJoint(&jointDef);

    jointDef.Initialize(enemyPaddle->getEnemyPaddleBody(), groundBody,
            enemyPaddle->getEnemyPaddleBody()->GetWorldCenter(), worldAxis);
       world->CreateJoint(&jointDef);






    schedule(schedule_selector(GameLayer::doStep));
    schedule(schedule_selector(GameLayer::dropItem));
    schedule(schedule_selector(GameLayer::itemIntersects));
    schedule(schedule_selector(GameLayer::paddleTimer));
    schedule(schedule_selector(GameLayer::extraBallTimer));

    return true;
}



void GameLayer::doStep(float delta)
{

    world->Step(delta, 10, 10);
    for(b2Body *b = world->GetBodyList(); b; b=b->GetNext()) {
        if (b->GetUserData() != NULL) {
            CCSprite *sprite = (CCSprite *)b->GetUserData();
            sprite->setPosition(ccp(b->GetPosition().x * PTM_RATIO,b->GetPosition().y * PTM_RATIO));
            b2Fixture* f = b->GetFixtureList();
            switch (f->GetType())
            {
                case b2Shape::e_circle:
                {
                    b2CircleShape* circle = (b2CircleShape*) f->GetShape();
                    /* Do stuff with a circle shape */
                }
                break;

                case b2Shape::e_polygon:
                {
                    b2PolygonShape* poly = (b2PolygonShape*) f->GetShape();
                    CCRect rect = sprite->boundingBox();
                    poly->SetAsBox(rect.size.width/2/PTM_RATIO,rect.size.height/2/PTM_RATIO);

                }
                break;
            }

        }
    }



    enemyPaddle->move(ball,extraBall);

    avoidUnwantedSituation();

    avoidUnwantedSituation();

	if(!gameIsEnded){
		Ball *ball= (Ball*)this->getChildByTag(0);
        if(ball->getPosition().y<0){

            CCLabelTTF *label = CCLabelTTF::create("you lose","",123);
            label->setPosition(ccp(winSize.width/2,winSize.height/2));
            addChild(label,1,0);
            gameIsEnded = true;
            ball->removeFromParentAndCleanup(true);
            if(extraBall!=NULL){
            	extraBall->removeFromParentAndCleanup(true);
            	extraBall = NULL;
            }
        }
        else if(ball->getPosition().y > winSize.height){
            CCLabelTTF *label = CCLabelTTF::create("you win","",123);
            label->setPosition(ccp(winSize.width/2,winSize.height*3/4));
            addChild(label,1,0);
            gameIsEnded = true;
           ball->removeFromParentAndCleanup(true);
           if(extraBall!=NULL){
               extraBall->removeFromParentAndCleanup(true);
               extraBall = NULL;
           }
        }

        if(extraBall!=NULL){
            if(extraBall->getPosition().y<0){

            CCLabelTTF *label = CCLabelTTF::create("you lose","",123);
            label->setPosition(ccp(winSize.width/2,winSize.height/2));
            addChild(label,1,0);
            gameIsEnded = true;
            ball->removeFromParentAndCleanup(true);
        }
        else if(extraBall->getPosition().y > winSize.height){
            CCLabelTTF *label = CCLabelTTF::create("you win","",123);
            label->setPosition(ccp(winSize.width/2,winSize.height*3/4));
            addChild(label,1,0);
            gameIsEnded = true;
            ball->removeFromParentAndCleanup(true);

        }



        }
        restartConfirm();
    }

}


void GameLayer::restartConfirm(){
    if(gameIsEnded){
//        CCSprite *restartButton = CCSprite::create("restart.png");
//        restartButton->setScale(0.4);
//        this->addChild(restartButton,2,0);
//        restartButton->setPosition(ccp(winSize.width/2,winSize.height/4));
        CCMenuItemImage *restartButton = CCMenuItemImage::create( "GameLayer/restart.png",
				  "GameLayer/restart.png",
				  this,
				  menu_selector(GameLayer::restart));
        restartButton -> setPosition( ccp(0, 0) );
        CCMenu* pMenusSetting = CCMenu::create(restartButton, NULL);
        	pMenusSetting -> setPosition(ccp(winSize.width/2,winSize.height/4));
        	this -> addChild(pMenusSetting, 1);

    }

}


void GameLayer::restart(){
   //Item::itemNum = 0;

	CCDirector::sharedDirector()->replaceScene(GameLayer::scene());

}










 void GameLayer::ccTouchesBegan(CCSet *pTouches,CCEvent *event)
 {
    if(SettingLayer::getControlMode()==SettingLayer::DRAG){
		   if (_mouseJoint != NULL) return;

		 CCTouch *myTouch = (CCTouch*)pTouches->anyObject();
		 CCPoint location = myTouch->getLocationInView();

	  location = CCDirector::sharedDirector()->convertToGL(location);
		 b2Vec2 locationWorld = b2Vec2(location.x/PTM_RATIO, location.y/PTM_RATIO);

		 if (myPaddleFixture->TestPoint(locationWorld)) {
		 b2MouseJointDef md;
		 md.bodyA = groundBody;
		 md.bodyB = myPaddle->getMyPaddleBody();
		 md.target = locationWorld;
		 md.collideConnected =true;
		 md.maxForce =1000.0f*myPaddle->getMyPaddleBody()->GetMass();
		 _mouseJoint = (b2MouseJoint *)world->CreateJoint(&md);
		 }
    }
    else if(SettingLayer::getControlMode()==SettingLayer::TOUCH){
    	 CCTouch *myTouch = (CCTouch*)pTouches->anyObject();
    	CCPoint touchPosition = myTouch->getLocation();
    	if(touchPosition.x < winSize.width/2){
          b2Vec2 v = b2Vec2(-20,0);
    	    myPaddle->getMyPaddleBody()->SetLinearVelocity(v);
    	}
    	else{
    		 b2Vec2 v = b2Vec2(20,0);
          myPaddle->getMyPaddleBody()->SetLinearVelocity(v);
    	}



    }

 }

 void GameLayer::ccTouchesMoved(CCSet *pTouches, CCEvent* event)
 {
	 if(SettingLayer::getControlMode()==SettingLayer::DRAG){

     CCTouch* myTouch = (CCTouch*)pTouches->anyObject();

      CCPoint location = myTouch->getLocationInView();
      location = CCDirector::sharedDirector()->convertToGL(location);
      b2Vec2 locationWorld = b2Vec2(location.x/PTM_RATIO, location.y/PTM_RATIO);
      if (_mouseJoint)   //判断 否则会找不到  然后报错
          _mouseJoint->SetTarget(locationWorld);
	 }else if(SettingLayer::getControlMode()==SettingLayer::TOUCH){
		 CCTouch *myTouch = (CCTouch*)pTouches->anyObject();
		 CCPoint touchPosition = myTouch->getLocation();
		 if(touchPosition.x < winSize.width/2){
	    		 b2Vec2 v = b2Vec2(-20,0);
          myPaddle->getMyPaddleBody()->SetLinearVelocity(v);
	    	}
	    	else{
	    		 b2Vec2 v = b2Vec2(20,0);
          myPaddle->getMyPaddleBody()->SetLinearVelocity(v);
	    	}
	 }

 }

 void GameLayer::ccTouchesEnded(CCSet *pTouches,CCEvent* event)
 {
	 if(SettingLayer::getControlMode()==SettingLayer::DRAG){
     if (_mouseJoint)  //判断 否则会找不到  然后报错
     {
         world->DestroyJoint(_mouseJoint);   //摧毁关节
         _mouseJoint = NULL;
     }
	 }
   else if(SettingLayer::getControlMode()==SettingLayer::TOUCH){
         b2Vec2 v = b2Vec2(0,0);
          myPaddle->getMyPaddleBody()->SetLinearVelocity(v);
    }
 }


 void GameLayer::didAccelerate(CCAcceleration* pAccelerationValue)
 {
     b2Vec2 gravity(pAccelerationValue->x * 100,pAccelerationValue->y * 100);
     world->SetGravity(gravity);
 }



void GameLayer::dropItem(){

    int drop = rand()%6;

    if(!gameIsEnded && !gameIsPaused && itemList.size() < MAX_ITEM){
         if(drop ==0){
            int type= rand()%4;
            if(type == 0){
            	item = EnlargeItem::getEnlargeItem();

            }
            else if(type == 1){
            	item = ReverseXItem::getReverseXItem();
            }
            else if(type == 2){
              item = DoubleItem::getDoubleItem();
            }
            else if(type == 3){
            	item = ReverseYItem::getReverseYItem();
            }

            int x=rand()%(int)winSize.width;
            int y=340+rand()%700;
            item->setPosition(ccp(x,y));
            addChild(item,1,0);
            itemList.push_back(item);
            //Item::itemNum++;
        }
    }
}




void GameLayer::itemIntersects() {

	if (!gameIsEnded && !gameIsPaused && itemList.size() > 0) {

		for (list<Item *>::iterator it = itemList.begin(); it != itemList.end();) {

			(*it)->frameAddOne();
			if ((*it)->getFrameLasted() > 600) {
				CCLOG("remove");
				((*it)->removeFromParentAndCleanup(true));
				it = itemList.erase(it);
			} else if ((*it)->rect().intersectsRect(ball->rect()) && (*it)->getFrameLasted()>10) {

				if ((*it)->getFunction() == "enlarge") {
					enlargePaddle(ball);
				} else if ((*it)->getFunction() == "reverseX") {
					reverseBallVelocity();
				} else if((*it)->getFunction() == "double"){
          doubleBall();
				}

				((*it)->removeFromParentAndCleanup(true));
				it = itemList.erase(it);

			} else {
				it++;
			}
		}

	}

}

//-------------------------- can be put in paddle class
void GameLayer::enlargePaddle(Ball* ball){
    CCActionInterval*  actionBy = CCScaleBy::create(0.5f, 2.0f, 1.0f);
    b2Vec2 v = ball->getBallBody()->GetLinearVelocity();
    CCRect myRect = myPaddle->boundingBox();
    CCRect enemyRect = enemyPaddle->boundingBox();
    if(v.y<0){

       if(enemyPaddle->getLengthState() == Paddle::shortPaddle
    		   && enemyRect.size.width <= enemyPaddle->getWidth()
    		   ){
        enemyPaddle->toggleLengthState();
        enemyPaddle->runAction(actionBy);

      }
      else{

      }
    }
    else if(v.y>0) {

      if(myPaddle->getLengthState() == Paddle::shortPaddle
    		  && myRect.size.width <= myPaddle->getWidth()
    		  ){
             myPaddle->toggleLengthState();
             myPaddle->runAction(actionBy);


      }
      else{

        //increase time
      }

     //actionBy release



    }

}


void GameLayer::paddleTimer(){

  if(myPaddle->getLengthState() == Paddle::longPaddle){
     CCActionInterval*  actionBy = CCScaleBy::create(0.5f, 0.5f, 1.0f);
    if(myPaddle->getFrameLasted() > 600){
      myPaddle->setFrameLastedTo0();
      myPaddle->toggleLengthState();
      myPaddle->runAction(actionBy);
    }
    else{
      myPaddle->frameAddOne();

    }

  }

  if(enemyPaddle->getLengthState() == Paddle::longPaddle){
     CCActionInterval*  actionBy = CCScaleBy::create(0.5f, 0.5f, 1.0f);
    if(enemyPaddle->getFrameLasted() > 600){
      enemyPaddle->setFrameLastedTo0();
      enemyPaddle->toggleLengthState();
      enemyPaddle->runAction(actionBy);
    }
    else{
      enemyPaddle->frameAddOne();

    }

  }

 // actionBy->autorelease();


}


void GameLayer::reverseBallVelocity(){
    b2Vec2 v = ball->getBallBody()->GetLinearVelocity();
    v.x = - v.x;
    CCLOG("reverse");
    ball->getBallBody()->SetLinearVelocity(v);

}


//===============================================================================

void GameLayer::avoidUnwantedSituation(){
    b2Vec2 v = ball->getBallBody()->GetLinearVelocity();
    float s = v.x*v.x + v.y*v.y;

    if(v.y*v.y  < s/4){
    	if(v.y < 0){
        	v.y = -sqrt(s)/2;
    	}
    	else{
    		v.y = sqrt(s)/2;
    	}

    	if(v.x < 0){
    		v.x = -sqrt(s-v.y*v.y);
    	}
    	else{
    		v.x = sqrt(s-v.y*v.y);
    	}


    }


    //if(s > )
//
//    if(v.y > 0 && v.y < 3){
//
//
//    	v.y += 3;
//    	if(v.x < 0){
//        	v.x = -sqrt(s-v.y*v.y);
//    	}
//    	else{
//    		(v.x = sqrt(s-v.y*v.y));
//    	}
//
//
//    }
//    else if(v.y >-3 && v.y < 0){
//
//        v.y -= 3;
//            	if(v.x < 0){
//                	v.x = -sqrt(s-v.y*v.y);
//            	}
//            	else{
//            		(v.x = sqrt(s-v.y*v.y));
//            	}
//    }
    ball->getBallBody()->SetLinearVelocity(v);

}


void GameLayer::doubleBall(){
  if(extraBall == NULL){
    extraBall = Ball::getBall();
  this->addChild(extraBall, 1,0);
  extraBall->setPosition(ccp(winSize.width/2,winSize.height/2));

  b2BodyDef ballBodyDef;
    ballBodyDef.type = b2_dynamicBody;
    ballBodyDef.position.Set(extraBall->getPosition().x/PTM_RATIO, extraBall->getPosition().y/PTM_RATIO);
    ballBodyDef.userData = extraBall;
    ballBodyDef.gravityScale = 0.0f;
    extraBall->setBallBody(world->CreateBody(&ballBodyDef));
    extraBall->getBallBody()->SetUserData(extraBall);
//circle shape

    b2CircleShape circle;
    circle.m_radius = extraBall->getRadius()/PTM_RATIO;

//ball shape
    b2FixtureDef ballFixtureDef;
    ballFixtureDef.shape = &circle;
    ballFixtureDef.density = 1.0f;
    ballFixtureDef.friction = 0.0f;
    ballFixtureDef.restitution = 1.0f;
    b2Fixture *ballFixture = extraBall->getBallBody()->CreateFixture(&ballFixtureDef);
    b2Vec2 v = b2Vec2(extraBall->getVelocity().x,extraBall->getVelocity().y);
    extraBall->getBallBody()->SetLinearVelocity(v);

  }


}

void GameLayer::extraBallTimer(){

  if(extraBall != NULL){
      if(extraBall->getFrameLasted() > 600){
    	  CCLOG("time out!!!");
      extraBall->removeFromParentAndCleanup(true);
      extraBall = NULL;
    }
    else{
      extraBall->frameAddOne();
    }


  }




}

void GameLayer::pause()
{
    //Empty for the time being
}
