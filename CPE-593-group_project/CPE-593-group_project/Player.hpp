//
//  Player.hpp
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

class Player{
private:
    
public:
    Player(){
        
    }
    //virtual vector<pair<int,int>> findOption()=0;
    virtual void getSituation(const vector<vector<int>>&status,bool turn)=0;
    virtual pair<int,int> chosePosition()=0;
};