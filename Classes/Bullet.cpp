#include <algorithm>
#include <cmath>
#include <iostream>
#include "Bullet.h"

Bullet::Bullet() :
    visibleSize(cocos2d::Director::getInstance()->getVisibleSize()),
    moveSpeed(500),
    velocity(cocos2d::Vec2(0,0))
{ }

Bullet* Bullet::create(const cocos2d::Vec2& pos, const cocos2d::Vec2& dir) {
    // load in player image
    Bullet* pSprite = new Bullet();
    if(pSprite && pSprite->initWithFile("bullet.png")) {
        pSprite->autorelease();
        pSprite->initOptions(pos, dir);
        pSprite->addEvents();
        return pSprite;
    }

    CC_SAFE_DELETE(pSprite);
    return NULL;
}

void Bullet::update(float dt) { 

    cocos2d::Sprite::update(dt);
    move(dt);
}

void Bullet::addEvents() { }

void Bullet::initOptions(const cocos2d::Vec2& pos, const cocos2d::Vec2& dir) {

    setPosition(pos);
    velocity = dir*moveSpeed;

    // Schedule update
    schedule(schedule_selector(Bullet::update));
} 

void Bullet::move(float dt) {
    setPosition(cocos2d::Vec2(getPositionX() + (velocity.x*dt),
                            getPositionY() + (velocity.y*dt)));
}
