#include <algorithm>
#include <cmath>
#include <iostream>
#include "Squid.h"

Squid::Squid() :
    Enemy(),
    canShoot(true)
{ 
    setMoveSpeed(100);
}

Squid* Squid::create(const cocos2d::Vec2& pos, const cocos2d::Vec2& dir) {
    // load in player image
    Squid* pSprite = new Squid();
    if(pSprite && pSprite->initWithFile("enemy.png")) {
        pSprite->autorelease();
        pSprite->initOptions(pos, dir);
        pSprite->addEvents();
        return pSprite;
    }

    CC_SAFE_DELETE(pSprite);
    return NULL;
}

void Squid::update(float dt) { 
    cocos2d::Sprite::update(dt);

    if(canShoot) {
        shoot();
    }
    move(dt);
}

void Squid::addEvents() { }

void Squid::initOptions(const cocos2d::Vec2& pos, const cocos2d::Vec2& dir) {

    // end particle stuff

    setVelocity(dir*getMoveSpeed());
    setPosition(pos);

    // Schedule update
    schedule(schedule_selector(Squid::update));
} 

void Squid::shoot() {
    setShooting(1);
}

void Squid::stop(const cocos2d::Vec2& dir) {
    runAction(cocos2d::RepeatForever::create(cocos2d::MoveBy::create(1, dir)));  
}
