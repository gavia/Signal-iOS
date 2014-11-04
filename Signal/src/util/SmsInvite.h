#import <Foundation/Foundation.h>
#import <MessageUI/MessageUI.h>
#import "PhoneNumber.h"

@interface SmsInvite : NSObject <MFMessageComposeViewControllerDelegate>

@property (strong, nonatomic, readonly) UIViewController* parent;

- (instancetype)initWithParent:(UIViewController*)parent;
- (void)sendSMSInviteToNumber:(PhoneNumber*)number;

@end
