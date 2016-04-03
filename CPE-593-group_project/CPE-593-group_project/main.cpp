//
//  main.cpp
//  CPE-593-group_project
//
//  Created by FANXUEZHOU on 16/3/31.
//  Copyright © 2016年 FANXUEZHOU. All rights reserved.
//

#include "Board.hpp"
#include "Player_human.hpp"
#include "Administer.hpp"

using namespace::std;

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    Board a;
    a.display();
    Player_human human;
    while(1){
//        human.getSituation(a.getSitution(), a.getTurn());
//        pair<int,int>temp=human.chosePosition();
//        while (!a.testValid(temp)) {
//            temp=human.chosePosition();
//        }
//        a.setChess(temp);
//        a.display();
//        a.changeTurn();
    }
    return 0;
}
