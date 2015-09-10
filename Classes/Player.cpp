#include <algorithm>
#include "SimpleAudioEngine.h"
#include <cmath>
#include <iostream>
#include "Player.h"
#include "Bullet.h"

Player::Player() :
    visibleSize(cocos2d::Director::getInstance()->getVisibleSize()),
    moveSpeed(400),
    velocity(cocos2d::Vec2(0,0)),
    shooting(NONE),
    timer(0),
    lastShot(0),
    KEY_A(NOT_PRESSED),
    KEY_D(NOT_PRESSED),
    KEY_SPACE(NOT_PRESSED)
{ }

Player* Player::create() {
    // load in player image
    Player* pSprite = new Player();
    if(pSprite && pSprite->initWithFile("player.png")) {
        pSprite->autorelease();
        pSprite->initOptions();
        pSprite->addEvents();
        return pSprite;
    }

    CC_SAFE_DELETE(pSprite);
    return NULL;
}

void Player::update(float dt) { 

    cocos2d::Sprite::update(dt);
    timer++;

    if(KEY_A == PRESSED_ACTIVE) {
        move(LEFT,dt);
    }
    else if(KEY_D == PRESSED_ACTIVE) {
        move(RIGHT,dt);
    }
    if(KEY_SPACE == PRESSED_ACTIVE) {
        if( (timer-lastShot > 15) || (lastShot ==0)) {
            shoot();
            lastShot=timer;
        }
        KEY_SPACE = PRESSED_INACTIVE;
    }
    else if(KEY_SPACE == PRESSED_INACTIVE && ((timer%10) == 0)) {
        shoot();
    }
}

void Player::addEvents() { 
    
    auto listener = cocos2d::EventListenerKeyboard::create();

    listener->onKeyPressed = [this](cocos2d::EventKeyboard::KeyCode keyCode,
                                    cocos2d::Event* event) {
        switch(static_cast<int>(keyCode)) {
            case static_cast<int>(cocos2d::EventKeyboard::KeyCode::KEY_A):
                KEY_A = ( (KEY_D == PRESSED_ACTIVE) ? PRESSED_INACTIVE 
                                                    : PRESSED_ACTIVE);
                break;
            case static_cast<int>(cocos2d::EventKeyboard::KeyCode::KEY_D):
                KEY_D = ( (KEY_A == PRESSED_ACTIVE) ? PRESSED_INACTIVE 
                                                    : PRESSED_ACTIVE);
                break;
            case static_cast<int>(cocos2d::EventKeyboard::KeyCode::KEY_SPACE):
                KEY_SPACE = PRESSED_ACTIVE;
                break;
            default:
                // what
                break;
        }
    };

    listener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode,
                                     cocos2d::Event* event) {
        switch(static_cast<int>(keyCode)) {
            case static_cast<int>(cocos2d::EventKeyboard::KeyCode::KEY_A):
                KEY_A = NOT_PRESSED;
                if(KEY_D == PRESSED_INACTIVE) {
                    KEY_D = PRESSED_ACTIVE;
                }
                break;
            case static_cast<int>(cocos2d::EventKeyboard::KeyCode::KEY_D):
                KEY_D = NOT_PRESSED;
                if(KEY_A == PRESSED_INACTIVE) {
                    KEY_A = PRESSED_ACTIVE;
                }
            break;
            case static_cast<int>(cocos2d::EventKeyboard::KeyCode::KEY_SPACE):
                KEY_SPACE = NOT_PRESSED;
                break;
            default:
                break;
        }
    };
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener,30);
}
    


void Player::initOptions() {
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    addEvents();

    //runAction(cocos2d::RepeatForever::create(cocos2d::Sequence::create(cocos2d::RotateBy::create(1, 15), cocos2d::CallFunc::create(CC_CALLBACK_0(Player::move,this)), NULL)));

    // Schedule update
    schedule(schedule_selector(Player::update));
} 

void Player::move(const int dir, float dt) { 
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    if(dir == LEFT) {
        velocity.x = -1*moveSpeed*dt;
    }
    else if(dir == RIGHT) {
        velocity.x = moveSpeed*dt;
    }
    velocity.y = 0;

    setPosition(cocos2d::Vec2(getPositionX() + velocity.x, getPositionY() + velocity.y));
    if( (getPosition().x - getContentSize().width/2) < origin.x) {
        setPosition(cocos2d::Vec2(origin.x+getContentSize().width/2, getPosition().y));
    }
    else if( (getPosition().x + getContentSize().width/2) > origin.x + visibleSize.width) {
        setPosition(cocos2d::Vec2(origin.x+visibleSize.width-getContentSize().width/2, getPosition().y));
    }
}

void Player::shoot() {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("laser.mp3");
    setShooting(SHOOTING);
}
