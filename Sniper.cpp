#include "Sniper.hpp"

bool Sniper :: action (Soldier& s){
    s.setHP(-50);
    return s.isAlive();
}

void Sniper :: fullHeal(){
    this->hp = 100;
}