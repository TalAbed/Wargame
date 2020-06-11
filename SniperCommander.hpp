#pragma once
#include "Soldier.hpp"


class SniperCommander : public Soldier {
    public:
    explicit SniperCommander(int playerid) : Soldier (playerid){
        st = SoldierType :: sniperCommander;
        hp = 120;
        power = 100;
    }
    
    bool action (Soldier& s) override;
    void fullHeal() override;
};