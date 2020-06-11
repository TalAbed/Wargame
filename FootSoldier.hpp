#pragma once
#include "Soldier.hpp"


class FootSoldier : public Soldier {
    public:
    explicit FootSoldier(int playerid) : Soldier (playerid){
        st = SoldierType :: footSoldier;
        hp = 100;
        power = 10;
    }
    
    bool action (Soldier& s) override;
    void fullHeal() override;
};