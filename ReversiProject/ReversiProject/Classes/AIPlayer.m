//
//  AIPlayer.m
//  ReversiProject
//
//  Created by FANXUEZHOU on 11/10/15.
//  Copyright © 2015 FANXUEZHOU. All rights reserved.
//

#import "AIPlayer.h"


@implementation AIPlayer
{
    Byte _chessBoard[M][M];
    BOOL _working;
}

-(instancetype)init
{
    if (self = [super init]) {
        _working = YES;
    }
    return self;
}

-(void)yourTurn:(Byte [M][M])board
{
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < M; ++j) {
            _chessBoard[i][j] = board[i][j];
        }
    }
    [self performSelector:@selector(compute) withObject:nil afterDelay:0.1f];
}

-(void)clearPlayer
{
    _working = NO;
}

-(void)compute
{
    if (_working) {
        [self.board askUserPlayer:self];
        CGPoint point = [_computeDelegate caculateBoard:_chessBoard currentPlayerId:self.playerId];
        BOOL goFlag = [self.delegate putChessX:point.x Y:point.y];
        if (!goFlag) {
            CCLOG(@"========= error: cannot put here %@", NSStringFromCGPoint(point));
        }
    }
    
}

@end
