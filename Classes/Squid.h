#ifndef SQUID_H
#define SQUID_H

#include <cocos2d.h>
#include "Enemy.h"

#define NONE 0

class Squid : public Enemy
{
public:
    Squid();
    static Squid* create(const cocos2d::Vec2&, const cocos2d::Vec2&);
    ~Squid() {}

    virtual void update(float) override;
    virtual void addEvents() override;
    virtual void initOptions(const cocos2d::Vec2&, const cocos2d::Vec2&) override;
    
    bool shootingAllowed() const { return canShoot; }
    void setShootingAllowed(bool b) { canShoot = b; }

    virtual void shoot() override;
    void stop(const cocos2d::Vec2&);

private:
    bool canShoot;
};

#endif
