//
//  ButtonGroup.m
//  ReversiProject
//
//  Created by FANXUEZHOU on 5/7/16.
//  Copyright © 2016 FANXUEZHOU. All rights reserved.
//

#import "ButtonGroup.h"

@implementation ButtonGroup

-(instancetype)initWithList:(NSArray *)list
{
    if (self = [super init]) {
        
        self.userInteractionEnabled = YES;
        
        CGSize contentSize = [[CCDirector sharedDirector] viewSize];
        self.contentSize = contentSize;
        self.positionType = CCPositionTypeNormalized;
        self.position = ccp(0.5, 0.5);
        
        CCNodeColor *node = [CCNodeColor nodeWithColor:[CCColor colorWithRed:0 green:0 blue:0 alpha:1] width:_contentSize.width height:_contentSize.height];
        node.positionType = CCPositionTypeNormalized;
        node.anchorPoint = ccp(0.5,0.5);
        node.position = ccp(0.5, 0.5);
        
        if (node != nil) {
            [self addChild:node];
        }
        CCButton *closeButton = [CCButton buttonWithTitle:@"close"];
        [closeButton setTarget:self selector:@selector(clickCloseButton)];
        list = [list arrayByAddingObject:closeButton];

        NSUInteger buttonNumber = list.count;
        for (int i = 0; i < buttonNumber; ++i) {
            CCButton *button = [list objectAtIndex:i];
            button.positionType = CCPositionTypePoints;
            button.anchorPoint = ccp(0.5, 0.5);
            button.position = ccp(contentSize.width / 2, contentSize.height / 2 + (buttonNumber / 2.0 - i) * 30);
            [self addChild:button];
        }
    }
    return self;
}

-(void)clickCloseButton
{
    [self removeFromParent];
}

@end
