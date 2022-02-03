#pragma once
#include "Entity.h"
#include <iostream>
#include <time.h>
class BulletEntity :
    public Entity
{
private:
    Side m_side{ Side::eNeutral };


public:
    void Update(visualisation& vis, World& w) override;
    void renderEntity(visualisation& vis);
    void SetBullet(Side side, float changingPosX, float changingPosY) override;
    virtual Side GetSide() const { return m_side; };
    int GetDamage() const override { return 1; }
    int GetScore() const override { return 0; }
};

