//
//  ViewController.m
//  Process2
//
//  Created by Dio Brand on 2023/4/3.
//

#import "ViewController.h"
#include "SocketManager.h"

@interface ViewController ()

@property (weak, nonatomic) IBOutlet UILabel *show;
@property(nonatomic,strong)NSMutableDictionary *tipDict;

@end

@implementation ViewController

-(void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    [self.tipDict removeAllObjects];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    self.navigationItem.title = @"进程间通信2";
    self.tipDict = [NSMutableDictionary dictionary];
}

- (IBAction)start:(UIButton *)sender {
    //    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0), ^{
    start();
    //    });
    [self.show setText:@"服务器监听已启动!"];
}

@end
