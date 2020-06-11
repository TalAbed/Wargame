#pragma once
#include "Soldier.hpp"


class FootCommander : public Soldier {
    public:
    FootCommander(int playerid) : Soldier (playerid){
        st = SoldierType :: footCommander;
        hp = 150;
        power = 20;
    }
    
    bool action (Soldier& s) override;
    void fullHeal() override;
};