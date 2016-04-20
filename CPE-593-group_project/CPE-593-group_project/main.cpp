//
//  main.cpp
//  CPE-593-group_project
//
//  Created by FANXUEZHOU on 16/3/31.
//  Copyright © 2016年 FANXUEZHOU. All rights reserved.
//

#include "Player_human.hpp"
#include "Administer.hpp"
#include "Player_random.hpp"
#include "Player_greedy.hpp"
#include "Weight_chart_fixed.hpp"
#include "Player_awesome.hpp"
#include "Player_thinker.hpp"
#include "Player_learner.h"
#include "Player_deepthinker.h"
using namespace::std;

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    srand((unsigned)time(NULL));
    Weight_chart_fixed *wc = new Weight_chart_fixed();
    
    Player *player1=new Player_human;
    Player *player2=new Player_random;
    Player *player3=new Player_greedy;
    Player *player4=new Player_awesome(wc);
    Player *player5=new Player_thinker(0);
    Player *player6=new Player_learner;
    Administer a(player2,player4);
    //    a.playStepByStep();
    a.factory();
    return 0;
}
