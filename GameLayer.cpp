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

    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
    "CloseNormal.png",
    "CloseSelected.png",
    this,
    menu_selector(GameLayer::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    ball = Ball::getBall();
    this->addChild(ball, 0);
    ball->setPosition(ccp(winSize.width/2,winSize.height/2));


    myPaddle = MyPaddle::getMyPaddle();
    this->addChild(myPaddle);
    myPaddle->setPosition(ccp(winSize.width/2,myPaddle->getTextureRect().getMidY()));

    enemyPaddle = EnemyPaddle::getEnemyPaddle();
    this->addChild(enemyPaddle);
    enemyPaddle->setPosition(ccp(winSize.width/2,winSize.height-enemyPaddle->getTextureRect().getMidY()));

    b2Vec2 gravity(0.0f, -8.0f);
    world = new b2World(gravity);



    b2BodyDef ballBodyDef;
    ballBodyDef.type = b2_dynamicBody;
    ballBodyDef.position.Set(ball->getPosition().x/PTM_RATIO, ball->getPosition().y/PTM_RATIO);
    ballBodyDef.userData = ball;
    b2Body *ballBody = world->CreateBody(&ballBodyDef);


    b2FixtureDef ballFixtureDef;
    b2CircleShape circle;
    circle.m_radius = ball->getTextureRect().getMaxY()/2/PTM_RATIO;

    ballFixtureDef.shape = &circle;
    ballFixtureDef.density = 1.0f;
    ballFixtureDef.friction = 0.2f;
    ballFixtureDef.restitution = 0.8f;

    ballBody->CreateFixture(&ballFixtureDef);








    b2BodyDef paddleBodyDef;
      paddleBodyDef.type = b2_dynamicBody;
      paddleBodyDef.position.Set(500/PTM_RATIO,500/PTM_RATIO);
      paddleBodyDef.userData = myPaddle;

    world->CreateBody(myPaddle->getBodyDef());






    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0,0);


    b2Body *groundBody = world->CreateBody(&groundBodyDef);
    b2EdgeShape groundEdge;

    b2FixtureDef boxShapeDef;
    boxShapeDef.shape = &groundEdge;

    //wall definitions
    //bottom
    groundEdge.Set(b2Vec2(0,0), b2Vec2(winSize.width /PTM_RATIO, 0));
    groundBody->CreateFixture(&boxShapeDef);

    // left
    groundEdge.Set(b2Vec2(0,0), b2Vec2(0,winSize.height/PTM_RATIO));
    groundBody->CreateFixture(&boxShapeDef);

    // top
    groundEdge.Set(b2Vec2(0, winSize.height/PTM_RATIO),
    b2Vec2(winSize.width/PTM_RATIO, winSize.height/PTM_RATIO));
    groundBody->CreateFixture(&boxShapeDef);

    // right
    groundEdge.Set(b2Vec2(winSize.width/PTM_RATIO, winSize.height/PTM_RATIO),
    b2Vec2(winSize.width/PTM_RATIO, 0));
    groundBody->CreateFixture(&boxShapeDef);





    schedule(schedule_selector(GameLayer::doStep));
    //schedule(schedule_selector(HelloWorld::kick), 5);

    return true;
}

void GameLayer::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void GameLayer::doStep(float delta)
{

    world->Step(delta, 10, 10);
    for(b2Body *b = world->GetBodyList(); b; b=b->GetNext()) {
        if (b->GetUserData() != NULL) {
            CCSprite *ballData = (CCSprite *)b->GetUserData();
            ballData->setPosition(ccp(b->GetPosition().x * PTM_RATIO,
            b->GetPosition().y * PTM_RATIO));
            ballData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
        }
    }
}
