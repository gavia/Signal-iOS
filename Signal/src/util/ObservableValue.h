#import <Foundation/Foundation.h>
#import "CollapsingFutures.h"
#import "Queue.h"

typedef void (^LatestValueCallback)(id latestValue);

/**
 *
 * An ObservableValue represents an asynchronous stream of values, such as 'latest state of toggle' or 'latest sensor reading'.
 *
 */
@interface ObservableValue : NSObject

@property (strong, readonly, atomic) id currentValue;

- (void)watchLatestValueOnArbitraryThread:(LatestValueCallback)callback
                           untilCancelled:(TOCCancelToken*)untilCancelledToken;

- (void)watchLatestValue:(LatestValueCallback)callback
                onThread:(NSThread*)thread
          untilCancelled:(TOCCancelToken*)untilCancelledToken;

@end

@interface ObservableValueController : ObservableValue

- (instancetype)initWithInitialValue:(id)value;
- (void)updateValue:(id)value;
- (void)adjustValue:(id(^)(id))adjustment;
- (void)sealValue;

@end
