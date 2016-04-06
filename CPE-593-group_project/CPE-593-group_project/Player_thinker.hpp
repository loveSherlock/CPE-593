//
//  Player_thinker.hpp
//  CPE-593-group_project
//
//  Created by FANXUEZHOU on 16/4/6.
//  Copyright © 2016年 FANXUEZHOU. All rights reserved.
//

#ifndef Player_thinker_h
#define Player_thinker_h
#include "Player.hpp"
#include "Board.hpp"

class Player_thinker: public Player{
private:
    int depth;
    int calculate(int n,pair<int,int> pos)
    {
        Board *b=new Board(this->status);
        
        
        
        return 1;
    }
public:
    Player_thinker(int d)
    {
        depth=d;
        name="thinker_player";
    }
    string getName(){
        return name;
    }
    pair<int,int> chosePosition()
    {
        int length=(int)optionPosition.size();
        for(int i=0;i<length;i++)
        {
            //对每一个走法进行depth层递归计算每一个的值
        }
    }
};
#endif /* Player_thinker_h */
