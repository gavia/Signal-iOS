#import <Foundation/Foundation.h>
#import "RTPPacket.h"
#import "KeyAgreementParticipant.h"
#import "KeyAgreementProtocol.h"
#import "Util.h"
#import "Zid.h"

/**
 *
 * HandshakePacket represents a zrtp handshake packet, of whatever type.
 * These packets are exchanged during the zrtp handshake, to agree on crypto keys and such.
 *
 *  (embedded in RTP packet)
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |0 0 0 1|Not Used (set to zero) |         Sequence Number       |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                 Magic Cookie 'ZRTP' (0x5a525450)              |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                        Source Identifier                      |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                                                               |
 * |           ZRTP Message (length depends on Message Type)       |
 * |                            . . .                              |
 * |                                                               |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                          CRC (1 word)                         |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
**/

#define HANDSHAKE_TYPE_HELLO       @"Hello   ".encodedAsAscii
#define HANDSHAKE_TYPE_HELLO_ACK   @"HelloAck".encodedAsAscii
#define HANDSHAKE_TYPE_COMMIT      @"Commit  ".encodedAsAscii
#define HANDSHAKE_TYPE_DH_1        @"DHPart1 ".encodedAsAscii
#define HANDSHAKE_TYPE_DH_2        @"DHPart2 ".encodedAsAscii
#define HANDSHAKE_TYPE_CONFIRM_1   @"Confirm1".encodedAsAscii
#define HANDSHAKE_TYPE_CONFIRM_2   @"Confirm2".encodedAsAscii
#define HANDSHAKE_TYPE_CONFIRM_ACK @"Conf2Ack".encodedAsAscii

#define COMMIT_DEFAULT_HASH_SPEC_ID    @"S256".encodedAsAscii
#define COMMIT_DEFAULT_CIPHER_SPEC_ID  @"AES1".encodedAsAscii
#define COMMIT_DEFAULT_AUTH_SPEC_ID    @"HS80".encodedAsAscii
#define COMMIT_DEFAULT_AGREE_SPEC_ID   @"DH3k".encodedAsAscii
#define COMMIT_DEFAULT_SAS_SPEC_ID     @"B256".encodedAsAscii

#define HANDSHAKE_TRUNCATED_HMAC_LENGTH 8

@class DHPacket;
@class CommitPacket;
@class ConfirmPacket;
@class HelloPacket;
@class HelloAckPacket;
@class ConfirmAckPacket;

@interface HandshakePacket : NSObject

@property (strong, readonly, nonatomic) NSData* typeId;
@property (strong, readonly, nonatomic) NSData* payload;

- (instancetype)initWithTypeId:(NSData*)typeId andPayload:(NSData*)payload;
- (instancetype)initFromRTPPacket:(RTPPacket*)rtpPacket;
- (HandshakePacket*)withHMACAppended:(NSData*)macKey;
- (HandshakePacket*)withHMACVerifiedAndRemoved:(NSData*)macKey;

- (NSData*)dataUsedForAuthentication;
- (RTPPacket*)embeddedIntoRTPPacketWithSequenceNumber:(uint16_t)sequenceNumber
                                  usingInteropOptions:(NSArray*)interopOptions;

- (HelloPacket*)parsedAsHello;
- (HelloAckPacket*)parsedAsHelloAck;
- (CommitPacket*)parsedAsCommitPacket;
- (DHPacket*)parsedAsDH1;
- (DHPacket*)parsedAsDH2;
- (ConfirmPacket*)parsedAsConfirm1AuthenticatedWithMacKey:(NSData*)macKey andCipherKey:(NSData*)cipherKey;
- (ConfirmPacket*)parsedAsConfirm2AuthenticatedWithMacKey:(NSData*)macKey andCipherKey:(NSData*)cipherKey;
- (ConfirmAckPacket*)parsedAsConfAck;

@end
