//
//  ComputeAgent.h
//  ReversiProject
//
//  Created by FANXUEZHOU on 11/20/15.
//  Copyright © 2015 FANXUEZHOU. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "AIPlayer.h"

typedef NS_ENUM(Byte, ComputeAgentType) {
    ComputeAgentRandom,
    ComputeAgentMaxValue,
    ComputeAgentPriority,
    ComputeAgentPriorityAll,
    ComputeAgentAwesome,
};
@interface ComputeAgent : NSObject <ComputeDelegate>

@property (nonatomic, assign) ComputeAgentType agentType;

@end
