#include "FootSoldier.hpp"

bool FootSoldier :: action (Soldier& s){
    s.setHP(-10);
    return s.isAlive();
}

void FootSoldier :: fullHeal(){
    this->hp = 100;
}