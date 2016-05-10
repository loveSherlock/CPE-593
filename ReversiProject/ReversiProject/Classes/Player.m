//
//  BasePlayer.m
//  ReversiProject
//
//  Created by FANXUEZHOU on 11/10/15.
//  Copyright © 2015 FANXUEZHOU. All rights reserved.
//

#import "Player.h"

@implementation Player

-(void)yourTurn:(Byte [8][8])board
{
    [self.board askUserPlayer:self];
}

-(void)putChessX:(int)x Y:(int)y
{
    [self.delegate putChessX:x Y:y];
}

@end
