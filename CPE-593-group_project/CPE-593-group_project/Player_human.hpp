//
//  Player_human.hpp
//  CPE-593-group_project
//
//  Created by FANXUEZHOU on 16/3/31.
//  Copyright © 2016年 FANXUEZHOU. All rights reserved.
//



class Player_human:public Player{
private:
    bool turn;
public:
//    vector<pair<int,int>> findOption(){
//        
//    }
    Player_human()
    {
    }
    void getSituation(const vector<vector<int>>&status,bool t){
        turn=t;
    }
    pair<int,int> chosePosition(){
        cout << "now you are ";
        turn?cout <<"white one\n":cout <<"black one\n";
        cout << "please input the point you want to chose:\n";
        pair<int,int>ans;
        int i;
        int j;
        cin >>i>>j;
        ans.first=i-1;
        ans.second=j-1;
        return ans;
    }

};