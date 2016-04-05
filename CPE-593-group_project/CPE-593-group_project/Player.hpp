//
//  Player.hpp
//  CPE-593-group_project
//
//  Created by FANXUEZHOU on 16/3/31.
//  Copyright © 2016年 FANXUEZHOU. All rights reserved.
//
#ifndef __PLAYER__H_
#define __PLAYER__H_

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

class Player{
protected:
    string name;
    vector<vector<int>> status;
    vector<pair<int,int>> optionPosition;
    bool turn;
public:
    Player(){
       
    }
//    virtual void findOption(const vector<pair<int,int>> &optionPosition)=0;
//    virtual void getSituation(const vector<vector<int>>&status,bool turn)=0;
    virtual pair<int,int> chosePosition()=0;
    virtual string getName()=0;
    void getSituation(const vector<vector<int>>&stat,bool t)
    {
        turn=t;
        status=stat;
        
    }
    void findOption(const vector<pair<int,int>> &OP)
    {
        optionPosition=OP;
    }
};
#endif