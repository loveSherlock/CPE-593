//
//  Player_awesome.hpp
//  CPE-593-group_project
//
//  Created by FANXUEZHOU on 16/4/4.
//  Copyright © 2016年 FANXUEZHOU. All rights reserved.
//

#ifndef Player_awesome_h
#define Player_awesome_h
#include "Weight_chart.hpp"

class Player_awesome:public Player{
private:
    Weight_chart *weightChart;
public:
    Player_awesome(Weight_chart *wc){
        name="awesome_player";
        weightChart = wc;
    }
    pair<int,int> chosePosition()
    {
        return weightChart->getBestPos(optionPosition);
    }
    string getName(){
        return name;
    }
};


#endif /* Player_awesome_h */
