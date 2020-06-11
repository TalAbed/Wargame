#pragma once
#include "Soldier.hpp"


class Paramedic : public Soldier {
    public:
    explicit Paramedic(int playerid) : Soldier (playerid){
        st = SoldierType :: paramedic;
        hp = 100;
        power = 0;
    }
    
    bool action (Soldier& s) override;
    void fullHeal() override;
};