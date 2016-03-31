//
//  Board.hpp
//  CPE-593-group_project
//
//  Created by FANXUEZHOU on 16/3/31.
//  Copyright © 2016年 FANXUEZHOU. All rights reserved.
//
#include <iostream>
#include <string.h>
#include <cstring>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <deque>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <random>
#include <bitset>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <list>
#include <fstream>
using namespace::std;
//○ ●
class Board{
private:
    vector<vector<int>> status;//0--黑棋 1--白棋 10--空
    vector<pair<int,int>> sequence;//以下棋子的序列（只存放下子的位置）用于悔棋
    bool turn;//当前执方 0--黑棋 1--白棋
    void check_above(vector<vector<bool>>&needChange,pair<int,int>position)
    {
        if(position.first<=1)
            return;
        if(status[position.first-1][position.second]==10 || status[position.first-1][position.second]==turn)
            return;
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
    }
    void check_below(vector<vector<bool>>&needChange,pair<int,int>position)
    {
        if(position.first==7)
            return;
        if(status[position.first+1][position.second]==10 || status[position.first+1][position.second]==turn)
            return;
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
    }
    void check_left(vector<vector<bool>>&needChange,pair<int,int>position)
    {
        if(position.second==0)
            return;
        if(status[position.first][position.second-1]==10 || status[position.first][position.second-1]==turn)
            return;
        bool flag=false;
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
    }
    void check_right(vector<vector<bool>>&needChange,pair<int,int>position)
    {
        if(position.second==7)
            return;
        if(status[position.first][position.second+1]==10 || status[position.first][position.second+1]==turn)
            return;
        bool flag=false;
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
    }
    void check_top_left(vector<vector<bool>>&needChange,pair<int,int>position)
    {
        if(position.first==0 || position.second==0)
            return;
        if(status[position.first-1][position.second-1]==10 || status[position.first-1][position.second-1]==turn)
            return;
        bool flag=false;
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
    }
    void check_top_right(vector<vector<bool>>&needChange,pair<int,int>position)
    {
        if(position.first==0 || position.second==7)
            return;
        if(status[position.first-1][position.second+1]==10 || status[position.first-1][position.second+1]==turn)
            return;
        bool flag=false;
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
    }
    void check_bottom_left(vector<vector<bool>>&needChange,pair<int,int>position)
    {
        if(position.first==7 || position.second==0)
            return;
        if(status[position.first+1][position.second-1]==10 || status[position.first+1][position.second-1]==turn)
            return;
        bool flag=false;
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
            for(int x=position.first-1,y=position.second-1;x<=i && y>=j;x++,y--)
            {
                needChange[x][y]=true;
            }
        }
    }
    void check_bottom_right(vector<vector<bool>>&needChange,pair<int,int>position)
    {
        if(position.first==7 || position.second==7)
            return;
        if(status[position.first+1][position.second+1]==10 || status[position.first+1][position.second+1]==turn)
            return;
        bool flag=false;
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
    }
    void updateBoard(pair<int,int>position)//某一步棋之后更新棋盘状态
    {
//        int i=position.first;
//        int j=position.second;
        vector<vector<bool>> needChange(8,vector<bool>(8,false));//false 不改变 true 改变为当前执方
        //检查正上方
        check_above(needChange, position);
        //检查正下方
        check_below(needChange, position);
        //检查左边
        check_left(needChange, position);
        //检查右边
        check_right(needChange, position);
        //左上
        check_top_left(needChange, position);
        //右上
        check_top_right(needChange, position);
        //左下
        check_bottom_left(needChange, position);
        //右下
        check_bottom_right(needChange,position);
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                if(needChange[i][j])
                    status[i][j]=turn;
            }
        }
    }
public:
    Board()
    {
        status=vector<vector<int>>(8,vector<int>(8,10));
        status[3][3]=1;
        status[4][4]=1;
        status[3][4]=0;
        status[4][3]=0;
        turn=0;
    }
    
    void setChess(pair<int,int>position)
    {
        sequence.push_back(position);
        status[position.first][position.second]=turn;
        updateBoard(position);
    }
    void changeTurn()//更换执方
    {
        turn=!turn;
    }
    void display()
    {
        for(int i=0;i<=8;i++)
        {
            if(i==0)
            {
                cout <<"   |";
                continue;
            }
            cout<<" "<<i<<" "<<"|";
        }
        cout <<endl;
        for(int i=1;i<=8;i++)
        {
            for(int j=0;j<=8;j++)
            {
                //if(j!=0)
                cout <<"---";
                cout <<"+";
            }
            cout << endl;
            for(int j=0;j<=8;j++)
            {
                if(j==0)
                {
                    cout <<" "<<i<<" ";
                    cout <<"|";
                }
                else
                {
                    switch (status[i-1][j-1])
                    {
                        case 0:
                            cout <<" ● ";
                            break;
                        case 1:
                            cout <<" ○ ";
                            break;
                        default:
                            cout <<"   ";
                            break;
                    }
                    cout <<"|";
                }
            }
            cout <<endl;
        }
        for(int j=0;j<=8;j++)
        {
            //if(j!=0)
            cout <<"---";
            cout <<"+";
        }
        cout <<endl;
        cout <<endl;
    }
};


