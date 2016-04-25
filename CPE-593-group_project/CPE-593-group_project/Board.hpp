//
//  Board.hpp
//  CPE-593-group_project
//
//  Created by FANXUEZHOU on 16/3/31.
//  Copyright © 2016年 FANXUEZHOU. All rights reserved.
//
#ifndef Board_h
#define Board_h
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
    vector<bool>sequence_turn;//配套存放棋子的执方
    //bool turn;//当前执方 0--黑棋 1--白棋
    bool check_above(vector<vector<bool>>&needChange,pair<int,int>position,bool turn)
    {
        if(position.first<=1)
            return false;
        if(status[position.first-1][position.second]!=(!turn))
            return false;
        bool flag=false;
        int i=position.first-2;
        for(;i>=0;i--)
        {
            if(status[i][position.second]==10)
            {
                return false;
            }
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
        if(position.first>=6)
            return false;
        if(status[position.first+1][position.second]!=(!turn))
            return false;
        bool flag=false;
        int i=position.first+2;
        for(;i<8;i++)
        {
            if(status[i][position.second]==10)
            {
                return false;
            }
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
        if(position.second<=1)
            return flag;
        if(status[position.first][position.second-1]==10 || status[position.first][position.second-1]==turn)
            return flag;
        int j=position.second-2;
        for(;j>=0;j--)
        {
            if(status[position.first][j]==10)
            {
                return false;
            }
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
        if(position.second>=6)
            return flag;
        if(status[position.first][position.second+1]==10 || status[position.first][position.second+1]==turn)
            return flag;
        int j=position.second+2;
        for(;j<8;j++)
        {
            if(status[position.first][j]==10)
            {
                return false;
            }
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
        if(position.first<=1 || position.second<=1)
            return flag;
        if(status[position.first-1][position.second-1]==10 || status[position.first-1][position.second-1]==turn)
            return flag;
        int i=position.first-2;
        int j=position.second-2;
        for(;i>=0 && j>=0;i--,j--)
        {
            if(status[i][j]==10)
            {
                return false;
            }
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
        if(position.first<=1 || position.second>=6)
            return flag;
        if(status[position.first-1][position.second+1]==10 || status[position.first-1][position.second+1]==turn)
            return flag;
        int i=position.first-2;
        int j=position.second+2;
        for(;i>=0 && j<8;i--,j++)
        {
            if(status[i][j]==10)
            {
                return false;
            }
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
        if(position.first>=6 || position.second<=1)
            return flag;
        if(status[position.first+1][position.second-1]==10 || status[position.first+1][position.second-1]==turn)
            return flag;
        int i=position.first+2;
        int j=position.second-2;
        for(;i<8 && j>=0;i++,j--)
        {
            if(status[i][j]==10)
            {
                return false;
            }
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
        if(position.first>=6 || position.second>=6)
            return flag;
        if(status[position.first+1][position.second+1]==10 || status[position.first+1][position.second+1]==turn)
            return flag;
        int i=position.first+2;
        int j=position.second+2;
        for(;i<8 && j<8;i++,j++)
        {
            if(status[i][j]==10)
            {
                return false;
            }
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
    void changeBoard(vector<vector<bool>>& needChange,bool turn)
    {
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                if(needChange[i][j])
                    status[i][j]=turn;
            }
        }
    }
    void updateBoard(pair<int,int>position,bool turn)//某一步棋之后更新棋盘状态
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
        changeBoard(needChange,turn);
    }
public:
    Board()
    {
        status=vector<vector<int>>(8,vector<int>(8,10));
        status[3][3]=1;
        status[4][4]=1;
        status[3][4]=0;
        status[4][3]=0;
    }
    Board(vector<vector<int>> b)
    {
        status=b;
    }
    Board(string path)
    {
        ifstream infile;
        infile.open(path);
        if(infile.fail())
        {
            cout << "open fail!"<<endl;
            cout << "creat a new board!"<<endl;
        }
        else
        {
            cout << "continue the saved game!"<<endl;
        }
        string s;
        while(!infile.eof())
        {
            getline(infile,s);
            int x;
            int y;
            bool turn;
            stringstream temp;
            temp << s;
            temp >>x;
            temp >>y;
            temp >>turn;
            pair<int,int>position;
            position.first=x;
            position.second=y;
            sequence.push_back(position);
            sequence_turn.push_back(turn);
        }
        reappear();
    }
    bool testValid(pair<int,int>position,bool turn)
    {
        bool flag=false;
        if(position.first>=8 || position.first<0 || position.second>=8 || position.second<0)
            return false;
        if(status[position.first][position.second]!=10)
            return flag;
        vector<vector<bool>>test(8,vector<bool>(8,false));
        //上
        flag |=check_above(test, position,turn);
        //下
        flag |=check_below(test,position,turn);
        //左
        flag |=check_left(test, position,turn);
        //右
        flag |=check_right(test, position,turn);
        //左上
        flag |=check_top_left(test, position,turn);
        //右上
        flag |=check_top_right(test, position,turn);
        //左下
        flag |=check_bottom_left(test, position,turn);
        //右下
        flag |=check_bottom_right(test,position,turn);
        
        return flag;
    }
    vector<pair<int,int>> optionalPosition(bool turn)
    {
        vector<pair<int,int>> ans;
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                pair<int,int>temp;
                temp.first=i;
                temp.second=j;
                if(testValid(temp, turn))
                    ans.push_back(temp);
            }
        }
        return ans;
    }
    vector<vector<int>> getSitution()
    {
        return status;
    }
    void setChess(pair<int,int>position,bool turn)
    {
        sequence.push_back(position);
        sequence_turn.push_back(turn);
        status[position.first][position.second]=turn;
        updateBoard(position,turn);
    }
    bool isAnyValid()
    {
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                if(testValid(pair<int,int>(i,j), 0) || testValid(pair<int,int>(i,j), 1))
                    return true;
            }
        }
        return false;
    }
    int checkWinner(int &player1, int &player2)
    {
        //        int player1=0;
        //        int player2=0;
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
        //cout <<"player1 : player2 = "<<player1<<" : "<<player2<<endl;
        if(player1>player2)
            return 1;
        else if(player2>player1)
            return 2;
        else
            return 0;
    }
    void reappear()
    {
        status=vector<vector<int>>(8,vector<int>(8,10));
        status[3][3]=1;
        status[4][4]=1;
        status[3][4]=0;
        status[4][3]=0;
        vector<pair<int,int>> seq=sequence;//以下棋子的序列（只存放下子的位置）用于悔棋
        vector<bool>seq_turn=sequence_turn;//配套存放棋子的执方
        sequence.clear();
        sequence_turn.clear();
        for(int i=0;i<seq.size();i++)
        {
            setChess(seq[i], seq_turn[i]);
        }
    }
    bool undo(bool turn)
    {
        bool flag=false;
        while(sequence.size() && sequence_turn.size() && sequence_turn.back()!=turn)
        {
            sequence.pop_back();
            sequence_turn.pop_back();
        }
        if(sequence_turn.size() && sequence_turn.size())
        {
            sequence.pop_back();
            sequence_turn.pop_back();
            flag=true;
            reappear();
        }
        return flag;
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
    void save_board(vector<pair<int,int>> sequence,vector<bool> sequence_turn)
    {
        ofstream fp;
        fp.open("output.txt");
        for(int i=0;i<sequence.size();i++)
        {
            fp<<sequence[i].first <<" "<<sequence[i].second<<" "<<sequence_turn[i]<<endl;
        }
        fp.close();
    }

};
#endif

