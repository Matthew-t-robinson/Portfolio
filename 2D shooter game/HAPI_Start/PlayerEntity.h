#pragma once
#include "Entity.h"
class PlayerEntity :
    public Entity
{   
public:

private:
    void Update(visualisation& vis, World& w) override final;
    void SetBullet(Side side, float changingPosX, float changingPosY) override;
    Side GetSide() const override { return m_side; }
    int GetDamage() const override { return 1; }
    int GetScore() const override { return 0; }
    
    Side m_side{ Side::ePlayer };
};

