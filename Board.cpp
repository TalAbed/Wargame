#include "Board.hpp"
#include "cmath"
#include "Soldier.hpp"

bool WarGame::Board::legalLocation(std::pair<int,int> location) const{
    return !(location.first > board.size()-1 || location.second>board[0].size()-1 || location.first<0 || location.second<0);
}

Soldier *& WarGame :: Board :: operator[] (std::pair<int,int> location){
    Soldier** s = &board[location.first][location.second];
    if(!legalLocation(location)){
        throw std::runtime_error("illegal location");
    }
    return *s;
}

Soldier *WarGame :: Board :: operator[] (std::pair<int,int> location) const {
    Soldier *s = board[location.first][location.second];
    if(!legalLocation(location)){
        throw std::runtime_error("illegal location");
    }
    return s;
}

bool WarGame :: Board :: has_soldiers (uint player_number) const{
    for (int i=0;i<board.size();i++){
        for (int j=0;j<board[0].size();j++){
            if (board[i][j]!= nullptr){
                if(board[i][j]->getId() == player_number)
                    return true;
            }
        }
    }
    return false;
}

Soldier &WarGame :: Board :: soldierToAttack (int x, int y, SoldierType st, int id){
    Soldier* s = nullptr;
    if((id==1 && !has_soldiers(2)) || (id==2 && !has_soldiers(1))){
        return *board[x][y];
    }

    if(st == footSoldier){
        double min = INT16_MAX;
        pair <int,int> minLoc (-1,-1);
        for(int i=0;i<board.size();++i){
            for(int j = 0;j<board[0].size(); ++j){
                if(board[i][j] != nullptr && board[i][j]->getId() != id){
                    if(sqrt(pow(std::abs(x-i),2) + pow(std::abs(y-j), 2)) < min){
                        min = sqrt(pow(std::abs(x-i), 2) + pow(std::abs(y-j), 2));
                        minLoc.first = i;
                        minLoc.second = j;
                    }
                }
            }
        }

        if(minLoc.first !=-1 && minLoc.second != -1){
            s = board[minLoc.first][minLoc.second];
            s -> setLocation(minLoc);
        }
    }

    else if (st == footCommander){
        for (int i=0; i<board.size(); ++i){
            for (int j=0; j<board[0].size(); ++j){
                if (board[i][j] != nullptr && board[i][j]->getId() == id && board[i][j] -> getType() == footSoldier){
                    Soldier &t = soldierToAttack(i, j, footSoldier, id);
                    if(!board[i][j]->action(t)){
                        board[t.getLocation().first][t.getLocation().second] = nullptr;
                    }
                }
                else if(board[i][j] != nullptr && board[i][j]->getId() == id && board[i][j] -> getType() == footCommander){
                    s = board[i][j];
                    s->setLocation(pair<int,int>(i,j));
                    Soldier &t = soldierToAttack(i,j,footSoldier, id);
                    if (!board[i][j]->action(t)){
                        board[t.getLocation().first][t.getLocation().second] = nullptr;
                    }
                }
            }
        }
    }

    else if (st == sniper){
        double max = INT16_MIN;
        pair<int,int> maxLoc (-1,-1);
        for (int i=0;i<board.size();++i){
            for (int j=0;j<board[0].size(); ++j){
                if (board[i][j] !=nullptr && board[i][j]->getId() != id){
                    if (board[i][j]->getHP() > max){
                        max = board[i][j]->getHP();
                        maxLoc.first = i;
                        maxLoc.second = j;
                    }
                }
            }
        }
        if (maxLoc.first !=-1 && maxLoc.second != -1){
            s = board[maxLoc.first][maxLoc.second];
            s->setLocation(maxLoc);
        }
    }

    else if (st == sniperCommander){
        for(int i = 0; i<board.size(); ++i){
            for (int j=0;j<board[0].size(); ++j){
                if (board[i][j] != nullptr && board[i][j]->getId() == id && board[i][j] -> getType() == sniperCommander){
                    s = board[i][j];
                    s->setLocation(pair<int,int> (i,j));
                    Soldier &t = soldierToAttack(i,j,sniper,id);
                    if (!board[i][j]->action(t)){
                        board[t.getLocation().first][t.getLocation().second] = nullptr;
                    }
                }
            }
        }

        for (int i = 0; i<board.size(); ++i){
            for (int j=0;j<board[0].size(); ++j){
                if (board[i][j] != nullptr && board[i][j]->getId() == id && board[i][j] -> getType() == sniper){
                    Soldier &t = soldierToAttack(i,j,sniper,id);
                    if (!board[i][j]->action(t)){
                        board[t.getLocation().first][t.getLocation().second] = nullptr;
                    }
                }
            }
        }
    }

    else if (st == paramedic){
        s=board[x][y];
        try{
            if (board[x-1][y-1] != nullptr && board[x-1][y-1]->getId() == id){
                board[x-1][y-1]->fullHeal();
            }
        }
        catch(exception &e){}

        try{
            if (board[x][y-1] != nullptr && board[x][y-1]->getId() == id){
                board[x][y-1]->fullHeal();
            }
        }
        catch(exception &e){}

        try{
            if (board[x+1][y-1] != nullptr && board[x+1][y-1]->getId() == id){
                board[x+1][y-1]->fullHeal();
            }
        }
        catch(exception &e){}

        try{
            if (board[x+1][y] != nullptr && board[x+1][y]->getId() == id){
                board[x+1][y]->fullHeal();
            }
        }
        catch(exception &e){}

        try{
            if (board[x+1][y+1] != nullptr && board[x+1][y+1]->getId() == id){
                board[x+1][y+1]->fullHeal();
            }
        }
        catch(exception &e){}

        try{
            if (board[x][y+1] != nullptr && board[x][y+1]->getId() == id){
                board[x][y+1]->fullHeal();
            }
        }
        catch(exception &e){}

        try{
            if (board[x-1][y+1] != nullptr && board[x-1][y+1]->getId() == id){
                board[x-1][y+1]->fullHeal();
            }
        }
        catch(exception &e){}

        try{
            if (board[x-1][y] != nullptr && board[x-1][y]->getId() == id){
                board[x-1][y]->fullHeal();
            }
        }
        catch(exception &e){}
    }

    else if (st == paramedicCommander){
        s = board[x][y];
        for (int i=0;i<board.size();++i){
            for (int j=0;j<board[0].size();j++){
               if(board[i][j] != nullptr && board[i][j]->getId() == id && board[i][j] -> getType() == paramedic){
                   board[i][j]->action(soldierToAttack(i,j,paramedic,id));
               } 
            }
        }
        board[x][y]->action(soldierToAttack(x,y,paramedic,id));
    }

    return *s;
}

void WarGame :: Board:: move(uint player_number, std::pair<int,int> source, MoveDIR direction){
    if (board[source.first][source.second] == nullptr || board[source.first][source.second]->getId() != player_number){
        throw std :: runtime_error("didn't find player");
    }

    switch(direction){
        
        case Up:{
        if(!legalLocation(pair<int,int>(source.first+1, source.second)) || board[source.first+1][source.second] != nullptr){
            throw std :: runtime_error("illegal move");
        }
        board[source.first+1][source.second] = board[source.first][source.second];
        board[source.first][source.second] = nullptr;
        Soldier &t = soldierToAttack(source.first+1, source.second, board[source.first+1][source.second]->getType(), board[source.first+1][source.second]->getId());
        if(board[t.getLocation().first][t.getLocation().second] != nullptr && t.getId()!=board[source.first+1][source.second]->getId()){
            if(board[source.first+1][source.second]->getType() == footSoldier || board[source.first+1][source.second]->getType() == sniper){
                if(!board[source.first+1][source.second]->action(t)){
                    cout << "moving UP" << endl;
                    board[t.getLocation().first][t.getLocation().second] = nullptr;
                }
            }
        }
        break;
        }

        case Down:{
            if(!legalLocation(pair<int,int>(source.first-1, source.second)) || board[source.first-1][source.second] != nullptr){
                throw std :: runtime_error("illegal move");
            }
            board[source.first-1][source.second] = board[source.first][source.second];
            board[source.first][source.second] = nullptr;
            Soldier &t = soldierToAttack(source.first-1, source.second, board[source.first-1][source.second]->getType(), board[source.first-1][source.second]->getId());
            if(board[t.getLocation().first][t.getLocation().second] != nullptr && t.getId()!=board[source.first-1][source.second]->getId()){
                if(board[source.first-1][source.second]->getType() == footSoldier || board[source.first-1][source.second]->getType() == sniper){
                    if(!board[source.first-1][source.second]->action(t)){
                        cout << "moving DOWN" << endl;
                        board[t.getLocation().first][t.getLocation().second] = nullptr;
                    }
                }
            }
            break;
        }

        case Right:{
            if(!legalLocation(pair<int,int>(source.first, source.second+1)) || board[source.first][source.second+1] != nullptr){
                throw std :: runtime_error("illegal move");
            }
            board[source.first][source.second+1] = board[source.first][source.second];
            board[source.first][source.second] = nullptr;
            Soldier &t = soldierToAttack(source.first, source.second+1, board[source.first][source.second+1]->getType(), board[source.first][source.second+1]->getId());
            if(board[t.getLocation().first][t.getLocation().second] != nullptr && t.getId()!=board[source.first][source.second+1]->getId()){
               if(board[source.first][source.second+1]->getType() == footSoldier || board[source.first][source.second+1]->getType() == sniper) {
                   if(!board[source.first][source.second+1]->action(t)){
                       cout << "moving RIGHT" << endl;
                       board[t.getLocation().first][t.getLocation().second] = nullptr;
                   }
               }
            }
            break;
        }

        case Left:{
            if(!legalLocation(pair<int,int>(source.first, source.second-1)) || board[source.first][source.second-1] != nullptr){
                throw std :: runtime_error("illegal move");
            }
            board[source.first][source.second-1] = board[source.first][source.second];
            board[source.first][source.second] = nullptr;
            Soldier &t = soldierToAttack(source.first, source.second-1, board[source.first][source.second-1]->getType(), board[source.first][source.second-1]->getId());
            if(board[t.getLocation().first][t.getLocation().second] != nullptr && t.getId()!=board[source.first][source.second-1]->getId()){
               if(board[source.first][source.second-1]->getType() == footSoldier || board[source.first][source.second-1]->getType() == sniper) {
                   if(!board[source.first][source.second-1]->action(t)){
                       cout << "moving LEFT" << endl;
                       board[t.getLocation().first][t.getLocation().second] = nullptr;
                   }
               }
            }
            break;
        }
    }
}