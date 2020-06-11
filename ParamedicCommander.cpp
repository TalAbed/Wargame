#include "ParamedicCommander.hpp"

bool ParamedicCommander :: action (Soldier& s){
    s.fullHeal();
    return true;
}

void ParamedicCommander :: fullHeal(){
    this->hp = 200;
}