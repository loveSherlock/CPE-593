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
    //int depth;
    int calculate_mobility(vector<vector<int>> sta,pair<int,int> pos,bool t)//走出某步之后的局面评分－－一定要确认pos是可走的－－行动力评价
    {
        Board *b=new Board(sta);
        b->setChess(pos,t);
        int ans=0;
        vector<pair<int,int>> optionalPositionList=b->optionalPosition(!t);
        for(pair<int,int>temp:optionalPositionList)
        {
            ans+=weight[temp.first][temp.second];
        }
        if(turn==t)
            return -ans;
        else
            return ans;
    }
    int calculate(vector<vector<int>> sta,pair<int,int> pos,bool t)
    {
        int ans=0;
        //行动力评分＋不动点评分＋。。。可以加权值
        ans+=calculate_mobility(sta, pos, t);
        return ans;
    }
    public:
    Player_thinker()
    {
        //depth=d;
        name="thinker_player";
    }
    string getName(){
        return name;
    }
    pair<int,int> chosePosition()
    {
        int value=INT_MIN;
        int chose=0;
        int length=(int)optionPosition.size();
        for(int i=0;i<length;i++)
        {
            //对每一个走法进行depth层递归计算每一个的值
            int temp=calculate(this->status,optionPosition[i], turn);
            if(temp>value)
            {
                value=temp;
                chose=i;
            }
        }
        return optionPosition[chose];
    }
};
#endif /* Player_thinker_h */
