//
//  ReversiData.h
//  ReversiProject
//
//  Created by FANXUEZHOU on 11/10/15.
//  Copyright © 2015 FANXUEZHOU. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BoardScene.h"
#import "BasePlayer.h"

@interface ReversiData : NSObject

@property (nonatomic, strong) id<BoardDataDelegate> delegate;

-(void)startWithPlayer1:(BasePlayer *)player1 Player2:(BasePlayer *)player2;

-(void)startGame;

@end
