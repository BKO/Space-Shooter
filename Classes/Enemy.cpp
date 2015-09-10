#include <algorithm>
#include <cmath>
#include <iostream>
#include "Enemy.h"

Enemy::Enemy() :
    visibleSize(cocos2d::Director::getInstance()->getVisibleSize()),
    moveSpeed(300),
    velocity(cocos2d::Vec2(0,0)),
    timer(0),
    shooting(NONE)
{ }

Enemy* Enemy::create(const cocos2d::Vec2& pos, const cocos2d::Vec2& dir) {
    // load in player image
    Enemy* pSprite = new Enemy();
    if(pSprite && pSprite->initWithFile("asteroid.png")) {
        pSprite->autorelease();
        pSprite->initOptions(pos, dir);
        pSprite->addEvents();
        return pSprite;
    }

    CC_SAFE_DELETE(pSprite);
    return NULL;
}

void Enemy::update(float dt) { 
    timer++;

    cocos2d::Sprite::update(dt);

    if( (timer%30)==0) {
        shoot();
    }
    move(dt);
}

void Enemy::addEvents() { }

void Enemy::initOptions(const cocos2d::Vec2& pos, const cocos2d::Vec2& dir) {

    setPosition(pos);
    velocity = dir*moveSpeed;

    // Schedule update
    schedule(schedule_selector(Enemy::update));
} 

void Enemy::move(float dt) {
    setPosition(cocos2d::Vec2(getPositionX() + (velocity.x*dt),
                            getPositionY() + (velocity.y*dt)));
}

void Enemy::shoot() {
    //setShooting(1);
}
