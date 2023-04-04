//
//  ViewController.m
//  Process1
//
//  Created by Dio Brand on 2023/4/3.
//

#import "ViewController.h"
#include "SocketManager.h"

@interface ViewController ()<UITextFieldDelegate>

@property (weak, nonatomic) IBOutlet UITextField *input;
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
    self.navigationItem.title = @"进程间通信1";
    self.tipDict = [NSMutableDictionary dictionary];
    self.input.delegate = self;
}

- (IBAction)start:(UIButton *)sender {
    [self.view endEditing:YES];
    [self.show setText:@""];
    if(!(self.input.text.length > 0)) {
        [self showTip:@"输入框不能为空!"];
        return;
    }
//    NSLog(@"msg1:%@",self.input.text);
    const char *msg = [self.input.text UTF8String];
//    printf("msg2:%s\n",msg);
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0), ^{
        struct msg_data msg_send;
        bzero(&msg_send, sizeof(struct msg_data));
        memcpy(msg_send.msg, msg, strlen(msg));
        msg_send.len = strlen(msg);
        
        struct msg_data msg_recv;
        bzero(&msg_recv, sizeof(struct msg_data));
        int ret = send_msg(&msg_send, &msg_recv);
        if(ret < 0) {
            printf("error status = %d\n", ret);
            return;
        }
        NSString *msg_str = [NSString stringWithUTF8String:msg_recv.msg];
        NSLog(@"Receive Message:%@", msg_str);
        [self showTip:msg_str];
    });
}

-(void)showTip:(NSString * _Nonnull)tip {
    dispatch_async(dispatch_get_main_queue(), ^{
        [self.show setText:tip];
        NSLog(@"%@",tip);
    });
}

-(void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    [self.view endEditing:YES];
}

-(BOOL)textFieldShouldReturn:(UITextField *)textField {
    [textField resignFirstResponder];
    return YES;
}

@end
