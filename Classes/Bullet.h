#ifndef BULLET_H
#define BULLET_H

#include <cocos2d.h>

class Bullet : public cocos2d::Sprite
{
public:
    Bullet();
    static Bullet* create(const cocos2d::Vec2&, const cocos2d::Vec2&);
    ~Bullet() {}

    void update(float);
    virtual void addEvents();
    virtual void initOptions(const cocos2d::Vec2&, const cocos2d::Vec2&);

    void move(float);

    int getMoveSpeed() const { return moveSpeed; }
    cocos2d::Vec2 getVelocity() const { return velocity; }
    float getVelocityX() const { return velocity.x; }
    float getVelocityY() const { return velocity.y; }

    void setVelocityY(const float& y) { velocity.y = y; }
    void setVelocityX(const float& x) { velocity.x = x; }
    void setVelocity(const cocos2d::Vec2& v) { velocity = v; }
    void setMoveSpeed(const int& s) { moveSpeed = s; }

private:
    cocos2d::Size visibleSize;
    int moveSpeed;
    cocos2d::Vec2 velocity;
};

#endif
