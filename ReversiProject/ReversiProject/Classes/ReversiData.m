//
//  ReversiData.m
//  ReversiProject
//
//  Created by FANXUEZHOU on 11/10/15.
//  Copyright © 2015 FANXUEZHOU. All rights reserved.
//

#import "BoardDefine.h"
#import "ReversiData.h"

@interface ReversiData()<PlayerDelegate>

@end

@implementation ReversiData
{
    BasePlayer *_player1;
    BasePlayer *_player2;
    BOOL _playerTurn1;
    Byte _board[M][M];
    NSMutableArray *_playList;
}

-(void)startWithPlayer1:(BasePlayer *)player1 Player2:(BasePlayer *)player2
{
    [_player1 clearPlayer];
    [_player2 clearPlayer];
    _player1 = player1;
    _player2 = player2;
    _player1.playerId = 1;
    _player2.playerId = 2;
    _player1.delegate = self;
    _player2.delegate = self;
    [self startGame];
}

-(void)startGame
{
    _playerTurn1 = YES;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < M; ++j) {
            _board[i][j] = P;
        }
    }
    _board[3][3] = P1;
    _board[4][4] = P1;
    _board[4][3] = P2;
    _board[3][4] = P2;
    
    _playList = [NSMutableArray new];
    [_delegate cleanBoard];
    [_delegate showMap:_board turn:_playerTurn1];
    [self callStart];
}

-(void)callStart
{
    BasePlayer *player = _playerTurn1 ? _player1 : _player2;
    [player yourTurn:_board];
}

-(Byte)currentPlayer
{
    return _playerTurn1 ? P1:P2;
}

-(Byte)opponentPlayer
{
    return _playerTurn1 ? P1:P2;
}

-(BOOL)checkChessX:(int)x Y:(int)y dX:(int)dx dY:(int)dy withChange:(BOOL)change
{
    Byte cp = [self currentPlayer];
    BOOL flag = NO;
    for (int i = x + dx, j = y + dy; i >= 0 && j >= 0 && i < M && j < M; i += dx, j += dy) {
        if (_board[j][i] == P) {
            return NO;
        } else if (_board[j][i] == cp){
            if (flag && change) {
                for (int ii = x, jj = y; ii != i || jj != j; ii += dx, jj += dy) {
                    _board[jj][ii] = cp;
                }
            }
            return flag;
        } else {
            flag = YES;
        }
    }
    return NO;
}

-(BOOL)checkPlayerTurn
{
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < M; ++j) {
            if ([self putChessX:i Y:j change:NO]) {
                return YES;
            }
        }
    }
    return NO;
}

-(void)undo
{
    
}

-(BOOL)putChessX:(int)x Y:(int)y
{
    return [self putChessX:x Y:y change:YES];
}

-(BOOL)putChessX:(int)x Y:(int)y change:(BOOL)change
{
    if (x < 0 || y < 0 || x >= M || y >= M) {
        return false;
    }
    if (_board[y][x] != P) {
        return false;
    }
    BOOL flag = [self checkChessX:x Y:y dX:1 dY:0 withChange:change];
    flag = [self checkChessX:x Y:y dX: 1 dY: 1 withChange:change] || flag;
    flag = [self checkChessX:x Y:y dX: 1 dY:-1 withChange:change] || flag;
    flag = [self checkChessX:x Y:y dX: 0 dY: 1 withChange:change] || flag;
    flag = [self checkChessX:x Y:y dX: 0 dY:-1 withChange:change] || flag;
    flag = [self checkChessX:x Y:y dX:-1 dY:-1 withChange:change] || flag;
    flag = [self checkChessX:x Y:y dX:-1 dY: 0 withChange:change] || flag;
    flag = [self checkChessX:x Y:y dX:-1 dY: 1 withChange:change] || flag;
    if (!change) {
        return flag;
    } else {
        [_playList addObject:NSStringFromCGPoint((CGPoint){x,y})];
    }
    
    /// check the 
    if (flag) {
        _playerTurn1 = !_playerTurn1;
        [_delegate showMap:_board turn:_playerTurn1];
        
        // check whether next player can play.
        if (![self checkPlayerTurn]) {
            [_playList addObject:NSStringFromCGPoint((CGPoint){-1,-1})];
            NSLog(@"cannot play");
            _playerTurn1 = !_playerTurn1;
            [_delegate showMap:_board turn:_playerTurn1];
            if (![self checkPlayerTurn]) {
                // game over
                [_delegate showMapGameOver:_board];
                return flag;
            }
        }
        
        [self callStart];
    }
    return flag;
}

@end
