//
//  Token.h
//  ReversiProject
//
//  Created by FANXUEZHOU on 16/4/26.
//  Copyright © 2016年 FANXUEZHOU. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AIPlayer.h"
@interface Token : NSObject

@property    NSMutableArray * status;
@property    CGPoint pos;
@property    int weight;
@property    bool isEnd;

-(void)initWith:(Byte[M][M])board andPosition:(CGPoint)position;

@end
