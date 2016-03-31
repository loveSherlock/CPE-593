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
    void changeBoard(pair<int,int>position)//某一步棋之后更新棋盘状态
    {
        
    }
    void setChess(pair<int,int>position)
    {
        sequence.push_back(position);
        changeBoard(position);
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
    }
};


