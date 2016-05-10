//
//  BasePlayer.h
//  ReversiProject
//
//  Created by FANXUEZHOU on 11/11/15.
//  Copyright © 2015 FANXUEZHOU. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BoardDefine.h"
#import "BoardScene.h"

@protocol PlayerDelegate <NSObject>

@optional
-(BOOL)putChessX:(int)x Y:(int)y;

@end

@interface BasePlayer : NSObject

@property (nonatomic, weak) BoardScene *board;
@property (nonatomic, assign) int playerId;
@property (nonatomic, weak) id<PlayerDelegate> delegate;

-(void)yourTurn:(Byte[M][M])board;
-(void)clearPlayer;

@end
