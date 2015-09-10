#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Squid.h"
#include "SquidBullet.h"
#include <cstdlib>
#include <iostream>
#include <ctime>

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add physics
    scene->getPhysicsWorld()->setGravity(Vec2(0,0));
    layer->setPhysicsWorld(scene->getPhysicsWorld());

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

HelloWorld::~HelloWorld() {
    for(Sprite* enemy : enemies) {
        enemy->release();
    }
    for(Sprite* bullet : bullets) {
        bullet->release();
    }
    background1->release();
    background2->release();
    scroll1->release();
    scroll2->release();
    scoreBoard->release();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{

    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("laser.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("pop.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("smack.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("woosh.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("boom.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("backgroundMusic.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.8);

    score=0;

    cocos2d::Director::getInstance()->setDisplayStats(false);

    timer=0;
    std::srand(std::time(NULL));
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(0,255,0,255)) )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // add physics
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(0,0.25,25),3);
    auto edgeNode = cocos2d::Node::create();
    edgeNode->setPosition(cocos2d::Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    edgeNode->setPhysicsBody(edgeBody);
    this->addChild(edgeNode);

    // score label
    std::stringstream s;
    s << score;
    std::string score = std::string("Score: ") + s.str();
    scoreBoard = cocos2d::LabelTTF::create(score, "Market Felt", 24);

    scoreBoard->setPosition(cocos2d::Vec2(origin.x + 100,
                                          origin.y + 30));
    scoreBoard->retain();

    addChild(scoreBoard,1);

    /**********************
     * 
     * Add scrolling backgrounds
     *
     * ********************/

    background1 = cocos2d::Sprite::create("background.png");
    background1->setScaleX((cocos2d::Director::getInstance()->getWinSize().width/background1->getContentSize().width));
    background1->setScaleY((cocos2d::Director::getInstance()->getWinSize().height/background1->getContentSize().height));
    background1->setPosition(cocos2d::Point(visibleSize.width/2 + origin.x,
                                           visibleSize.height/2 + origin.y));

    background2 = cocos2d::Sprite::create("background.png");
    background2->setScaleX((cocos2d::Director::getInstance()->getWinSize().width/background2->getContentSize().width));
    background2->setScaleY((cocos2d::Director::getInstance()->getWinSize().height/background2->getContentSize().height));
    background2->setPosition(cocos2d::Point(visibleSize.width/2 + origin.x,
                                           visibleSize.height + visibleSize.height/2+ origin.y));

    scroll1 = cocos2d::Sprite::create("scrollLayer.png");
    scroll1->setScaleX((cocos2d::Director::getInstance()->getWinSize().width/scroll1->getContentSize().width));
    scroll1->setScaleY((cocos2d::Director::getInstance()->getWinSize().height/scroll1->getContentSize().height));
    scroll1->setPosition(cocos2d::Point(visibleSize.width/2 + origin.x,
                                           visibleSize.height + origin.y));

    scroll2 = cocos2d::Sprite::create("scrollLayer.png");
    scroll2->setScaleX((cocos2d::Director::getInstance()->getWinSize().width/scroll2->getContentSize().width));
    scroll2->setScaleY((cocos2d::Director::getInstance()->getWinSize().height/scroll2->getContentSize().height));
    scroll2->setPosition(cocos2d::Point(visibleSize.width/2 + origin.x,
                                        origin.y));

    background1->retain();
    background2->retain();
    scroll1->retain();
    scroll2->retain();

    addChild(background1,0);
    addChild(background2,0);
    addChild(scroll1,0);
    addChild(scroll2,0);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    

    // add "HelloWorld" splash screen"
    //auto sprite = Sprite::create("HelloWorld.png");
    player = Player::create();
    player->setPosition(Vec2(origin.x + visibleSize.width/2,
                        origin.y + visibleSize.height/8));
    player->setTag(PLAYER);

    // position the sprite on the center of the screen
    //sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(player, 0);

    schedule(schedule_selector(HelloWorld::update));

    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("backgroundMusic.mp3");
    
    return true;
}

void HelloWorld::update(float dt) {

    timer++;

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /*******************
    *
    * Background SCrolling
    *
    * *****************/
    
    if(background1->getPosition().y+visibleSize.height/2 < origin.y) {
        background1->setPosition(background1->getPosition().x, origin.y + visibleSize.height/2 + visibleSize.height-5);
    }
    if(background2->getPosition().y+visibleSize.height/2< origin.y) {
        background2->setPosition(background2->getPosition().x, origin.y + visibleSize.height/2 + visibleSize.height-5);
    }
    if(scroll1->getPosition().y +visibleSize.height/2< origin.y) {
        scroll1->setPosition(scroll1->getPosition().x, origin.y + visibleSize.height);
    }
    if(scroll2->getPosition().y+visibleSize.height/2 < origin.y) {
        scroll2->setPosition(scroll2->getPosition().x, origin.y + visibleSize.height);
    }

    background1->setPosition(background1->getPosition().x, background1->getPosition().y - 30*dt);
    background2->setPosition(background2->getPosition().x, background2->getPosition().y - 30*dt);
    scroll1->setPosition(scroll1->getPosition().x, scroll1->getPosition().y - 60*dt);
    scroll2->setPosition(scroll2->getPosition().x, scroll2->getPosition().y - 60*dt);

    /********************
     *
     * Shooting logic
     *
     * *****************/


    if(player->isShooting()) {
        Vec2 bulletPos = Vec2(player->getPositionX(), player->getPositionY()+player->getContentSize().height/2);
        Vec2 bulletDir = Vec2(0, 1);
        addBullet(Bullet::create(bulletPos, bulletDir));
        bullets.back()->setTag(PLAYER_BULLET);
        player->setShooting(0);
    }


    /***************
     *
     * Collision Handling
     *
     **************/


    Vector<Sprite*> enemiesToDelete;
    Vector<Sprite*> bulletsToDelete;

    for(Sprite* bullet : bullets) {
        Rect bulletRect = Rect(bullet->getPosition().x - (bullet->getContentSize().width/2),
                               bullet->getPosition().y - (bullet->getContentSize().height/2),
                               bullet->getContentSize().width,
                               bullet->getContentSize().height);

        if( (bullet->getPosition().y +bullet->getContentSize().height/2 ) > 
            (origin.y + visibleSize.height) ) {
            bulletsToDelete.pushBack(bullet);
        }
        else {
            for(Sprite* enemy : enemies) {
                Rect enemyRect = Rect(enemy->getPosition().x - (enemy->getContentSize().width/2),
                                      enemy->getPosition().y - (enemy->getContentSize().height/2),
                                      enemy->getContentSize().width,
                                      enemy->getContentSize().height);

                if(bulletRect.intersectsRect(enemyRect) && (bullet->getTag() != enemy->getTag()) ) {
                    if(dynamic_cast<Squid*>(enemy) ) {
                        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pop.mp3");
                        enemiesToDelete.pushBack(enemy);
                        score+=2;
                    }
                    else {
                        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("smack.mp3");
                    }
                    bulletsToDelete.pushBack(bullet);
                }
            }
        }
    }

    /***********
     *
     * Enemies OOB &
     * Player Collisins
     *
     * ********/

    for(Sprite* enemy : enemies) {
        Enemy* en = static_cast<Enemy*>(enemy);
        if( (enemy->getPosition().y + enemy->getContentSize().height/2 ) < 
            (origin.y) ) {
            enemiesToDelete.pushBack(enemy);
        }
        else if(en->isShooting()) {
            Vec2 bulletPos = Vec2(enemy->getPositionX(), enemy->getPositionY()+enemy->getContentSize().height/2);
            Vec2 bulletDir = Vec2(0, 1);
            addBullet(SquidBullet::create(bulletPos, bulletDir));
            bullets.back()->setTag(ENEMY);
            en->setShooting(0);
        }
        // player collision
        Rect playerRect = Rect(player->getPosition().x - (player->getContentSize().width/2),
                               player->getPosition().y - (player->getContentSize().height/2),
                               player->getContentSize().width/2,
                               player->getContentSize().height/2);
        Rect enemyRect = Rect(enemy->getPosition().x - (player->getContentSize().width/2),
                              enemy->getPosition().y - (player->getContentSize().height/2),
                              enemy->getContentSize().width,
                              enemy->getContentSize().height);
        if(playerRect.intersectsRect(enemyRect) ) {
            if(!dynamic_cast<Squid*>(enemy)) {
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("boom.mp3");
            }
            enemiesToDelete.pushBack(enemy);
            if(score>0) {
                score-=1;
            }
        }       
        else if(dynamic_cast<Squid*>(enemy) && (enemy->getPosition().distance(player->getPosition())< 425) 
                 && (enemy->getPosition().y- player->getPosition().y > 25) ) {
            en->setVelocity(cocos2d::Vec2(0,0));
            cocos2d::Vec2 newVel;
            cocos2d::Vec2::subtract(en->getPosition(), player->getPosition(), &newVel);
            newVel.normalize();
            newVel *= -25;
            static_cast<Squid*>(en)->setShootingAllowed(false);
            auto callback1 = cocos2d::CallFunc::create([en,newVel]() {
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("woosh.mp3");
                static_cast<Squid*>(en)->stop(newVel);
            });
            auto callback2 = cocos2d::CallFunc::create([en,newVel]() {
                en->runAction(cocos2d::RepeatForever::create(cocos2d::Sequence::create(
                                                            cocos2d::TintTo::create(0.1,255,0,0),
                                                            cocos2d::TintTo::create(0.1,255,255,255),
                                                            NULL)));
            });
                
            enemy->runAction(cocos2d::Sequence::create(callback2, 
                                                       cocos2d::MoveTo::create(1, cocos2d::Vec2(en->getPosition().x, en->getPosition().y)), 
                                                       callback1,NULL)); 
        }
    }

    /***********
     *
     *  Remove
     *  dead guys
     *
     * ********/
    
    for(Sprite* enemy : enemiesToDelete) {
        enemies.eraseObject(enemy);
        removeChild(enemy, true);
    }
    for(Sprite* bullet : bulletsToDelete) {
        bullets.eraseObject(bullet);
        removeChild(bullet, true);
    }

    // create new enemies
    if((timer%30)==0) {
        addEnemy();
    }

    // update score
    std::stringstream s;
    s << score;
    scoreBoard->setString(std::string("Score: ") + s.str());
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::addBullet(Sprite* bullet) {
    addChild(bullet);
    bullets.pushBack(bullet);
}

void HelloWorld::addEnemy(Sprite* enemy) {
    addChild(enemy);
    enemies.pushBack(enemy);
    enemies.back()->setTag(ENEMY);
}

void HelloWorld::addEnemy() {

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Vec2 enemyPos = Vec2(origin.x + 32 + (std::rand() % ((int)((visibleSize.width + origin.x) - 32 +1))), visibleSize.height+origin.y-10);
    Vec2 enemyDir = Vec2(0, -1);
    Sprite* enemy;
    if( rand() % 2) {
        enemy = Squid::create(enemyPos, enemyDir);
    }
    else {
        enemy = Enemy::create(enemyPos, enemyDir);
    }
    addChild(enemy);
    enemies.pushBack(enemy);
    enemies.back()->setTag(ENEMY);
}
