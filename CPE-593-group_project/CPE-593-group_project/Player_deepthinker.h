//
//  Player_deepthinker.h
//  CPE-593-group_project
//
//  Created by LIU YUJIE on 4/18/16.
//  Copyright © 2016 FANXUEZHOU. All rights reserved.
//

#ifndef Player_deepthinker_h
#define Player_deepthinker_h
#include "Player.hpp"
#include "Board.hpp"
#include "Player_thinker.hpp"
#include "Administer.hpp"
struct Token
{
    // 当前局面 走在pos之后，整个盘面的权重
    vector<vector<int>> status;
    pair<int, int> pos;
    int weight; //走这个pos后的权值，如果需要可以继续增加参数，方便比较
    bool isEnd;
    Token(vector<vector<int>> sta)
    {
        this->status = sta;
        isEnd=false;
    }
};
static bool mysort(Token *a,Token *b)
{
    return a->weight>b->weight;
}

class Player_deepthinker: public Player
{
private:
    int depth;
    int calculateWeight(const vector<vector<int>> &sta )
    {
        // TODO: 计算出权重， 如果确认获胜可以把权重设置成一个很大的值
        
        return 0;
    }
    // 根据棋局，和深度计算出几种最优解，最优解的走法，权重
    vector<Token*> choosePositionWithDepth(vector<vector<int>> sta,int d)
    {
        vector<Token*> tokenlist;
        Board curBoard(sta);
        vector<pair<int,int>> plist = curBoard.optionalPosition(turn);
        // 对每一个棋局，遍历所有的走法
        for (int i = 0; i < plist.size(); ++i)
        {
            Board board1(sta);
            board1.setChess(plist[i], turn);
            Token *t = new Token(sta);
            t->pos = plist[i];
            // 走完棋局后, 换对方来走， 这个player不要用deepthinker， 否则会一直递归到死
            if(board1.isAnyValid())
            {
                vector<pair<int,int>> temp=board1.optionalPosition(!turn);
                if(temp.size()!=0)
                {
                    Player_thinker *player = new Player_thinker(0);
                    player->findOption(board1.optionalPosition(!turn));
                    player->getSituation(board1.getSitution(), !turn);
                    board1.setChess(player->chosePosition(), !turn);
                }
                else//对方无法下，直接计算权值，正好后面就算了，这里空吧
                {
                    ;
                }
                
                t->weight = calculateWeight(board1.getSitution());
            }
            else//棋局结束
            {
                // TODO: 如果游戏已经获胜，则赋予最大权重，如果输了则赋予最小权重
                t->isEnd=true;
                int player1=0;
                int player2=0;
                int winner=board1.checkWinner(player1,player2);
                if(winner==0)//平局
                {
                    
                }
                else if((winner==1 && turn==0)||(winner==2 && turn==1))//win
                {
                    
                }
                else//lose
                {
                    
                }
            }
            
            t->status=board1.getSitution();
            tokenlist.push_back(t);
        }
        
        if (d == 0)
        {
            // 没必要再深度递归了，就返回当前的token list
            return tokenlist;
        }
        
        for (int i = 0; i < tokenlist.size(); ++i)
        {
            Token *token = tokenlist[i];
            if(token->isEnd)
                continue;
            vector<Token*> tList = choosePositionWithDepth(token->status, d - 1);
            // TODO: 根据tList的平均情况，重新定义 token的权重
            long long sum=0;
            for(int j=0;j<tList.size();j++)
            {
                sum+=tList[j]->weight;
            }
            sum/=tList.size();
            token->weight=(int)sum;
        }
        // TODO: 按照weight 排序tokenList
        sort(tokenlist.begin(),tokenlist.end(),mysort);
        // 取前面的几种走法进行减枝
        if (tokenlist.size() > 3)
        {
            tokenlist.resize(3);
        }
        return tokenlist;
    }
public:
    Player_deepthinker(int d)
    {
        depth=d;
        name="deepthinker_player";
    }
    string getName()
    {
        return name;
    }
    pair<int,int> chosePosition()
    {
        vector<Token*> tList = choosePositionWithDepth(this->status,depth);
        return tList[0]->pos;
    }
};

#endif /* Player_deepthinker_h */
