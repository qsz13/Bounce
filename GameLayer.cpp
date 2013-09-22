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

// on "init" you need to initialize your instance
bool GameLayer::init()
{

    if ( !CCLayer::init() )
    {
        return false;
    }

    
    if(SettingLayer::getControlMode()==0){
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
    b2Vec2 v = b2Vec2(ball->getVelocity(),ball->getVelocity());
    ball->getBallBody()->SetLinearVelocity(v);







//my paddle;
    myPaddle = MyPaddle::getMyPaddle();
    this->addChild(myPaddle,1);
    myPaddle->setPosition(ccp(winSize.width/2,myPaddle->getTextureRect().getMidY()));


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
    enemyPaddle->setPosition(ccp(winSize.width/2,winSize.height-enemyPaddle->getTextureRect().getMidY()));



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
    //schedule(schedule_selector(HelloWorld::kick), 5);

    return true;
}

// void GameLayer::menuCloseCallback(CCObject* pSender)
// {
//     CCDirector::sharedDirector()->end();

// #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//     exit(0);
// #endif
// }

void GameLayer::doStep(float delta)
{

    world->Step(delta, 10, 10);
    for(b2Body *b = world->GetBodyList(); b; b=b->GetNext()) {
        if (b->GetUserData() != NULL) {
            CCSprite *sprite = (CCSprite *)b->GetUserData();
            sprite->setPosition(ccp(b->GetPosition().x * PTM_RATIO,b->GetPosition().y * PTM_RATIO));

            

        }
    }
    enemyPaddle->move(ball);

	if(!gameIsEnded){
		Ball *ball= (Ball*)this->getChildByTag(0);
        if(ball->getPosition().y<0){
        	//CCLOG("!!!!!");
//                  char temp[30];
//                  sprintf(temp,"%f",sprite->getPosition().y);
//                    CCLOG(temp);
            CCLabelTTF *label = CCLabelTTF::create("you lose","",123);
            label->setPosition(ccp(winSize.width/2,winSize.height/2));
            addChild(label,1,0);
            gameIsEnded = true;
            //ball->removeFromParentAndCleanup(true);
        }
        else if(ball->getPosition().y > winSize.height){
            CCLabelTTF *label = CCLabelTTF::create("you win","",123);
            label->setPosition(ccp(winSize.width/2,winSize.height*3/4));
            addChild(label,1,0);
            gameIsEnded = true;
           // ball->removeFromParentAndCleanup(true);
            
        }
        restart();
    }

}




void GameLayer::restart(){
    if(gameIsEnded){
        CCSprite *restartButton = CCSprite::create("restart.png");
        restartButton->setScale(0.4);
        this->addChild(restartButton,2,0);
        restartButton->setPosition(ccp(winSize.width/2,winSize.height/4));

    }



}







 void GameLayer::ccTouchesBegan(CCSet *pTouches,CCEvent *event)
 {
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
  
 void GameLayer::ccTouchesMoved(CCSet *pTouches, CCEvent* event)
 {
     CCTouch* myTouch = (CCTouch*)pTouches->anyObject();
 
      CCPoint location = myTouch->getLocationInView();
      location = CCDirector::sharedDirector()->convertToGL(location);
      b2Vec2 locationWorld = b2Vec2(location.x/PTM_RATIO, location.y/PTM_RATIO);
      if (_mouseJoint)   //判断 否则会找不到  然后报错
          _mouseJoint->SetTarget(locationWorld);
      
 }
  
 void GameLayer::ccTouchesEnded(CCSet *pTouches,CCEvent* event)
 {
     if (_mouseJoint)  //判断 否则会找不到  然后报错
     {
         world->DestroyJoint(_mouseJoint);   //摧毁关节
         _mouseJoint = NULL;
     }
     
 }


 void GameLayer::didAccelerate(CCAcceleration* pAccelerationValue)
 {
     b2Vec2 gravity(pAccelerationValue->x * 500,pAccelerationValue->y * 00);
     world->SetGravity(gravity);
 }


