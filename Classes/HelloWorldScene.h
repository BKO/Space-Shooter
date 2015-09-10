#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#define ENEMY 0
#define ENEMY_BULLET 1
#define PLAYER_BULLET 2
#define PLAYER 3

#include "cocos2d.h"
#include "Player.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    ~HelloWorld();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    void update(float dt);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    void addBullet(cocos2d::Sprite*);
    void addEnemy(cocos2d::Sprite*);
    void addEnemy();
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
public:
    void setPhysicsWorld(cocos2d::PhysicsWorld* world){m_world = world;}
private:
    Player* player;
    int timer; // for update
    cocos2d::PhysicsWorld* m_world;
    cocos2d::Vector<cocos2d::Sprite*> enemies;
    cocos2d::Vector<cocos2d::Sprite*> bullets;
    cocos2d::Sprite* background1;
    cocos2d::Sprite* background2;
    cocos2d::Sprite* scroll1;
    cocos2d::Sprite* scroll2;
    int score;
    cocos2d::LabelTTF *scoreBoard;
};

#endif // __HELLOWORLD_SCENE_H__
