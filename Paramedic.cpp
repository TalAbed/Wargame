#include "Paramedic.hpp"

bool Paramedic :: action (Soldier& s){
    s.fullHeal();
    return true;
}

void Paramedic :: fullHeal(){
    this->hp = 100;
}