#pragma once
#include "Entity.h"
class ExplosionEntity :
    public Entity
{
private:
    Side m_side{ Side::eNeutral };
    int count{ 0 };
public:
    void Update(visualisation& vis, World& w) override;
    void renderEntity(visualisation& vis);
    void SetBullet(Side side, float changingPosX, float changingPosY) override;
    virtual Side GetSide() const { return m_side; }
    int GetDamage() const override { return 0; }
    int GetScore() const override { return 0;}

};

