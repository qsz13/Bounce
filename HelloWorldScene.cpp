#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();

    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
    "CloseNormal.png",
    "CloseSelected.png",
    this,
    menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);



    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSprite* _ball = CCSprite::create("ball.png");
    this->addChild(_ball, 0);
    _ball->setPosition( ccp(500,500) );


    //MyPaddle *paddle = MyPaddle::create();
    //this->addChild(paddle,1);
    //paddle->setPosition(ccp(500,500));





    b2Vec2 gravity(0.0f, -8.0f);
    _world = new b2World(gravity);


    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0,0);


    b2Body *groundBody = _world->CreateBody(&groundBodyDef);
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



    b2BodyDef ballBodyDef;
    ballBodyDef.type = b2_dynamicBody;
    ballBodyDef.position.Set(500/PTM_RATIO, 500/PTM_RATIO);
    ballBodyDef.userData = _ball;
    ball_body = _world->CreateBody(&ballBodyDef);

   b2BodyDef paddleBodyDef;
   paddleBodyDef.type = b2_dynamicBody;
   paddleBodyDef.position.Set(500/PTM_RATIO,500/PTM_RATIO);
   ballBodyDef.userData = _paddle;
   paddle_body = _world->CreateBody(&paddleBodyDef);



    b2CircleShape circle;
    circle.m_radius = 150.0/PTM_RATIO;

    b2FixtureDef ballShapeDef;
    ballShapeDef.shape = &circle;
    ballShapeDef.density = 1.0f;
    ballShapeDef.friction = 0.2f;
    ballShapeDef.restitution = 0.8f;
    ball_body->CreateFixture(&ballShapeDef);

    schedule(schedule_selector(HelloWorld::tick));
    //schedule(schedule_selector(HelloWorld::kick), 5);

    //CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background-music-aac.wav", true);
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::tick(float dt)
{

    _world->Step(dt, 10, 10);
    for(b2Body *b = _world->GetBodyList(); b; b=b->GetNext()) {
        if (b->GetUserData() != NULL) {
            CCSprite *ballData = (CCSprite *)b->GetUserData();
            ballData->setPosition(ccp(b->GetPosition().x * PTM_RATIO,
            b->GetPosition().y * PTM_RATIO));
            ballData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
        }
    }
}
