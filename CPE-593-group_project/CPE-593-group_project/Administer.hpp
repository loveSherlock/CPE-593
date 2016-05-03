//
//  Administer.hpp
//  CPE-593-group_project
//
//  Created by FANXUEZHOU on 16/4/2.
//  Copyright © 2016年 FANXUEZHOU. All rights reserved.
//
#ifndef Administer_hpp
#define Administer_hpp
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
    bool run_for_factory()
    {
        //board->display();
        //判断是否还有位置下
        if(!board->isAnyValid())
            return false;
        checkAndSet();
        turn=!turn;
        return true;
    }
    bool isSecretCode(pair<int,int>pos)
    {
        if(pos.first==-1 && pos.second==-1)
            return true;
        if(pos.first==10 && pos.second==10)
            return true;
        return false;
    }
    void secretCode(pair<int,int>code)
    {
        if(code.first==-1 && code.second==-1)//悔棋
        {
            bool flag=board->undo(turn);
            if(flag)
                cout <<"undo it!"<<endl;
            else
                cout <<"can't do that!"<<endl;
        }
        if(code.first==10 && code.first==10)//save
        {
            board->save_board();
            cout << "save this game in the output.txt"<<endl;
        }
        turn=!turn;
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
        
        //test
        //cout << "position:"<<tempPosition.first+1<<","<<tempPosition.second+1<<endl;
        while (!board->testValid(tempPosition,turn) && !isSecretCode(tempPosition))//返回不合法，可以改成n次之后自动选一个位置?
        {
            !turn?tempPosition=player1->chosePosition():tempPosition=player2->chosePosition();
        }
        if(isSecretCode(tempPosition))
            secretCode(tempPosition);
        else
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
        int p1=0;
        int p2=0;
        int ans=board->checkWinner(p1,p2);
        cout <<"player1 : player2 = "<<p1<<" : "<<p2<<endl;
        if(ans==0)
            cout<<"DRAW!!!"<<endl;
        if(ans==1)
            cout <<"Player1-"<<player1->getName()<<": is Winner!!"<<endl;
        if(ans==2)
            cout <<"Player2-"<<player2->getName()<<": is Winner!!"<<endl;
    }
public:
    Administer(Player* p1,Player *p2){
        player1=p1;
        player2=p2;
        board=new Board();
        turn=0;
    }
    Administer(Player *p1,Player *p2,vector<vector<int>> b,bool t)
    {
        player1=p1;
        player2=p2;
        board=new Board(b);
        turn=t;
    }
    Administer(Player *p1,Player *p2,string path)
    {
        player1=p1;
        player2=p2;
        board=new Board();
        turn=0;
        ifstream infile;
        infile.open(path);
        if(infile.fail())
        {
            cout << "open fail!"<<endl;
            cout << "creat a new board!"<<endl;
        }
        else
        {
            cout << "reappear the saved game!"<<endl;
            string s;
            while(!infile.eof())
            {
                getline(infile,s);
                int x;
                int y;
                stringstream temp;
                temp << s;
                temp >>x;
                temp >>y;
                temp >>turn;
                pair<int,int>position;
                position.first=x;
                position.second=y;
                board->setChess(position, turn);
                board->display();
            }
            turn=!turn;
            cout << "continue the saved game!"<<endl;
            playStepByStep();
        }

    }
    void playStepByStep()
    {
        //board=new Board();
        //turn=0;
        while(run());
        checkWinner();
    }
    void factory(int repeat)
    {
        int pl1=0;
        int pl2=0;
        while(repeat)
        {
            repeat--;
            board=new Board();
            turn=0;
            int p1=0;
            int p2=0;
            while(run_for_factory());
            int temp=board->checkWinner(p1,p2);
            if(temp==1)
                pl1++;
            else if(temp==2)
                pl2++;
        }
        cout << "player1-"<<player1->getName()<<" win "<< pl1<<" times."<<endl;
        cout << "player2-"<<player2->getName()<<" win "<< pl2<<" times."<<endl;
    }
};
#endif