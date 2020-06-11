#include "SniperCommander.hpp"

bool SniperCommander :: action (Soldier& s){
    s.setHP(-100);
    return s.isAlive();
}

void SniperCommander :: fullHeal(){
    this->hp = 120;
}