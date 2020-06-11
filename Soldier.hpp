#pragma once
#include <iostream>
#include <utility>
using namespace std;

enum SoldierType {footSoldier, footCommander, sniper, sniperCommander, paramedic, paramedicCommander};

class Soldier {
    protected:
    int playerId;
    SoldierType st;
    int hp;
    int power;
    pair <uint,uint> location;

    public:
    Soldier(int id) : playerId (id){}

    int getId(){
        return this->playerId;
    }

    SoldierType getType(){
        return this->st;
    }

    int getHP(){
        return this->hp;
    }

    int getPower(){
        return this->power;
    }

    pair<uint,uint> getLocation(){
        return this->location;
    }

    void setHP (int h){
        this->hp = hp+h;
    }

    void setLocation(pair<uint,uint> l){
        this->location.first = l.first;
        this->location.second = l.second;
    }

    bool isAlive(){
        if (this->hp > 0)
            return true;
        return false;
    }

    virtual bool action (Soldier& s) = 0;
    virtual void fullHeal() = 0;
};