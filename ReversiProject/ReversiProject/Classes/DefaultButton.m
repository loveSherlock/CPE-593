//
//  DefaultButton.m
//  FileTestProject
//
//  Created by FANXUEZHOU on 1/31/16.
//  Copyright © 2016 FANXUEZHOU. All rights reserved.
//

#import "DefaultButton.h"

@implementation DefaultButton


-(instancetype)initWithTitle:(NSString *)title
{
    self = [super initWithTitle:title spriteFrame: [CCSpriteFrame frameWithImageNamed:@"button_up.png"]];
    [self setValue:@(20) forKey:@"fontSize"];
    self.scale = 0.68;
    [self setHorizontalPadding:23];
    
    return self;
}

@end
