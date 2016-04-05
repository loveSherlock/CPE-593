//
//  Player_random.hpp
//  CPE-593-group_project
//
//  Created by FANXUEZHOU on 16/4/4.
//  Copyright © 2016年 FANXUEZHOU. All rights reserved.
//

#ifndef Player_random_h
#define Player_random_h
#include "Player.hpp"

class Player_random:public Player{
private:
public:
    Player_random(){
        name="random_player";
    }
//    void getSituation(const vector<vector<int>>&stat,bool t)
//    {
//        turn=t;
//        status=stat;
//        
//    }
    pair<int,int> chosePosition()
    {
        int length=(int)optionPosition.size();
        int x=rand()%length;
        return optionPosition[x];
    }
    string getName(){
        return name;
    }
//    void findOption(const vector<pair<int,int>> &OP)
//    {
//        optionPosition=OP;
//    }
};



#endif /* Player_random_h */
