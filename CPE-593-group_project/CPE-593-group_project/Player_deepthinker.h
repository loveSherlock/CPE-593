//
//  Player_deepthinker.h
//  CPE-593-group_project
//
//  Created by LIU YUJIE on 4/18/16.
//  Copyright © 2016 FANXUEZHOU. All rights reserved.
//

#ifndef Player_deepthinker_h
#define Player_deepthinker_h
#include "Player.hpp"
#include "Board.hpp"
#include "Player_thinker.hpp"
#include "Administer.hpp"
struct Token
{
    // 当前局面 走在pos之后，整个盘面的权重
    vector<vector<int>> status;
    pair<int, int> pos;
    int weight; //走这个pos后的权值，如果需要可以继续增加参数，方便比较
    bool isEnd;
    Token(vector<vector<int>> sta)
    {
        this->status = sta;
        isEnd=false;
    }
};
static bool mysort(Token *a,Token *b)
{
    return a->weight>b->weight;
}

class Player_deepthinker: public Player
{
private:
    int depth;
    int possiblePosition(const vector<vector<int>> &sta,bool self)
    {
        int ans=0;
        Board board(sta);
        vector<pair<int,int>> positionList = board.optionalPosition(self?turn:!turn);
        for(int i=0;i<positionList.size();i++)
        {
            pair<int,int>temp=positionList[i];
            ans+=weight[temp.first][temp.second];
        }
        return ans;
    }
    bool isStablePoint(pair<int, int> p, pair<int, int> d,const unordered_set<int> &s)
    {
        pair<int, int> p1 = make_pair(p.first + d.first, p.second + d.second);
        if (p1.first < 0 || p1.second << 0 || p1.first >= 8 || p1.second >= 8 || isPairInSet(p1, s)) {
            return true;
        }
        p1 = make_pair(p.first - d.first, p.second - d.second);
        if (p1.first < 0 || p1.second << 0 || p1.first >= 8 || p1.second >= 8 || isPairInSet(p1, s)) {
            return true;
        }
        return false;
    }
    
    bool isPairInSet(pair<int, int>p ,const unordered_set<int> &s)
    {
        return s.count(p.first * 8 + p.second);
    }
    void putPairInSet(pair<int, int>p ,unordered_set<int> &s)
    {
        s.insert(p.first * 8 + p.second);
    }

    int absStablePosition(const vector<vector<int>> &sta)
    {
        Board board(sta);
        // 一定不会被吃掉的列表
        pair<int,int> p1 = make_pair<int, int>(0, 0);
        pair<int,int> p2 = make_pair<int, int>(0, 7);
        pair<int,int> p3 = make_pair<int, int>(7, 0);
        pair<int,int> p4 = make_pair<int, int>(7, 7);
        vector<pair<int, int>> list;
        list.push_back(p1);
        list.push_back(p2);
        list.push_back(p3);
        list.push_back(p4);
        
        int number = 0;
        unordered_set<int> s;
        while (!list.empty()) {
            pair<int,int> pp = list.back();
            list.pop_back();
            if (board.getSitution()[pp.first][pp.second] == turn && !isPairInSet(pp, s)) {
                putPairInSet(pp, s);
                number+=1000;
                //考虑下相邻的点
                pair<int,int> pp1 = make_pair(pp.first - 1, pp.second);
                if (pp1.first >= 0 && isStablePoint(pp1, make_pair(0, 1) , s) &&
                    isStablePoint(pp1, make_pair(1, 1) , s) &&
                    isStablePoint(pp1, make_pair(1, 0) , s) &&
                    isStablePoint(pp1, make_pair(-1, 1) , s)) {
                    list.push_back(pp1);
                }
                pp1 = make_pair(pp.first + 1, pp.second);
                if (pp1.first < 8 && isStablePoint(pp1, make_pair(0, 1) , s) &&
                    isStablePoint(pp1, make_pair(1, 1) , s) &&
                    isStablePoint(pp1, make_pair(1, 0) , s) &&
                    isStablePoint(pp1, make_pair(-1, 1) , s)) {
                    list.push_back(pp1);
                }
                pp1 = make_pair(pp.first, pp.second + 1);
                if (pp1.second >= 0 && isStablePoint(pp1, make_pair(0, 1) , s) &&
                    isStablePoint(pp1, make_pair(1, 1) , s) &&
                    isStablePoint(pp1, make_pair(1, 0) , s) &&
                    isStablePoint(pp1, make_pair(-1, 1) , s)) {
                    list.push_back(pp1);
                }
                pp1 = make_pair(pp.first, pp.second - 1);
                if (pp1.second < 8 && isStablePoint(pp1, make_pair(0, 1) , s) &&
                    isStablePoint(pp1, make_pair(1, 1) , s) &&
                    isStablePoint(pp1, make_pair(1, 0) , s) &&
                    isStablePoint(pp1, make_pair(-1, 1) , s)) {
                    list.push_back(pp1);
                }
            } else {
                number++;
            }
        };
        return number;
    }
    int calculateWeight(const vector<vector<int>> &sta,pair<int,int>pos)
    {
        int ans=0;
        //第一部分权值，可下位置；
        ans+=1*possiblePosition(sta,true);
        //第二部分权值，下完这步之后的绝对稳定子
        ans+=100*absStablePosition(sta);
        //第三部分权值，下完这步之后的对方执行力
        Board board(status);
        board.setChess(pos, turn);
        ans+=-1*possiblePosition(board.getSitution(), false);
        return ans;
    }
    // 根据棋局，和深度计算出几种最优解，最优解的走法，权重
    vector<Token*> choosePositionWithDepth(vector<vector<int>> sta,int d)
    {
        vector<Token*> tokenlist;
        Board curBoard(sta);
        vector<pair<int,int>> plist = curBoard.optionalPosition(turn);
        // 对每一个棋局，遍历所有的走法
        if(plist.size()==0)
            return vector<Token*>();
        for (int i = 0; i < plist.size(); ++i)
        {
            Board board1(sta);
            board1.setChess(plist[i], turn);
            Token *t = new Token(sta);
            t->pos = plist[i];
            // 走完棋局后, 换对方来走， 这个player不要用deepthinker， 否则会一直递归到死
            if(board1.isAnyValid())
            {
                vector<pair<int,int>> temp=board1.optionalPosition(!turn);
                if(temp.size()!=0)
                {
                    Player_thinker *player = new Player_thinker(0);
                    player->findOption(board1.optionalPosition(!turn));
                    player->getSituation(board1.getSitution(), !turn);
                    board1.setChess(player->chosePosition(), !turn);
                }
                else//对方无法下，直接计算权值，正好后面就算了，这里空吧
                {
                    ;
                }
                
                t->weight = calculateWeight(board1.getSitution(),plist[i]);
            }
            else//棋局结束
            {
                // TODO: 如果游戏已经获胜，则赋予最大权重，如果输了则赋予最小权重
                t->isEnd=true;
                int player1=0;
                int player2=0;
                int winner=board1.checkWinner(player1,player2);
                if(winner==0)//平局
                {
                    t->weight=0;
                }
                else if((winner==1 && turn==0)||(winner==2 && turn==1))//win
                {
                    t->weight=9999999;
                }
                else//lose
                {
                    t->weight=-999999;
                }
            }
            
            t->status=board1.getSitution();
            tokenlist.push_back(t);
        }
        
        if (d == 0)
        {
            // 没必要再深度递归了，就返回当前的token list
            return tokenlist;
        }
        
        for (int i = 0; i < tokenlist.size(); ++i)
        {
            Token *token = tokenlist[i];
            if(token->isEnd)
                continue;
            vector<Token*> tList = choosePositionWithDepth(token->status, d - 1);
            // TODO: 根据tList的平均情况，重新定义 token的权重
            long long sum=0;
            for(int j=0;j<tList.size();j++)
            {
                sum+=tList[j]->weight;
            }
            if(tList.size()!=0)
            {
                sum/=tList.size();
                token->weight=(int)sum;
            }
        }
        // TODO: 按照weight 排序tokenList
        sort(tokenlist.begin(),tokenlist.end(),mysort);
        // 取前面的几种走法进行减枝
        if (tokenlist.size() > 3)
        {
            tokenlist.resize(3);
        }
        return tokenlist;
    }
public:
    Player_deepthinker(int d)
    {
        depth=d;
        name="deepthinker_player";
    }
    string getName()
    {
        return name;
    }
    pair<int,int> chosePosition()
    {
        vector<Token*> tList = choosePositionWithDepth(this->status,depth);
        return tList[0]->pos;
    }
};

#endif /* Player_deepthinker_h */
