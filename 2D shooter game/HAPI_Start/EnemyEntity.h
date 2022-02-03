#pragma once
#include "Entity.h"
#include <iostream>
#include <time.h>
class EnemyEntity :
    public Entity
{
private:

    
    int fireBullet{ 0 };
public:
    void Update(visualisation& vis, World &w) override final;
    void renderEntity(visualisation& vis);
    void SetBullet(Side side, float changingPosX, float changingPosY) override;
    Side GetSide() const override { return Side::eEnemy; }
    int GetDamage() const override { return 2; }
    int GetScore() const override { return 100; }
    Side m_side{ Side::eEnemy };
};