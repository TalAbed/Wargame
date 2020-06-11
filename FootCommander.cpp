#include "FootCommander.hpp"

bool FootCommander :: action (Soldier& s){
    s.setHP(-20);
    return s.isAlive();
}

void FootCommander :: fullHeal(){
    this->hp = 150;
}