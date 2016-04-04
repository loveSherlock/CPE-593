//
//  Administer.hpp
//  CPE-593-group_project
//
//  Created by FANXUEZHOU on 16/4/2.
//  Copyright © 2016年 FANXUEZHOU. All rights reserved.
//
#include "Player.hpp"
#include "Board.hpp"
class Administer{
private:
    Player *player1;//black
    Player *player2;//white
    Board *board;
    bool turn;//0--player1 1--player2
    
    
    void changeTurn()//更换执方
    {
        turn=!turn;
    }

public:
    Administer(Player* p1,Player *p2){
        player1=p1;
        player2=p2;
        board=new Board();
        turn=0;
    }
    void run()
    {
        if(!turn)//black
        {
            
        }
        else//white
        {
            
        }
    }
};