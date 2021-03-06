#import <Foundation/Foundation.h>

/**
 *
 * SequenceCounter is used to expand a 16-bit sequence number into a 64-bit sequence number.
 *
 * Works by tracking when the almost monotonically increasing id 'looops around'.
 *
**/

@interface SequenceCounter : NSObject

- (int64_t)convertNext:(uint16_t)nextShortId;

@end
