//
//  Token.m
//  ReversiProject
//
//  Created by FANXUEZHOU on 16/4/26.
//  Copyright © 2016年 FANXUEZHOU. All rights reserved.
//

#import "Token.h"

@implementation Token
-(void)initWith:(Byte[M][M])board andPosition:(CGPoint)position
{
    _status=[NSMutableArray new];
    _pos=position;
    for(int i=0;i<8;i++)
    {
        NSMutableArray *temp = [NSMutableArray new];
        for(int j=0;j<8;j++)
        {
            int x=board[i][j];
            [temp addObject:@(x)];
        }
        [_status addObject:temp];
    }
}
@end
