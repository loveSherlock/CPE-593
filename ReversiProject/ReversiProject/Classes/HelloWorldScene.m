//
//  HelloWorldScene.m
//
//  Created by : FANXUEZHOU
//  Project    : ReversiProject
//  Date       : 11/9/15
//
//  Copyright (c) 2015 FANXUEZHOU.
//  All rights reserved.
//
// -----------------------------------------------------------------

#import "HelloWorldScene.h"
#import "ReversiData.h"
#import "BoardScene.h"
#import "Player.h"
#import "AIPlayer.h"
#import "ComputeAgent.h"
#import "ButtonGroup.h"

// -----------------------------------------------------------------------
static BoardScene *_boardScene;
static ReversiData *_reversiData;

@interface HelloWorldScene()<ControlDelegate>
@end
@implementation HelloWorldScene
{
    CCButton *_btnPlayer1;
    CCButton *_btnPlayer2;
    ButtonGroup *_groupButton;
}

// -----------------------------------------------------------------------

- (id)init
{
    // Apple recommend assigning self with supers return value
    self = [super init];
    
    // The thing is, that if this fails, your app will 99.99% crash anyways, so why bother
    // Just make an assert, so that you can catch it in debug
    NSAssert(self, @"Whoops");
    
    // Background
    CCSprite9Slice *background = [CCSprite9Slice spriteWithImageNamed:@"white_square.png"];
    background.anchorPoint = CGPointZero;
    background.contentSize = [CCDirector sharedDirector].viewSize;
    background.color = [CCColor grayColor];
    [self addChild:background];
    
    // The standard Hello World text
    CCLabelTTF *label = [CCLabelTTF labelWithString:@"Reversi" fontName:@"ArialMT" fontSize:64];
    label.positionType = CCPositionTypeNormalized;
    label.position = (CGPoint){0.5, 0.8};
    [self addChild:label];
    
//    CCButton *btnHumanToHuman = [CCButton buttonWithTitle:@"Human VS Human" fontName:nil fontSize:14];
//    btnHumanToHuman.positionType = CCPositionTypeNormalized;
//    btnHumanToHuman.position = (CGPoint){0.5, 0.55};
//    [btnHumanToHuman setTarget:self selector:@selector(clickHumanToHuman)];
//    [self addChild:btnHumanToHuman];
//    
//    CCButton *btnHumanToComputer = [CCButton buttonWithTitle:@"Human VS Computer" fontName:nil fontSize:14];
//    btnHumanToComputer.positionType = CCPositionTypeNormalized;
//    btnHumanToComputer.position = (CGPoint){0.5, 0.35};
//    [btnHumanToComputer setTarget:self selector:@selector(clickHumanToComputer)];
//    [self addChild:btnHumanToComputer];
//    
//    CCButton *btnComputerToComputer = [CCButton buttonWithTitle:@"Computer VS Computer" fontName:nil fontSize:14];
//    btnComputerToComputer.positionType = CCPositionTypeNormalized;
//    btnComputerToComputer.position = (CGPoint){0.5, 0.15};
//    [btnComputerToComputer setTarget:self selector:@selector(clickComputerToComputer)];
//    [self addChild:btnComputerToComputer];
    
    _btnPlayer1 = [CCButton buttonWithTitle:@"Human" fontName:nil fontSize:14];
    _btnPlayer1.positionType = CCPositionTypeNormalized;
    _btnPlayer1.position = (CGPoint){0.3, 0.45};
    [_btnPlayer1 setTarget:self selector:@selector(clickChangePlayer1)];
    [self addChild:_btnPlayer1];
    
    CCLabelTTF *labelVS = [CCLabelTTF labelWithString:@"VS" fontName:nil fontSize:14];
    labelVS.positionType = CCPositionTypeNormalized;
    labelVS.position = ccp(0.5, 0.45);
    [self addChild:labelVS];
    
    _btnPlayer2 = [CCButton buttonWithTitle:@"Human" fontName:nil fontSize:14];
    _btnPlayer2.positionType = CCPositionTypeNormalized;
    _btnPlayer2.position = (CGPoint){0.7, 0.45};
    [_btnPlayer2 setTarget:self selector:@selector(clickChangePlayer2)];
    [self addChild:_btnPlayer2];
    
    CCButton *btnStart = [[CCButton alloc] initWithTitle:@"start" fontName:nil fontSize:14];
    btnStart.positionType = CCPositionTypeNormalized;
    btnStart.position = (CGPoint){0.5, 0.3};
    [btnStart setTarget:self selector:@selector(clickStart)];
    [self addChild:btnStart];
    
    // done
    return self;
}

+(BoardScene *)sharedBoardScene
{
    if (_boardScene == nil) {
        _boardScene = [[BoardScene alloc] init];
        _reversiData = [ReversiData new];
        _reversiData.delegate = _boardScene;
    }
    return _boardScene;
}

-(void)clickHumanToHuman
{
    CCLOG(@"click human vs human");
    BoardScene *board = [HelloWorldScene sharedBoardScene];
    board.delegate = self;
    Player *p1 = [Player new];
    Player *p2 = [Player new];
    p1.board = board;
    p2.board = board;
    [_reversiData startWithPlayer1:p1 Player2:p2];
    [[CCDirector sharedDirector] pushScene:board];
}

-(void)clickHumanToComputer
{
    
    CCLOG(@"click human vs computer");
    BoardScene *board = [HelloWorldScene sharedBoardScene];
    board.delegate = self;
    Player *p1 = [Player new];
    p1.board = board;
    AIPlayer *p2 = [AIPlayer new];
    p2.board = board;
    ComputeAgent *computerAgent = [ComputeAgent new];
    computerAgent.agentType = ComputeAgentAwesome;
    //computerAgent.agentType = ComputeAgentRandom;
    p2.computeDelegate = computerAgent;
    [_reversiData startWithPlayer1:p1 Player2:p2];

    [[CCDirector sharedDirector] pushScene:board];
}

-(void)clickComputerToComputer
{
    
    CCLOG(@"click computer vs computer");
    BoardScene *board = [HelloWorldScene sharedBoardScene];
    board.delegate = self;
    AIPlayer *p1 = [AIPlayer new];
    p1.board = board;
    
    ComputeAgent *computerAgent1 = [ComputeAgent new];
    computerAgent1.agentType = ComputeAgentRandom;
    p1.computeDelegate = computerAgent1;
    
    AIPlayer *p2 = [AIPlayer new];
    p2.board = board;
    
    ComputeAgent *computerAgent2 = [ComputeAgent new];
    computerAgent2.agentType = ComputeAgentAwesome;
    //computerAgent2.agentType = ComputeAgentPriorityAll;
    p2.computeDelegate = computerAgent2;
    
    [_reversiData startWithPlayer1:p1 Player2:p2];
    
    [[CCDirector sharedDirector] pushScene:board];
}

-(void)clickChangePlayer1
{
    CCButton *button1 = [CCButton buttonWithTitle:@"Huaman"];
    CCButton *button2 = [CCButton buttonWithTitle:@"Level 1"];
    CCButton *button3 = [CCButton buttonWithTitle:@"Level 2"];
    CCButton *button4 = [CCButton buttonWithTitle:@"Level 3"];
    CCButton *button5 = [CCButton buttonWithTitle:@"Level 4"];
    
    NSArray *arrayList = @[button1,button2,button3,button4,button5];
    for (int i = 0; i < arrayList.count; ++i) {
        CCButton *button = arrayList[i];
        [button setTarget:self selector:@selector(clickPlayer1:)];
    }
    
    _groupButton = [[ButtonGroup alloc] initWithList:arrayList];
    [self addChild:_groupButton];
}

-(void)clickChangePlayer2
{
    CCButton *button1 = [CCButton buttonWithTitle:@"Huaman"];
    CCButton *button2 = [CCButton buttonWithTitle:@"Level 1"];
    CCButton *button3 = [CCButton buttonWithTitle:@"Level 2"];
    CCButton *button4 = [CCButton buttonWithTitle:@"Level 3"];
    CCButton *button5 = [CCButton buttonWithTitle:@"Level 4"];
    
    NSArray *arrayList = @[button1,button2,button3,button4,button5];
    for (int i = 0; i < arrayList.count; ++i) {
        CCButton *button = arrayList[i];
        [button setTarget:self selector:@selector(clickPlayer2:)];
    }
    _groupButton = [[ButtonGroup alloc] initWithList:arrayList];
    [self addChild:_groupButton];
}

-(void)clickPlayer1:(CCButton *)button
{
    [_groupButton removeFromParent];
    _groupButton = nil;
    _btnPlayer1.title = button.title;
}

-(void)clickPlayer2:(CCButton *)button
{
    
    [_groupButton removeFromParent];
    _groupButton = nil;
    _btnPlayer2.title = button.title;
}

-(void)clickStart
{
    BoardScene *board = [HelloWorldScene sharedBoardScene];
    board.delegate = self;
    
    BasePlayer *p1;
    BasePlayer *p2;
    
    if ([_btnPlayer1.title isEqualToString:@"Human"]) {
        p1 = [Player new];
    } else {
        ComputeAgent *computerAgent1 = [ComputeAgent new];
        if ([_btnPlayer1.title isEqualToString:@"Level 1"]) {
            computerAgent1.agentType = ComputeAgentRandom;
        } else if ([_btnPlayer1.title isEqualToString:@"Level 2"]) {
            computerAgent1.agentType = ComputeAgentMaxValue;
        } else if ([_btnPlayer1.title isEqualToString:@"Level 3"]) {
            computerAgent1.agentType = ComputeAgentPriority;
        } else if ([_btnPlayer1.title isEqualToString:@"Level 4"]) {
            computerAgent1.agentType = ComputeAgentAwesome;
        }
        
        AIPlayer *aiPlayer = [AIPlayer new];
        aiPlayer.computeDelegate = computerAgent1;
        p1 = aiPlayer;
    }
    p1.board = board;
    
    if ([_btnPlayer2.title isEqualToString:@"Human"]) {
        p2 = [Player new];
        p2.board = board;
    } else {
        ComputeAgent *computerAgent1 = [ComputeAgent new];
        if ([_btnPlayer2.title isEqualToString:@"Level 1"]) {
            computerAgent1.agentType = ComputeAgentRandom;
        } else if ([_btnPlayer2.title isEqualToString:@"Level 2"]) {
            computerAgent1.agentType = ComputeAgentMaxValue;
        } else if ([_btnPlayer2.title isEqualToString:@"Level 3"]) {
            computerAgent1.agentType = ComputeAgentPriority;
        } else if ([_btnPlayer2.title isEqualToString:@"Level 4"]) {
            computerAgent1.agentType = ComputeAgentAwesome;
        }
        
        AIPlayer *aiPlayer = [AIPlayer new];
        aiPlayer.computeDelegate = computerAgent1;
        p2 = aiPlayer;
    }
    
    [_reversiData startWithPlayer1:p1 Player2:p2];
    
    [[CCDirector sharedDirector] pushScene:board];
}

-(void)restartGame
{
    [_reversiData startGame];
}

// -----------------------------------------------------------------------

@end























// why not add a few extra lines, so we dont have to sit and edit at the bottom of the screen ...
