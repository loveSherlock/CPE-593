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
using namespace::std;

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    srand((unsigned)time(NULL));
    Player *player1=new Player_random;
    Player *player2=new Player_random;
    Administer a(player1,player2);
    a.factory();
    //a.playStepByStep();
    return 0;
}
