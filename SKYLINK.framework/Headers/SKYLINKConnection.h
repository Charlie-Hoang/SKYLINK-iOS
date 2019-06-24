/*!
 @header SKYLINKConnection.h
 @abstract Copyright (c) 2015 Temasys. All rights reserved.
 @author Temasys
 */
#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import "SKYLINKConnectionConfig.h"
#import "SKYLINKProtocol.h"
#import "SKYLINKMedia.h"

/*!
 @enum
 @abstract SKYLINKAssetType
 @description Asset types to help the framework read the files.
 @constant SKYLINKAssetTypeFile Files within the app sandbox.
 @constant SKYLINKAssetTypeMusic Files from the music library.
 @constant SKYLINKAssetTypePhoto Photo and Video content from the Photo Library.
 */
typedef enum SKYLINKAssetType {
    SKYLINKAssetTypeFile = 1,
    SKYLINKAssetTypeMusic,
    SKYLINKAssetTypePhoto
} SKYLINKAssetType;

extern NSString * _Nonnull const SKYLINKRequiresPermissionNotification;

@class UIView;
@class SKYLINKConnection;
@class SKYLINKPeerMediaProperties;

/*!
 @class
 @abstract The class representing the connection to the room.
 @discussion You should make sure this objects does not get released as long as you need it, for example by storing it as a strong property.
 */
@interface SKYLINKConnection : NSObject

/*!
 @name Delegates
 */

/*!
 @property
 @abstract delegate related to life cycle, implementing the SKYLINKConnectionLifeCycleDelegate protocol.
 */
@property(nonatomic, weak) id<SKYLINKConnectionLifeCycleDelegate> _Null_unspecified lifeCycleDelegate;
/*!
 @property
 @abstract delegate related to remote peer activities, implementing the SKYLINKConnectionRemotePeerDelegate protocol.
 */
@property(nonatomic, weak) id<SKYLINKConnectionRemotePeerDelegate> _Null_unspecified remotePeerDelegate;
/*!
 @property
 @abstract delegate related to audio/video media, implementing the SKYLINKConnectionMediaDelegate protocol.
 */
@property(nonatomic, weak) id<SKYLINKConnectionMediaDelegate> _Null_unspecified mediaDelegate;
/*!
 @property
 @abstract delegate related to various type of custom messages, implementing the SKYLINKConnectionMessagesDelegate protocol.
 */
@property(nonatomic, weak) id<SKYLINKConnectionMessagesDelegate> _Null_unspecified messagesDelegate;
/*!
 @property
 @abstract delegate related to file transfer, implementing the SKYLINKConnectionFileTransferDelegate protocol.
 */
@property(nonatomic, weak) id<SKYLINKConnectionFileTransferDelegate> _Null_unspecified fileTransferDelegate;
/*!
 @property
 @abstract delegate related to room recording, implementing the SKYLINKConnectionRecordingDelegate protocol.
 */
@property(nonatomic, weak) id<SKYLINKConnectionRecordingDelegate> _Null_unspecified recordingDelegate;
/**
 
 */
@property(nonatomic, weak) id<SKYLINKConnectionStatsDelegate> _Null_unspecified statsDelegate;
/*!
 @name Peer Id
 */

/*!
 @property
 @abstract peer id of the current local user
 */
@property(nonatomic, readonly) NSString * _Null_unspecified myPeerId;

/*!
 @property
 @abstract Maximun number of peers.
 @discussion The default value depends on the configuration.
 */
@property(nonatomic, assign) NSInteger maxPeerCount;

/*!
 @name Lifecycle
 */

/*!
 @method
 @abstract Initialize and return a newly allocated connection object.
 @discussion Changes in config after creating the object won't affect the connection.
 @param config The connection configuration object.
 @param appKey APP key.
 */
- (null_unspecified id)initWithConfig:(null_unspecified SKYLINKConnectionConfig *)config appKey:(null_unspecified NSString *)appKey;

/*!
 @method
 @abstract Join the room specifiying the shared secret, room name and user info.
 @discussion It is recommended to use connectToRoomWithCredentials:roomName:userInfo: after calculating the credentials on a server, but if the client application has no server implementation then this one should be used.
 @param secret Shared secret.
 @param roomName Name of the room to join.
 @param userInfo User defined information (relating to oneself). May be an NSString, NSDictionary or NSArray.
 @return NO if a connection is already established.
 */
- (BOOL)connectToRoomWithSecret:(null_unspecified NSString *)secret roomName:(null_unspecified NSString *)roomName userInfo:(null_unspecified id)userInfo;

/*!
 @method
 @abstract Join the room specifiying the calculated credential info, room name and user info.
 @discussion The dictionary 'credInfo' is expected to have 3 non-Null parameters: an NSString type 'credential', an NSDate type 'startTime' and an NSNumber type 'duration' in hours. The 'startTime' must be a correct time of the client application's timezone. Both the 'startTime' and 'duration' must be the same as the ones that were used to calculate the credential. Failing to provide any of them will result in a connection denial.
 @param credInfo A dictionary containing a credential, startTime and duration.
 @param roomName Name of the room to join.
 @param userInfo User defined information (relating to oneself). May be an NSString, NSDictionary or NSArray.
 @return nil if connection can be established otherwise a message specifying reason for connection denial.
 */
- (nonnull NSString *)connectToRoomWithCredentials:(null_unspecified NSDictionary *)credInfo roomName:(null_unspecified NSString *)roomName userInfo:(null_unspecified id)userInfo;

/*!
 @method
 @abstract Join the room specifiying the calculated string URL and user info.
 @discussion Use this method when you calculate the URL on your server with your API key, secret and room name. Allows you to avoid having those parameters in the iOS app code.
 @param stringURL Generated with room name, appKey, secret, startTime and duration. Typed NSString (not NSURL).
 @param userInfo User defined information (relating to oneself). May be an NSString, NSDictionary or NSArray.
 @return YES (success) if connection can be established. NO if a connection is already established.
 */
- (BOOL)connectToRoomWithStringURL:(null_unspecified NSString *)stringURL userInfo:(null_unspecified id)userInfo;

/*!
 @method
 @abstract Leave the room.
 @discussion Leave the room and remove any video renderers and PeerConnections.
 @param completion The completion block called on the UI thread after leaving the room. This block is a good place to deallocate SKYLINKConnection if desired. Leave as empty block if not required.
 */
- (void)disconnect:(void (^_Null_unspecified) (void))completion;

/*!
 @name Room Control.
 */

/*!
 @method
 @abstract Refresh peer connection with a specified peer.
 @discussion This method is provided as a convenience method. So that one can call if a peer streams are not behaving correctly.
 @param peerId The unique id of the peer with whom the connection is being refreshed.
 */
- (void)refreshConnection:(null_unspecified NSString *)peerId;

/*!
 @method
 @abstract Lock the room.
 */
- (void)lockTheRoom;

/*!
 @method
 @abstract Unlock the room.
 */
- (void)unlockTheRoom;

/*!
 @name Media
 */

/*!
 @method
 @abstract Mute/unmute own audio and trigger mute/unmute audio call back for all other peers.
 @param isMuted Flag to set if audio should be muted. Set to true to mute and false to unmute.
 */
- (void)muteAudio:(BOOL)isMuted;

/*!
 @method
 @abstract Mute/unmute own video and trigger mute/unmute video call back for all other peers.
 @param isMuted Flag to set if video should be muted. Set to true to mute and false to unmute.
 */
- (void)muteVideo:(BOOL)isMuted;

/*!
 @method
 @abstract Checks if own audio is currently muted.
 @return true if audio is muted and false otherwise.
 */
- (BOOL)isAudioMuted;

/*!
 @method
 @abstract Checks if own video is currently muted.
 @return true if video is muted and false otherwise.
 */
- (BOOL)isVideoMuted;

/*!
 @method
 @abstract Switches between front and back camera. By default the front camera input is captured.
 */
- (void)switchCamera;

/*!
 @name Recording (Beta)
 */

/*!
 @method
 @abstract Start the recording of the room.
 @warning This feature is in BETA.
 @discussion This is a Skylink Media Relay only feature, it needs to be enable for the API Key in Temasys developer console.
 @return The NSString return value is an error description. A nil value means no error occured.
 */
- (nullable NSString *)startRecording;

/*!
 @method
 @abstract Stop the recording of the room.
 @warning This feature is in BETA.
 @discussion This is a Skylink Media Relay only feature, it needs to be enable for the API Key in Temasys developer console.
 @return The NSString return value is an error description. A nil value means no error occured.
 */
- (nullable NSString *)stopRecording;

/*!
 @name Messaging
 */

/*!
 @method
 @abstract Send a custom message (dictionary, array or string) to a peer via signaling server.
 @discussion If the 'peerId' is not given then the message is broadcasted to all the peers.
 @param message User defined message to be sent. May be an NSString, NSDictionary or NSArray.
 @param peerId The unique id of the peer to whom the message is sent.
 */
- (void)sendCustomMessage:(null_unspecified id)message peerId:(null_unspecified NSString *)peerId;

/*!
 @method
 @abstract Send a message (dictionary, array or string) to a peer via data channel.
 @discussion If the 'peerId' is not given then the message is broadcasted to all the peers.
 @param message User defined message to be sent. May be an NSString, NSDictionary, NSArray.
 @param peerId The unique id of the peer to whom the message is sent.
 @return YES if the message has been succesfully sent to all targeted peers, if NO is returned and verbose is enabled then informations will be logged.
 */
- (BOOL)sendDCMessage:(null_unspecified id)message peerId:(null_unspecified id)peerId;

/*!
 @method
 @abstract Send binary data to a peer via data channel.
 @discussion If the 'peerId' is not given then the data is sent to all the peers. If the caller passes data object exceeding the maximum length i.e. 65456, excess bytes are truncated to the limit before sending the data on to the channel.
 @param data Binary data to be sent to the peer. The maximum size the method expects is 65456 bytes.
 @param peerId The unique id of the peer to whom the data is sent.
 */
- (void)sendBinaryData:(null_unspecified NSData *)data peerId:(null_unspecified NSString *)peerId;

/*!
 @name File Transfer
 */

/*!
 @method
 @abstract This will trigger a file permission event at a peer.
 @param fileURL The url of the file to send.
 @param assetType The type of the asset to send.
 @param peerId The unique id of the peer to whom the file would be sent.
 @exception exception An exception will be raised if there is already a file transfer being done with the same peer.
 */
- (void)sendFileTransferRequest:(null_unspecified NSURL *)fileURL assetType:(SKYLINKAssetType)assetType peerId:(null_unspecified NSString *)peerId;

/*!
 @method
 @abstract This will trigger a broadcast file permission event at all peers in the room.
 @discussion If all the data channel connections are busy in some file transfer then this message will be ignored. If one or more data channel connections are not busy in some file transfer then this will trigger a broadcast file permission event at the available peers.
 @param fileURL The url of the file to send.
 @param assetType The type of the asset to send.
 */
- (void)sendFileTransferRequest:(null_unspecified NSURL *)fileURL assetType:(SKYLINKAssetType)assetType;

/*!
 @method
 @abstract Accept or reject the file transfer request from a peer.
 @param accept Flag to specify whether the request is accepted.
 @param filename The name of the file in request.
 @param peerId The unique id of the peer who sent the file transfer request.
 */
- (void)acceptFileTransfer:(BOOL)accept filename:(null_unspecified NSString *)filename peerId:(null_unspecified NSString *)peerId;

/*!
 @method
 @abstract Cancel the existing on going transfer at anytime.
 @param filename The name of the file in request (optional).
 @param peerId The unique id of the peer with whom file is being transmitted.
 */
- (void)cancelFileTransfer:(null_unspecified NSString *)filename peerId:(null_unspecified NSString *)peerId;

/*!
 @name Miscellaneous
 */

/*!
 @method
 @abstract Update user information for every other peer and triggers user info call back at all the other peer's end.
 @param userInfo User defined information. May be an NSString, NSDictionary or NSArray.
 */
- (void)sendUserInfo:(null_unspecified id)userInfo;

/*!
 @method
 @abstract Get the cached user info for a particular peer.
 @param peerId The unique id of the peer.
 @return User defined information. May be an NSString, NSDictionary or NSArray.
 */
- (nonnull id)getUserInfo:(null_unspecified NSString *)peerId;


/*!
 @method
 @abstract Get room ID.
 @return Room ID.
 @discussion This is generally not needed.
 */
- (nonnull NSString *)roomId;


/*!
 @name Utility
 */

/*!
 @method
 @abstract Get the version string of this Skylink SDK for iOS.
 @return Version string of this Skylink SDK for iOS.
 */
+ (nonnull NSString *)getSkylinkVersion;

/*!
 @method
 @abstract Enable/disable verbose logs for all the connections.
 @warning You should always disable logs in RELEASE mode.
 @param verbose enable/disable verbose logs. Default is NO.
 */
+ (void)setVerbose:(BOOL)verbose;


/*!
 @method
 @abstract Calculate credentials to be used by the connection.
 @param roomName Name of the room.
 @param duration Duration of the call in hours.
 @param startTime Start time of the call as per client application time zone.
 @param secret The shared secret.
 @return The calculated credential string.
 */
+ (nonnull NSString *)calculateCredentials:(null_unspecified NSString *)roomName duration:(null_unspecified NSNumber *)duration startTime:(null_unspecified NSDate *)startTime secret:(null_unspecified NSString *)secret;

/*!
 @method
 @abstract xx
 @param width <#width description#>
 @param height <#height description#>
 @param fps <#fps description#>
 @param callback <#callback description#>
 */
- (void)setInputVideoResolutionToWidth:(NSUInteger)width height:(NSUInteger)height fps:(NSUInteger)fps callback:(void (^ _Null_unspecified) (void))callback;

/*!
 @method
 @abstract xx
 @param callback <#callback description#>
 */
- (void)getInputVideoResolutionCallback:(void (^ _Null_unspecified) (id _Nonnull responseObject, NSInteger width, NSInteger height, NSInteger fps))callback;

/*!
 @method
 @abstract xx
 @param peerID <#peerID description#>
 @param callback <#callback description#>
 */
- (void)getReceivedVideoResolutionOfPeerID:(nullable NSString *)peerID callback:(void (^ _Null_unspecified) (id _Nonnull responseObject, NSInteger width, NSInteger height, NSInteger fps))callback;

/*!
 @method
 @abstract xx
 @param peerID <#peerID description#>
 @param callback <#callback description#>
 */
- (void)getSentVideoResolutionOfPeerID:(nullable NSString *)peerID callback:(void (^ _Null_unspecified) (id _Nonnull responseObject, NSInteger width, NSInteger height, NSInteger fps))callback;

/*!
 @method
 @abstract xx
 @param callback <#callback description#>
 */
- (void)getCaptureFormatCallback:(void (^ _Null_unspecified) (AVCaptureDeviceFormat * _Null_unspecified format))callback;

/*!
 @method
 @abstract xx
 @param callback <#callback description#>
 */
- (void)getCaptureFormatsCallback:(void (^ _Null_unspecified) (NSArray<AVCaptureDeviceFormat *> * _Null_unspecified formats))callback;

/*!
 @method
 @abstract xx
 @param callback <#callback description#>
 */
- (void)getCurrentVideoDeviceCallback:(void (^ _Null_unspecified) (AVCaptureDevice * _Null_unspecified device))callback;

/*!
 @method
 @abstract xx
 @param callback <#callback description#>
 */
- (void)getCurrentCameraNameCallback:(void (^ _Null_unspecified) (NSString * _Null_unspecified name))callback;

/*!
 @method
 @abstract xx
 @param peerID <#peerID description#>
 @param callback <#callback description#>
 */
- (void)getFullStatsReportOfPeerID:(nullable NSString *)peerID callback:(void (^ _Null_unspecified) (id _Nonnull responseObject))callback;

/*!
 @method
 @abstract xx
 @param viewController <#viewController description#>
 @param callback <#callback description#>
 */
//- (void)startInAppScreenSharingFromViewController:(UIViewController * _Nonnull)viewController callback:(void (^ _Null_unspecified) (NSError * _Nullable error))callback;

/*!
 @method
 @abstract xx
 @param callback <#callback description#>
 */
//- (void)stopInAppScreenSharingWithCallback:(void (^ _Null_unspecified) (NSError * _Nullable error))callback;

/*!
 @method
 @abstract xx
 @param sampleBuffer <#sampleBuffer description#>
 */
- (void)processSampleBuffer:(CMSampleBufferRef _Nonnull)sampleBuffer;

- (void)startLocalMediaWithMediaType:(SKYLINKMediaType)mediaType fromViewController:(UIViewController * _Null_unspecified)viewController callback:(void (^ _Null_unspecified) (NSError * _Nullable error))callback;

- (void)stopLocalMediaWithMeidaID:(NSString * _Nonnull)mediaID callback:(void (^ _Null_unspecified) (NSError * _Nullable error))callback;

- (void)toggleLocalMeidaWithMeidaID:(NSString * _Nonnull)mediaID isPause:(BOOL)isPause callback:(void (^ _Null_unspecified) (NSError * _Nullable error))callback;

- (void)muteLocalMediaWithMeidaID:(NSString * _Nonnull)mediaID mute:(BOOL)mute callback:(void (^ _Null_unspecified) (NSError * _Nullable error))callback;
// pass the custom video capture
- (void)sendVideoCapturer:(RTCCameraVideoCapturer * _Nonnull)videoCapturer callback:(void (^ _Null_unspecified) (NSError * _Nullable error))callback;;

@end
