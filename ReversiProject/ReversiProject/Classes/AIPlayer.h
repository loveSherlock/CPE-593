//
//  AIPlayer.h
//  ReversiProject
//
//  Created by FANXUEZHOU on 11/10/15.
//  Copyright © 2015 FANXUEZHOU. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BasePlayer.h"

@protocol ComputeDelegate

-(CGPoint)caculateBoard:(Byte[M][M])board currentPlayerId:(Byte)cp;

@end

@interface AIPlayer : BasePlayer

@property (nonatomic, strong) id<ComputeDelegate> computeDelegate;

@end
