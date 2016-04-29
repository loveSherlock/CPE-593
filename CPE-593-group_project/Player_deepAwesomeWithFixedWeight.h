//
//  Player_deepAwesomeWithFixedWeight.h
//  CPE-593-group_project
//
//  Created by FANXUEZHOU on 16/4/28.
//  Copyright © 2016年 FANXUEZHOU. All rights reserved.
//

#ifndef Player_deepAwesomeWithFixedWeight_h
#define Player_deepAwesomeWithFixedWeight_h
#include "Weight_chart.hpp"

class Player_deepAwesomeWithFixedWeight: public Player
{
private:
    Weight_chart *weightChart;
    int depth;
    
    // 根据棋局，和深度计算出几种最优解，最优解的走法，权重
    vector<Token*> choosePositionWithDepth(vector<vector<int>> sta,int d)
    {
        vector<Token*> tokenlist;
        
        Board curBoard(sta);
        vector<pair<int,int>> plist = curBoard.optionalPosition(turn);
        for (int i = 0; i < plist.size(); ++i) {
            
            Board board1(sta);
            board1.setChess(plist[i], turn);
            // 走完棋局后, 换对方来走， 这个player不要用deepthinker， 否则会一直递归到死
            if(board1.isAnyValid())
            {
                int bestOpWeight = -100;
                vector<pair<int,int>> bestOptions;
                vector<pair<int,int>> temp=board1.optionalPosition(!turn);
                for (int j = 0; j < temp.size(); ++j) {
                    pair<int, int> opPos = temp[j];
                    int w = weightChart->getWeightByPos(opPos);
                    if (w > bestOpWeight) {
                        bestOpWeight = w;
                        bestOptions.clear();
                        bestOptions.push_back(opPos);
                    } else if (w == bestOpWeight) {
                        bestOptions.push_back(opPos);
                    }
                }
                for (int j = 0; j < bestOptions.size(); ++j) {
                    Board board2(board1.getSitution());
                    board2.setChess(bestOptions[j], !turn);
                    
                    Token *t = new Token(board2.getSitution());
                    t->pos = plist[i];
                    t->weight = weightChart->getWeightByPos(plist[i]) - bestOpWeight;
                    
                    tokenlist.push_back(t);
                }
                if (bestOptions.size() == 0) {
                    
                    Token *t = new Token(board1.getSitution());
                    t->pos = plist[i];
                    t->weight = weightChart->getWeightByPos(plist[i]);
                    
                    tokenlist.push_back(t);
                }
                
            }
            else//棋局结束
            {
                // TODO: 如果游戏已经获胜，则赋予最大权重，如果输了则赋予最小权重
                Token *t = new Token(board1.getSitution());
                t->isEnd=true;
                t->pos = plist[i];
                int player1=0;
                int player2=0;
                int winner=board1.checkWinner(player1,player2);
                if(winner==0)//平局
                {
                    t->weight=0;
                }
                else if((winner==1 && turn==0)||(winner==2 && turn==1))//win
                {
                    t->weight=9999999;
                }
                else//lose
                {
                    t->weight=-999999;
                }
                tokenlist.push_back(t);
            }
        }
        
        if (d <= 1) {
            // 没必要再深度递归了
            sort(tokenlist.begin(),tokenlist.end(),mysort);
            if (tokenlist.size() > 1) {
                tokenlist.resize(1);
            }
            return tokenlist;
        }
        for (int i = 0; i < tokenlist.size(); ++i) {
            Token *t = tokenlist[i];
            if (!t->isEnd) {
                vector<Token *> tlist = choosePositionWithDepth(t->status, d - 1);
                if (tlist.size() > 0) {
                    t->weight += tlist[0]->weight;
                }
            }
            
        }
        
        sort(tokenlist.begin(),tokenlist.end(),mysort);
        if (tokenlist.size() > 1) {
            tokenlist.resize(1);
        }
        return tokenlist;
    }
public:
    Player_deepAwesomeWithFixedWeight(int d,Weight_chart *wc)
    {
        depth=d;
        weightChart = wc;
        name="Player_deepAwesomeWithFixedWeight(" + to_string(d) + ")";
    }
    string getName()
    {
        return name;
    }
    pair<int,int> chosePosition()
    {
        vector<Token*> tList = choosePositionWithDepth(this->status,depth);
        int i=tList[0]->pos.first;
        int j=tList[0]->pos.second;
        if(i==0 && j==0)
        {
            weightChart->getWeightByPos(pair<int,int>(i+1,j));
            weightChart->getWeightByPos(pair<int,int>(i,j+1));
            weightChart->getWeightByPos(pair<int,int>(i+1,j+1));
        }
        else if(i==0 && j==7)
        {
            weightChart->getWeightByPos(pair<int,int>(i+1,j));
            weightChart->getWeightByPos(pair<int,int>(i,j-1));
            weightChart->getWeightByPos(pair<int,int>(i+1,j-1));
        }
        else if(i==7 && j==0)
        {
            weightChart->getWeightByPos(pair<int,int>(i-1,j));
            weightChart->getWeightByPos(pair<int,int>(i,j+1));
            weightChart->getWeightByPos(pair<int,int>(i-1,j+1));
        }
        else if( i==7 && j==7)
        {
            weightChart->getWeightByPos(pair<int,int>(i-1,j));
            weightChart->getWeightByPos(pair<int,int>(i,j-1));
            weightChart->getWeightByPos(pair<int,int>(i-1,j-1));
        }
        return tList[0]->pos;
    }
};


#endif /* Player_deepAwesomeWithFixedWeight_h */
