#ifndef SQUID_BULLET_H
#define SQUID_BULLET_H

#include <algorithm>
#include <cmath>
#include <iostream>
#include "SquidBullet.h"

SquidBullet::SquidBullet() : Bullet(), lifetime(0), lifeLimit(0)
{ 
    setMoveSpeed(250);
    lifeLimit = (rand()/RAND_MAX)+0.5;
}
    


SquidBullet* SquidBullet::create(const cocos2d::Vec2& pos, const cocos2d::Vec2& dir) {
    // load in player image
    SquidBullet* pSprite = new SquidBullet();
    if(pSprite && pSprite->initWithFile("squidPart.png")) {
        pSprite->autorelease();
        pSprite->initOptions(pos, dir);
        pSprite->addEvents();
        return pSprite;
    }

    CC_SAFE_DELETE(pSprite);
    return NULL;
}

void SquidBullet::update(float dt) { 
    Bullet::update(dt);
    lifetime+=dt;
    if( lifetime > lifeLimit) {
        setVisible(false);
    }
}

void SquidBullet::addEvents() { }

void SquidBullet::initOptions(const cocos2d::Vec2& pos, const cocos2d::Vec2& dir) {

    int x = (pos.x-16) +(std::rand() % ((int)((pos.x - 16) - (pos.x +17))));
    int y = pos.y;

    setPosition(cocos2d::Vec2( x, y));
    setVelocity(dir*getMoveSpeed());

    // Schedule update
    schedule(schedule_selector(SquidBullet::update));
} 

#endif
