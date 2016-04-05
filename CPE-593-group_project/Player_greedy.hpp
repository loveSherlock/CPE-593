//
//  Player_greedy.hpp
//  CPE-593-group_project
//
//  Created by FANXUEZHOU on 16/4/4.
//  Copyright © 2016年 FANXUEZHOU. All rights reserved.
//

#ifndef Player_greedy_h
#define Player_greedy_h
#include "Player.hpp"
class Player_greedy:public Player{
private:
//    vector<vector<int>> status;
//    vector<pair<int,int>> optionPosition;
//    bool turn;
    int count()
    {
        int player1=0;
        int player2=0;
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                if(status[i][j]==0)
                    player1++;
                else if(status[i][j]==1)
                    player2++;
            }
        }
        if(!turn)
            return player1;
        else
            return player2;
            
    }
    int updateBoard(pair<int,int>position,bool turn)//某一步棋之后更新棋盘状态
    {
        vector<vector<bool>> needChange(8,vector<bool>(8,false));//false 不改变 true 改变为当前执方
        //检查正上方
        check_above(needChange, position,turn);
        //检查正下方
        check_below(needChange, position,turn);
        //检查左边
        check_left(needChange, position,turn);
        //检查右边
        check_right(needChange, position,turn);
        //左上
        check_top_left(needChange, position,turn);
        //右上
        check_top_right(needChange, position,turn);
        //左下
        check_bottom_left(needChange, position,turn);
        //右下
        check_bottom_right(needChange,position,turn);
        return changeBoard(needChange,turn);
    }
    bool check_above(vector<vector<bool>>&needChange,pair<int,int>position,bool turn)
    {
        if(position.first<=1)
            return false;
        if(status[position.first-1][position.second]==10 || status[position.first-1][position.second]==turn)
            return false;
        bool flag=false;
        int i=position.first-2;
        for(;i>=0;i--)
        {
            if(status[i][position.second]==turn)
            {
                flag=true;
                break;
            }
        }
        if(flag)
        {
            for(int x=position.first-1;x>=i;x--)
            {
                needChange[x][position.second]=true;
            }
        }
        return flag;
    }
    bool check_below(vector<vector<bool>>&needChange,pair<int,int>position,bool turn)
    {
        if(position.first==7)
            return false;
        if(status[position.first+1][position.second]==10 || status[position.first+1][position.second]==turn)
            return false;
        bool flag=false;
        int i=position.first+2;
        for(;i<8;i++)
        {
            if(status[i][position.second]==turn)
            {
                flag=true;
                break;
            }
        }
        if(flag)
        {
            for(int x=position.first+1;x<=i;x++)
            {
                needChange[x][position.second]=true;
            }
        }
        return flag;
    }
    bool check_left(vector<vector<bool>>&needChange,pair<int,int>position,bool turn)
    {
        bool flag=false;
        if(position.second==0)
            return flag;
        if(status[position.first][position.second-1]==10 || status[position.first][position.second-1]==turn)
            return flag;
        int j=position.second-2;
        for(;j>=0;j--)
        {
            if(status[position.first][j]==turn)
            {
                flag=true;
                break;
            }
        }
        if(flag)
        {
            for(int x=position.second-1;x>=j;x--)
            {
                needChange[position.first][x]=true;
            }
        }
        return flag;
    }
    bool check_right(vector<vector<bool>>&needChange,pair<int,int>position,bool turn)
    {
        bool flag=false;
        if(position.second==7)
            return flag;
        if(status[position.first][position.second+1]==10 || status[position.first][position.second+1]==turn)
            return flag;
        int j=position.second+2;
        for(;j<8;j++)
        {
            if(status[position.first][j]==turn)
            {
                flag=true;
                break;
            }
        }
        if(flag)
        {
            for(int x=position.second+1;x<j;x++)
            {
                needChange[position.first][x]=true;
            }
        }
        return flag;
    }
    bool check_top_left(vector<vector<bool>>&needChange,pair<int,int>position,bool turn)
    {
        bool flag=false;
        if(position.first==0 || position.second==0)
            return flag;
        if(status[position.first-1][position.second-1]==10 || status[position.first-1][position.second-1]==turn)
            return flag;
        int i=position.first-2;
        int j=position.second-2;
        for(;i>=0 && j>=0;i--,j--)
        {
            if(status[i][j]==turn)
            {
                flag=true;
                break;
            }
        }
        if(flag)
        {
            for(int x=position.first-1,y=position.second-1;x>=i && y>=j;x--,y--)
            {
                needChange[x][y]=true;
            }
        }
        return flag;
    }
    bool check_top_right(vector<vector<bool>>&needChange,pair<int,int>position,bool turn)
    {
        bool flag=false;
        if(position.first==0 || position.second==7)
            return flag;
        if(status[position.first-1][position.second+1]==10 || status[position.first-1][position.second+1]==turn)
            return flag;
        int i=position.first-2;
        int j=position.second+2;
        for(;i>=0 && j<8;i--,j++)
        {
            if(status[i][j]==turn)
            {
                flag=true;
                break;
            }
        }
        if(flag)
        {
            for(int x=position.first-1,y=position.second+1;x>=i && y<=j;x--,y++)
            {
                needChange[x][y]=true;
            }
        }
        return flag;
    }
    bool check_bottom_left(vector<vector<bool>>&needChange,pair<int,int>position,bool turn)
    {
        bool flag=false;
        if(position.first==7 || position.second==0)
            return flag;
        if(status[position.first+1][position.second-1]==10 || status[position.first+1][position.second-1]==turn)
            return flag;
        int i=position.first+2;
        int j=position.second-2;
        for(;i<8 && j>=0;i++,j--)
        {
            if(status[i][j]==turn)
            {
                flag=true;
                break;
            }
        }
        if(flag)
        {
            for(int x=position.first+1,y=position.second-1;x<=i && y>=j;x++,y--)
            {
                needChange[x][y]=true;
            }
        }
        return flag;
    }
    bool check_bottom_right(vector<vector<bool>>&needChange,pair<int,int>position,bool turn)
    {
        bool flag=false;
        if(position.first==7 || position.second==7)
            return flag;
        if(status[position.first+1][position.second+1]==10 || status[position.first+1][position.second+1]==turn)
            return flag;
        int i=position.first+2;
        int j=position.second+2;
        for(;i<8 && j<8;i++,j++)
        {
            if(status[i][j]==turn)
            {
                flag=true;
                break;
            }
        }
        if(flag)
        {
            for(int x=position.first+1,y=position.second+1;x<=i && y<=j;x++,y++)
            {
                needChange[x][y]=true;
            }
        }
        return flag;
    }
    int changeBoard(vector<vector<bool>>& needChange,bool turn)
    {
        int count=0;
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                if(needChange[i][j] && status[i][j]==10)
                    count++;
            }
        }
        return count;
    }
public:
    Player_greedy(){
        name="greedy_player";
    }
    string getName(){
        return name;
    }
    pair<int,int> chosePosition()
    {
        int length=(int)optionPosition.size();
        int final=0;
        int max_change=0;
        //int now=count();
        for(int i=1;i<length;i++)
        {
            int temp_change=updateBoard(optionPosition[i], turn);
            if(temp_change>max_change)
            {
                max_change=temp_change;
                final=i;
            }
        }
        return optionPosition[final];
    }
};

#endif /* Player_greedy_h */
