#pragma once
#include "Soldier.hpp"


class Sniper : public Soldier {
    public:
    explicit Sniper(int playerid) : Soldier (playerid){
        st = SoldierType :: sniper;
        hp = 100;
        power = 50;
    }
    
    bool action (Soldier& s) override;
    void fullHeal() override;
};