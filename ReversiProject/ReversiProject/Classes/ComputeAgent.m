//
//  ComputeAgent.m
//  ReversiProject
//
//  Created by FANXUEZHOU on 11/20/15.
//  Copyright © 2015 FANXUEZHOU. All rights reserved.
//

#import "ComputeAgent.h"
#import "Token.h"
static const short PRIORITY_LIST[M][M] = {
    {200,-60,10,10,10,10,-60,200},
    {-60,-80,5,5,5,5,-80,-60},
    {20,5,10,1,1,10,5,20},
    {20,5,1,1,1,1,5,20},
    {20,5,1,1,1,1,5,20},
    {20,5,10,1,1,10,5,20},
    {-60,-80,5,5,5,5,-80,-60},
    {200,-60,10,10,10,10,-60,200}
};

@implementation ComputeAgent

-(BOOL)checkChessBoard:(Byte[M][M])board X:(int)x Y:(int)y dX:(int)dx dY:(int)dy playerId:(Byte)cp
{
    BOOL flag = NO;
    for (int i = x + dx, j = y + dy; i >= 0 && j >= 0 && i < M && j < M; i += dx, j += dy) {
        if (board[j][i] == P) {
            return NO;
        } else if (board[j][i] == cp){
            return flag;
        } else {
            flag = YES;
        }
    }
    return NO;
}

-(int)tryPutBoard:(Byte[M][M])board X:(int)x Y:(int)y dX:(int)dx dY:(int)dy playerId:(Byte)cp
{
    BOOL flag = NO;
    for (int i = x + dx, j = y + dy; i >= 0 && j >= 0 && i < M && j < M; i += dx, j += dy) {
        if (board[j][i] == P) {
            return 0;
        } else if (board[j][i] == cp){
            if (flag) {
                int len = 0;
                for (int ii = x, jj = y; ii != i || jj != j; ii += dx, jj += dy) {
                    len++;
                }
                return len;
            }
            return 0;
        } else {
            flag = YES;
        }
    }
    return 0;
}


-(void)tryPutBoardChange:(Byte[M][M])board X:(int)x Y:(int)y dX:(int)dx dY:(int)dy playerId:(Byte)cp
{
    BOOL flag = NO;
    for (int i = x + dx, j = y + dy; i >= 0 && j >= 0 && i < M && j < M; i += dx, j += dy) {
        if (board[j][i] == P) {
            return ;
        } else if (board[j][i] == cp){
            if (flag) {
                for (int ii = x, jj = y; ii != i || jj != j; ii += dx, jj += dy) {
                    board[jj][ii] = cp;
                }
                return;
            }
            return;
        } else {
            flag = YES;
        }
    }
}

-(Byte)getBoard:(Byte[M][M])board X:(int)x Y:(int)y direct:(int)direct
{
    switch (direct) {
        case 0:
            return board[y][x];
        case 1:
            return board[M-y][x];
        case 2:
            return board[M-y][M-x];
        case 3:
            return board[y][M-x];
    }
    return board[y][x];
}

-(int)calculatePriority:(Byte[M][M])board playerId:(Byte)cp
{
    BOOL nonOpponent = YES;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; ++j) {
            if (board[j][i] != cp && board[j][i] != P) {
                nonOpponent = NO;
            }
        }
    }
    if (nonOpponent) {
        return INT_MAX;
    }
    int priority = 0;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < M; ++j) {
            if (board[j][i] == cp) {
                priority += PRIORITY_LIST[j][i];
            }
        }
    }
    return priority;
}

-(NSMutableArray*)optionalPosition:(Byte [8][8])board currentPlayerId:(Byte)cp
{
    NSMutableArray *array = [NSMutableArray new];
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < M; ++j) {
            if (board[j][i] == P) {
                BOOL flag = [self checkChessBoard:board X:i Y:j dX:-1 dY:-1 playerId:cp];
                flag = flag || [self checkChessBoard:board X:i Y:j dX:-1 dY:0 playerId:cp];
                flag = flag || [self checkChessBoard:board X:i Y:j dX:-1 dY:1 playerId:cp];
                flag = flag || [self checkChessBoard:board X:i Y:j dX:0 dY:-1 playerId:cp];
                flag = flag || [self checkChessBoard:board X:i Y:j dX:0 dY:1 playerId:cp];
                flag = flag || [self checkChessBoard:board X:i Y:j dX:1 dY:-1 playerId:cp];
                flag = flag || [self checkChessBoard:board X:i Y:j dX:1 dY:0 playerId:cp];
                flag = flag || [self checkChessBoard:board X:i Y:j dX:1 dY:1 playerId:cp];
                if (flag) {
                    [array addObject:NSStringFromCGPoint((CGPoint){i,j})];
                }
            }
            
        }
    }
    return array;
}


-(CGPoint)caculateBoard:(Byte [8][8])board currentPlayerId:(Byte)cp
{
    NSMutableArray *array = [self optionalPosition:board currentPlayerId:cp];
    CGPoint point;
    if (self.agentType == ComputeAgentRandom) {
        point = CGPointFromString([array objectAtIndex:arc4random() % array.count]);
    } else if(self.agentType == ComputeAgentMaxValue) {
        int maxChange = 0;
        for (int i = 0; i < array.count; ++i) {
            CGPoint pt = CGPointFromString([array objectAtIndex:i]);
            int changeNum = 0;
            
            changeNum += [self tryPutBoard:board X:pt.x Y:pt.y dX:-1 dY:-1 playerId:cp];
            changeNum += [self tryPutBoard:board X:pt.x Y:pt.y dX:-1 dY:0 playerId:cp];
            changeNum += [self tryPutBoard:board X:pt.x Y:pt.y dX:-1 dY:1 playerId:cp];
            changeNum += [self tryPutBoard:board X:pt.x Y:pt.y dX:0 dY:-1 playerId:cp];
            changeNum += [self tryPutBoard:board X:pt.x Y:pt.y dX:0 dY:1 playerId:cp];
            changeNum += [self tryPutBoard:board X:pt.x Y:pt.y dX:1 dY:-1 playerId:cp];
            changeNum += [self tryPutBoard:board X:pt.x Y:pt.y dX:1 dY:0 playerId:cp];
            changeNum += [self tryPutBoard:board X:pt.x Y:pt.y dX:1 dY:1 playerId:cp];
            if (changeNum > maxChange) {
                maxChange = changeNum;
                point = pt;
            }
        }
    } else if(self.agentType == ComputeAgentPriority) {
        int maxPriority = 0;
        for (int i = 0; i < array.count; ++i) {
            CGPoint pt = CGPointFromString([array objectAtIndex:i]);
            if ((pt.x == 0 && pt.y == 0) || (pt.x == M-1 && pt.y == 0) || (pt.x == 0 && pt.y == M-1) || (pt.x == M-1 && pt.y == M-1)) {
                maxPriority = INT_MAX;
                point = pt;
            } else if (pt.x == 0 || pt.y == 0 || pt.x == M-1  || pt.y == M - 1) {
                int priority = 5;
                if (!(pt.x == 1 || pt.y == 1 || pt.x == M - 2 || pt.y == M - 2)) {
                    priority = 100;
                }
                if (maxPriority < priority) {
                    maxPriority = priority;
                    point = pt;
                }
            } else {
                int priority = 10;
                if (pt.x == 1 || pt.y == 1 || pt.x == M - 2 || pt.y == M - 2) {
                    priority = 5;
                }
                if (maxPriority < priority) {
                    maxPriority = priority;
                    point = pt;
                }
            }
        }
    } else if (self.agentType == ComputeAgentPriorityAll) {
        int maxPriority = INT_MIN;
        for (int i = 0; i < array.count; ++i) {
            CGPoint pt = CGPointFromString([array objectAtIndex:i]);
            Byte newBoard[M][M];
            for (int j = 0; j < M; ++j) {
                for (int k = 0; k < M; ++k) {
                    newBoard[j][k] = board[j][k];
                }
            }
            [self setChess:pt inBoard:newBoard turn:cp];
            int priority = [self calculatePriority:newBoard playerId:cp];
            if (priority > maxPriority) {
                maxPriority = priority;
                point = pt;
            }
        }
    }
    else if (self.agentType == ComputeAgentAwesome)
    {
        NSMutableArray *positionList=[NSMutableArray new];
        positionList=[self choosePosition:board WithDepth:3 currentPlayerId:cp];
        Token *t=[positionList objectAtIndex:0];
        point=t.pos;
//        vector<Token*> tList = choosePositionWithDepth(this->status,depth);
//        return tList[0]->pos;
    }
    return point;
}
-(void)setChess:(CGPoint) pt inBoard:(Byte [8][8])newBoard turn:(Byte)cp
{
    [self tryPutBoardChange:newBoard X:pt.x Y:pt.y dX:-1 dY:-1 playerId:cp];
    [self tryPutBoardChange:newBoard X:pt.x Y:pt.y dX:-1 dY:0 playerId:cp];
    [self tryPutBoardChange:newBoard X:pt.x Y:pt.y dX:-1 dY:1 playerId:cp];
    [self tryPutBoardChange:newBoard X:pt.x Y:pt.y dX:0 dY:-1 playerId:cp];
    [self tryPutBoardChange:newBoard X:pt.x Y:pt.y dX:0 dY:1 playerId:cp];
    [self tryPutBoardChange:newBoard X:pt.x Y:pt.y dX:1 dY:-1 playerId:cp];
    [self tryPutBoardChange:newBoard X:pt.x Y:pt.y dX:1 dY:0 playerId:cp];
    [self tryPutBoardChange:newBoard X:pt.x Y:pt.y dX:1 dY:1 playerId:cp];
}

-(void)showPriority:(short [8][8])priority
{
    
    for (int i = 0; i < 8; i++) {
        NSString *str = @"";
        for (int j = 0; j < 8; ++j) {
            str = [str stringByAppendingString:[@(priority[i][j]) stringValue]];
        }
        NSLog(@"%@", str);
    }
}

-(void)getPriority:(Byte [8][8])sta priority:(short [8][8])priority currentPlayerId:(Byte)cp
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; ++j) {
            priority[i][j] = PRIORITY_LIST[i][j];
        }
    }
    if (sta[0][0] == cp) {
        priority[0][1] = priority[1][1] = priority[1][0] = priority[0][0];
    }
    if (sta[0][7] == cp) {
        priority[0][6] = priority[1][6] = priority[1][7] = priority[0][7];
    }
    if (sta[7][0] == cp) {
        priority[7][1] = priority[6][1] = priority[6][0] = priority[7][0];
    }
    if (sta[7][7] == cp) {
        priority[7][6] = priority[6][6] = priority[6][7] = priority[0][0];
    }
}

-(NSMutableArray*) choosePosition:(Byte [8][8])sta WithDepth:(int) d currentPlayerId:(Byte)cp
{
     NSMutableArray *tokenlist=[NSMutableArray new];//保存所有局面
    NSMutableArray *plist = [self optionalPosition:sta currentPlayerId:cp];//当前执方可以下的位置
    Byte cp2;
    if(cp==1)
        cp2=2;
    else
        cp2=1;
    for (int i = 0; i < plist.count; ++i)
    {
        CGPoint pt = CGPointFromString([plist objectAtIndex:i]);//可下的某一点
        Byte board1[M][M];
        for (int j = 0; j < M; ++j) {
            for (int k = 0; k < M; ++k) {
                board1[j][k] = sta[j][k];
            }
        }
        [self setChess:pt inBoard:board1 turn:cp];
        
        short opPriorityList[8][8]; // 对手的priority
        [self getPriority:board1 priority:opPriorityList currentPlayerId:cp2];
        [self showPriority:opPriorityList];
         NSMutableArray *temp = [self optionalPosition:board1 currentPlayerId:cp2];//对方可以下的位置
        if(temp.count!=0)
        {
            int bestOpWeight = -100;
            NSMutableArray* bestOptions=[NSMutableArray new];
            for(int j=0;j<temp.count;++j)
            {
                CGPoint ooPos = CGPointFromString([temp objectAtIndex:j]);
                int w=opPriorityList[(int)ooPos.x][(int)ooPos.y];
                if(w>bestOpWeight)
                {
                    bestOpWeight=w;
                    [bestOptions removeAllObjects];
                    [bestOptions addObject:NSStringFromCGPoint(ooPos)];
                }
                else if(w==bestOpWeight)
                {
                    [bestOptions addObject:NSStringFromCGPoint(ooPos)];
                }
            }
            
            for(int j=0;j<bestOptions.count;++j)
            {
                CGPoint pt2 = CGPointFromString([bestOptions objectAtIndex:j]);
                Byte board2[M][M];
                for (int j = 0; j < M; ++j) {
                    for (int k = 0; k < M; ++k) {
                        board2[j][k] = board1[j][k];
                    }
                }
                [self setChess:pt2 inBoard:board2 turn:cp2];
                
                short priorityList[8][8]; // 自己priority
                [self getPriority:board2 priority:priorityList currentPlayerId:cp];
                
                Token *t =[Token new];
                [t initWith:board2 andPosition:pt];
                t.weight=priorityList[(int)pt.x][(int)pt.y]-bestOpWeight;
                [tokenlist addObject:t];
            }
            if(bestOptions.count==0)
            {
                Token *t=[Token new];
                [t initWith:board1 andPosition:pt];
                
                short priorityList[8][8]; // 自己priority
                [self getPriority:board1 priority:priorityList currentPlayerId:cp];
                
                t.weight=priorityList[(int)pt.x][(int)pt.y];
                [tokenlist addObject:t];
            }
        }
        else//没有地方下这里有点问题，如何区分胜负
        {
            
            NSMutableArray *temp2 = [self optionalPosition:board1 currentPlayerId:cp];//自己可以下的位置
            if (temp2.count == 0) {
                // 胜负已经分了, 数一下谁的子多
                int num1 = 0;
                int num2 = 0;
                for (int j = 0; j < 8; ++j) {
                    for (int k = 0; k < 8; ++k) {
                        if (board1[j][k] == cp) {
                            num1++;
                        } else if (board1[j][k] == cp2) {
                            num2++;
                        }
                    }
                }
                Token *t=[Token new];
                [t initWith:board1 andPosition:pt];
                t.isEnd=true;
                if (num1 > num2) {
                    t.weight=9999;
                } else if (num1 < num2) {
                    t.weight = -9999;
                }
                [tokenlist addObject:t];
            } else {
                Token *t=[Token new];
                [t initWith:board1 andPosition:pt];
                
                short priorityList[8][8]; // 自己priority
                [self getPriority:board1 priority:priorityList currentPlayerId:cp];
                
                t.weight=priorityList[(int)pt.x][(int)pt.y];
                t.isEnd=true;
                [tokenlist addObject:t];
            }
            
        }
    }
    if(d<=1)
    {
        NSSortDescriptor* sortByW =[NSSortDescriptor sortDescriptorWithKey:@"weight" ascending:NO];
        NSArray *descriptors=[NSArray arrayWithObjects:sortByW, nil];
        [tokenlist sortUsingDescriptors:descriptors];
        return tokenlist;
    }
    for(int i=0;i<tokenlist.count;++i)
    {
        Token *t=[tokenlist objectAtIndex:i];
        if(!t.isEnd)
        {
            NSMutableArray *tlist=[NSMutableArray new];
            Byte nextBoard[M][M];
            for (int j = 0; j < M; ++j) {
                for (int k = 0; k < M; ++k) {
                    nextBoard[j][k] = t.status[j][k];
                }
            }
            tlist=[self choosePosition:nextBoard WithDepth:d-1 currentPlayerId:cp];
            if(tlist.count!=0)
            {
                Token *temp=[tlist objectAtIndex:0];
                t.weight+=temp.weight;
            }
        }
    }
    NSSortDescriptor* sortByW =[NSSortDescriptor sortDescriptorWithKey:@"weight" ascending:NO];
    NSArray *descriptors=[NSArray arrayWithObjects:sortByW, nil];
    [tokenlist sortUsingDescriptors:descriptors];
    return tokenlist;
}
@end
