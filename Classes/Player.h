#include <cocos2d.h>

#define NONE 0
#define LEFT 1
#define RIGHT 2
#define NOT_PRESSED 3
#define PRESSED_INACTIVE 4
#define PRESSED_ACTIVE 5
#define SHOOTING 6

class Player : public cocos2d::Sprite
{
public:
    Player();
    static Player* create();
    ~Player() {}

    void update(float);
    virtual void addEvents();
    virtual void initOptions();

    void move(const int,float);
    void shoot();

    int getMoveSpeed() const { return moveSpeed; }
    cocos2d::Vec2 getVelocity() const { return velocity; }
    float getVelocityX() const { return velocity.x; }
    float getVelocityY() const { return velocity.y; }
    int isShooting() const { return shooting; }

    void setVelocityY(float y) { velocity.y = y; }
    void setVelocityX(float x) { velocity.x = x; }
    void setVelocity(cocos2d::Vec2 v) { velocity = v; }
    void setShooting(int s) { shooting = s; }

private:
    cocos2d::Size visibleSize;
    int moveSpeed;
    cocos2d::Vec2 velocity;
    int shooting;
    int timer; // for update
    int lastShot; // also for update
    int KEY_A, KEY_D, KEY_SPACE;
};
