//
//  BoardScene.m
//  ReversiProject
//
//  Created by FANXUEZHOU on 11/9/15.
//  Copyright © 2015 FANXUEZHOU. All rights reserved.
//

#import "BoardScene.h"
#import "Player.h"
#import "DefaultButton.h"

@implementation BoardScene
{
    CCLabelTTF *_labWhiteScore;
    CCLabelTTF *_labBlackScore;
    double _scale;
    NSMutableDictionary *_dictionary;
    CCSprite *_chessBoard;
    Player *_currentPlayer;
    CCLabelTTF *_labTurn;
}

- (id)init
{
    // Apple recommend assigning self with supers return value
    self = [super init];
    
    // The thing is, that if this fails, your app will 99.99% crash anyways, so why bother
    // Just make an assert, so that you can catch it in debug
    NSAssert(self, @"Whoops");
    CGSize s = [CCDirector sharedDirector].viewSize;
    
    _chessBoard = [CCSprite spriteWithImageNamed:@"ReversiBoard.png"];
    _chessBoard.positionType = CCPositionTypeNormalized;
    _scale = s.width/ _chessBoard.contentSize.width;
    _chessBoard.scale = _scale;
    _chessBoard.position = (CGPoint){0.5, 0.5};
    CCLOG(@"%@",(NSStringFromCGSize(_chessBoard.contentSize)));
    [self addChild:_chessBoard];
    
    DefaultButton *btnBack = [[ DefaultButton alloc] initWithTitle:@"Back"];
    btnBack.positionType = CCPositionTypeNormalized;
    btnBack.position = (CGPoint){0.1,0.9};
    [btnBack setTarget:self selector:@selector(clickBack)];
    [self addChild:btnBack];
    
    CCButton *btnRestart = [ CCButton buttonWithTitle:@"Restart" fontName:nil fontSize:20];
    btnRestart.positionType = CCPositionTypeNormalized;
    btnRestart.position = (CGPoint){0.9,0.9};
    [btnRestart setTarget:self selector:@selector(clickRestart)];
    [self addChild:btnRestart];
    
    CCLabelTTF *labBlack = [CCLabelTTF labelWithString:@"Black   vs   White" fontName:nil fontSize:20];
    labBlack.color = [CCColor whiteColor];
    labBlack.positionType = CCPositionTypeNormalized;
    labBlack.position = (CGPoint){0.5,0.14};
    [self addChild:labBlack];
    
    _labBlackScore = [CCLabelTTF labelWithString:@"2" fontName:nil fontSize:20];
    _labBlackScore.positionType = CCPositionTypeNormalized;
    _labBlackScore.position = (CGPoint){0.35,0.07};
    [self addChild:_labBlackScore];
    
    _labWhiteScore = [CCLabelTTF labelWithString:@"2" fontName:nil fontSize:20];
    _labWhiteScore.positionType = CCPositionTypeNormalized;
    _labWhiteScore.position = (CGPoint){0.65,0.07};
    [self addChild:_labWhiteScore];
    
    _labTurn = [CCLabelTTF labelWithString:@"Black's turn" fontName:nil fontSize:20];
    _labTurn.positionType = CCPositionTypeNormalized;
    _labTurn.position = (CGPoint){0.5,0.85};
    [self addChild:_labTurn];
    
    
    _dictionary = [NSMutableDictionary new];
    
    //self.userInteractionEnabled = YES;
    
    return self;
}

-(CGPoint)chessPositionX:(int)i Y:(int)j
{
    CGSize s = [CCDirector sharedDirector].viewSize;
    return (CGPoint){s.width / M * (i + 0.5), s.width /M *(j - M/2 + 0.5) + s.height / 2};
}

-(void)clickBack
{
    
    [[CCDirector sharedDirector] popScene];
}

-(void)clickRestart
{
    CCLOG(@"click restart");
    [_delegate restartGame];
}

-(void)showMap:(Byte[M][M])board
{
    int whiteNumber = 0;
    int blackNumber = 0;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < M; ++j) {
            Byte b = board[i][j];
            NSString *key = [NSString stringWithFormat:@"%d_%d",i,j];
            CCSprite *chess = [_dictionary objectForKey:key];
            if(b)
            {
                if (b == P1) {
                    blackNumber++;
                } else {
                    whiteNumber++;
                }
                if (chess == nil) {
                    NSString *fileName = [NSString stringWithFormat:@"Chess%d.png",b];
                    chess = [CCSprite spriteWithImageNamed:fileName];
                    chess.position = [self chessPositionX:j Y:i];
                    chess.name = [NSString stringWithFormat:@"%d",b];
                    [self addChild:chess];
                    [_dictionary setObject:chess forKey:key];
                } else {
                    int type = [chess.name intValue];
                    if (type != b) {
                        chess.name = [NSString stringWithFormat:@"%d",b];
                        chess.texture = [CCTexture textureWithFile:[NSString stringWithFormat:@"Chess%d.png",b]];
                    }
                }
            }
        }
    }
    _labBlackScore.string = [NSString stringWithFormat:@"%d",blackNumber];
    _labWhiteScore.string = [NSString stringWithFormat:@"%d",whiteNumber];
}

-(void)showMapGameOver:(Byte[M][M])board
{
    [self showMap:board];
    int blackNumber = [_labBlackScore.string intValue];
    int whiteNumber = [_labWhiteScore.string intValue];
    if (blackNumber > whiteNumber) {
        _labTurn.string = @"Black wins";
    } else if (blackNumber < whiteNumber){
        _labTurn.string = @"white wins";
    } else {
        _labTurn.string = @"draw";
    }
}

-(void)cleanBoard
{
    for (NSString *key in _dictionary) {
        CCSprite *sprite = [_dictionary objectForKey:key];
        [sprite removeFromParent];
    }
    [_dictionary removeAllObjects];
}

-(void)showMap:(Byte [M][M])board turn:(BOOL)player1Turn
{
    if (player1Turn) {
        _labTurn.string = @"Black's turn";
    } else {
        _labTurn.string = @"White' turn";
    }
    
    [self showMap:board];
}

-(void)askUserPlayer:(id)player
{
    self.userInteractionEnabled = [player isKindOfClass:[Player class]];
    _currentPlayer = player;
}

-(void)touchBegan:(CCTouch *)touch withEvent:(CCTouchEvent *)event
{
    CGPoint point = [touch locationInNode:_chessBoard];
    CGSize s = [CCDirector sharedDirector].viewSize;
    if (point.x > 0 && point.y > 0 && point.x * _scale < s.width && point.y * _scale < s.width) {
        int x = point.x / s.width * _scale * M;
        int y = point.y / s.width * _scale * M;
        [_currentPlayer putChessX:x Y:y];
        CCLOG(@"put :  %d , %d",x,y);
    }
}

-(void)touchEnded:(CCTouch *)touch withEvent:(CCTouchEvent *)event
{
}



@end
