//
//  BoardScene.h
//  ReversiProject
//
//  Created by FANXUEZHOU on 11/9/15.
//  Copyright © 2015 FANXUEZHOU. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "cocos2d.h"
#import "cocos2d-ui.h"
#import "BoardDefine.h"
@protocol BoardDataDelegate <NSObject>

-(void)cleanBoard;

-(void)showMap:(Byte[M][M])board turn:(BOOL)player1Turn;

-(void)showMapGameOver:(Byte[M][M])board;

-(void)askUserPlayer:(id)player;

@end

@protocol ControlDelegate <NSObject>

-(void)restartGame;

@end

@interface BoardScene : CCScene <BoardDataDelegate>

@property (nonatomic, weak) id<ControlDelegate> delegate;

@end
