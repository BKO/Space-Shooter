#include <cocos2d.h>
#include "Bullet.h"

class SquidBullet : public Bullet
{
public:
    SquidBullet();
    static SquidBullet* create(const cocos2d::Vec2&, const cocos2d::Vec2&);
    ~SquidBullet() {}

    void update(float);
    virtual void addEvents();
    virtual void initOptions(const cocos2d::Vec2&, const cocos2d::Vec2&);
private:
    float lifetime;
    float lifeLimit;
};
