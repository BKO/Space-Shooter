#ifndef ENEMY_H
#define ENEMY_H

#include <cocos2d.h>

#define NONE 0

class Enemy : public cocos2d::Sprite
{
public:
    Enemy();
    static Enemy* create(const cocos2d::Vec2&, const cocos2d::Vec2&);
    ~Enemy() {}

    virtual void update(float);
    virtual void addEvents();
    virtual void initOptions(const cocos2d::Vec2&, const cocos2d::Vec2&);

    virtual void move(float);
    virtual void shoot();

    int getMoveSpeed() const { return moveSpeed; }
    cocos2d::Vec2 getVelocity() const { return velocity; }
    float getVelocityX() const { return velocity.x; }
    float getVelocityY() const { return velocity.y; }
    int isShooting() const { return shooting; }

    void setVelocityY(float y) { velocity.y = y; }
    void setVelocityX(float x) { velocity.x = x; }
    void setVelocity(cocos2d::Vec2 v) { velocity = v; }
    void setShooting(int s) { shooting = s; }
    void setMoveSpeed(int m) { moveSpeed = m; }

private:
    cocos2d::Size visibleSize;
    int moveSpeed;
    cocos2d::Vec2 velocity;
    int shooting;
    int timer;
};

#endif
