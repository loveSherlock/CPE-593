//
//  Player_learner.h
//  CPE-593-group_project
//
//  Created by LIU YUJIE on 4/6/16.
//  Copyright © 2016 FANXUEZHOU. All rights reserved.
//

#ifndef Player_learner_h
#define Player_learner_h

#include "Weight_chart.hpp"
using namespace::std;

class Player_learner:public Player{
private:
    int losingCount;
    int winningCount;
    vector<pair<int, int>> steps;
    vector<vector<int>> remember;
protected:
    
public:
    Player_learner(){
        name="learner_player";
        read();
    }
    void read()
    {
        ifstream infile;
        infile.open("weight.txt");
        if(infile.fail())
            cout<<"open fail!"<<endl;
        weight = vector<vector<int>>(8,vector<int>(8,0));
        remember = vector<vector<int>>(8,vector<int>(8,0));
        for(int i=0;i<8;i++)
        {
            string temp;
            getline(infile,temp);
            stringstream x;
            x << temp;
            for(int j=0;j<8;j++)
            {
                int w;
                x >> w;
                remember[i][j]=w;
            }
        }
        infile >> losingCount;
        infile >> winningCount;
        infile.close();
    }
    void write()
    {
        ofstream oufile;
        oufile.open("weight2.txt");
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                oufile << remember[i][j] << " ";
            }
            
            oufile << '\n';
        }
        oufile << losingCount << " " << winningCount;
        oufile.close();
    }
    pair<int,int> chosePosition()
    {
        int bestValue = INT_MIN;
        vector<pair<int,int>> candidateList;
        for (int i = 0; i < optionPosition.size(); ++i) {
            pair<int, int> p = optionPosition[i];
            int value = weight[p.first][p.second];
            if (value > bestValue) {
                bestValue = value;
                candidateList.resize(1);
                candidateList[0] = p;
            } else if (value == bestValue) {
                candidateList.push_back(p);
            }
        }
        
        int randomIndex = arc4random() % candidateList.size();
        pair<int, int> sp = candidateList[randomIndex];
        steps.push_back(sp);
        return sp;
    }
    string getName(){
        return name;
    }
    
    void training(bool win) override
    {
        if (win)
        {
            for (int i = 0; i < steps.size(); ++i)
            {
                pair<int, int> sp = steps[i];
                remember[sp.first][sp.second]++;
            }
            winningCount++;
        } else {
            for (int i = 0; i < steps.size(); ++i)
            {
                pair<int, int> sp = steps[i];
                remember[sp.first][sp.second]--;
            }
            losingCount++;
        }
        steps.clear();
        write();
    }
};


#endif /* Player_learner_h */
