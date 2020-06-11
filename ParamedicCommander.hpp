#pragma once
#include "Soldier.hpp"


class ParamedicCommander : public Soldier {
    public:
    explicit ParamedicCommander(int playerid) : Soldier (playerid){
        st = SoldierType :: paramedicCommander;
        hp = 200;
        power = 00;
    }
    
    bool action (Soldier& s) override;
    void fullHeal() override;
};