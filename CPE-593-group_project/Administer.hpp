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
    bool checkAndSet()
    {
        vector<pair<int,int>> temp;//可能的选择位置
        temp=board->optionalPosition(turn);
        if(temp.size()==0)
            return false;
        pair<int,int> tempPosition;
        !turn?player1->findOption(temp):player2->findOption(temp);
        !turn?player1->getSituation(board->getSitution(), turn):player2->getSituation(board->getSitution(), turn);
        !turn?tempPosition=player1->chosePosition():tempPosition=player2->chosePosition();
        while (!board->testValid(tempPosition,turn))//返回不合法，可以改成n次之后自动选一个位置
        {
            !turn?tempPosition=player1->chosePosition():tempPosition=player2->chosePosition();
        }
        board->setChess(tempPosition,turn);
        return true;
    }
    bool run()
    {
        board->display();
        //判断是否还有位置下
        if(!board->isAnyValid())
            return false;
        cout <<"now is player";
        !turn? cout <<"1-"<<player1->getName():cout <<"2-"<<player2->getName();
        cout <<" turn(";
        !turn? cout <<"black":cout <<"white";
        cout <<")"<<endl;
        if(!checkAndSet())
            cout <<"there is no position can put the chess, skip this round."<<endl;
        turn=!turn;
        return true;
    }
    void checkWinner()
    {
        int ans=board->checkWinner();
        if(ans==0)
            cout<<"DRAW!!!"<<endl;
        if(ans==1)
            cout <<"Player1-"<<player1->getName()<<": is Winner!!"<<endl;
        if(ans==2)
            cout <<"Player2-"<<player2->getName()<<": is Winner!!"<<endl;
    }
};