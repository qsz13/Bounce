#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D.h"
#include "Paddle.h"
#define PTM_RATIO 32.0

class HelloWorld : public cocos2d::CCLayer
{
public:
    virtual bool init();  

    static cocos2d::CCScene* scene();
    
    void menuCloseCallback(CCObject* pSender);

    CREATE_FUNC(HelloWorld);
    void tick(float dt);
    b2World *_world;
    b2Body *ball_body;
    b2Body *paddle_body;
    cocos2d::CCSprite *_ball;
    Paddle *_paddle;


};

#endif // __HELLOWORLD_SCENE_H__
