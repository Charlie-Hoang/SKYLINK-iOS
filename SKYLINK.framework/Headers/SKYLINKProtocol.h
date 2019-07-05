/*!
 @header SKYLINKProtocol.h
 @abstract Copyright (c) 2015 Temasys. All rights reserved.
 @author Temasys
 */
#ifndef SKYLINKProtocol_h
#define SKYLINKProtocol_h
@class SKYLINKConnection, SKYLINKMedia;
// All the messages of the following protocols are sent on the main thread

/*!
 @protocol
 @abstract Protocol to receive events related to the lifecycle of the connection.
 @discussion Delegate methods are called on the main thread.
 */
@protocol SKYLINKConnectionLifeCycleDelegate <NSObject>

@optional

/*!
 @method
 @abstract First delegate method called on the delegate upon successful or unsuccessful connection.
 @discussion If the connection is successfull, this method gets called just before the connection notifies the other peers in the room that the local user entered it.
 @param connection The underlying connection object.
 @param errorMessage Error message in case the connection is unsuccessful.
 @param isSuccess Flag to specify whether the connection was successful.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didConnectWithMessage:(null_unspecified NSString *)errorMessage success:(BOOL)isSuccess;

/*!
 @method
 @abstract Called upon successful capturing and rendering of the local front camera.
 @param connection The underlying connection object.
 @param userVideoView The video view of the connecting client.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didRenderUserVideo:(null_unspecified UIView *)userVideoView;

/*!
 @method
 @abstract Called when a remote peer locks/unlocks the room.
 @param connection The underlying connection object.
 @param lockStatus The status of the lock.
 @param peerId The unique id of the peer who originated the action.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didLockTheRoom:(BOOL)lockStatus peerId:(null_unspecified NSString *)peerId;

/*!
 @method
 @abstract Called when a warning is received from the underlying system.
 @param connection The underlying connection object.
 @param message Warning message from the underlying system.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didReceiveWarning:(null_unspecified NSString *)message;

/*!
 @method
 @abstract Called when the client is disconnected from the server.
 @param connection The underlying connection object.
 @param errorMessage Message specifying the reason of disconnection.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didDisconnectWithMessage:(null_unspecified NSString *)errorMessage;

@end

/*!
 @protocol
 @abstract Protocol to receive events related to remote peers.
 @discussion Delegate methods are called on the main thread.
 */
@protocol SKYLINKConnectionRemotePeerDelegate <NSObject>

@optional

/*!
 @method
 @abstract Called when a remote peer joins the room.
 @param connection The underlying connection object.
 @param userInfo User defined information. May be an NSString, NSDictionary or NSArray.
 @param pmProperties An object defining peer media properties of the joining peer.
 @param peerId The unique id of the joining peer.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didJoinPeer:(null_unspecified id)userInfo mediaProperties:(null_unspecified SKYLINKPeerMediaProperties *)pmProperties peerId:(null_unspecified NSString *)peerId;

/*!
 @method
 @abstract Called upon receiving a remote video stream.
 @param connection The underlying connection object.
 @param peerVideoView The video view of the joining peer.
 @param peerId The unique id of the peer.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didRenderPeerVideo:(null_unspecified UIView *)peerVideoView peerId:(null_unspecified NSString *)peerId;

/*!
 @method
 @abstract Called upon receiving an update about a user info.
 @param connection The underlying connection object.
 @param userInfo User defined information. May be an NSString, NSDictionary or NSArray.
 @param peerId The unique id of the peer.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didReceiveUserInfo:(null_unspecified id)userInfo peerId:(null_unspecified NSString *)peerId;

/*!
 @method
 @abstract Called when a peer has left the room implictly or explicitly.
 @param connection The underlying connection object.
 @param errorMessage Error message in case the peer is left due to some error.
 @param peerId The unique id of the leaving peer.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didLeavePeerWithMessage:(null_unspecified NSString *)errorMessage peerId:(null_unspecified NSString *)peerId;

@end

/*!
 @protocol
 @abstract Protocol to receive events related to media i.e. audio/video.
 @discussion Delegate methods are called on the main thread.
 */
@protocol SKYLINKConnectionMediaDelegate <NSObject>

@optional

/*!
 @method
 @abstract Called when the dimensions of the video view are changed.
 @param connection The underlying connection object.
 @param videoSize The size of the respective video.
 @param videoView The video view for which the size was sent.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didChangeVideoSize:(CGSize)videoSize videoView:(null_unspecified UIView *)videoView;

/*!
 @method
 @abstract Called when a peer mutes/unmutes its audio.
 @param connection The underlying connection object.
 @param isMuted Flag to specify whether the audio is muted.
 @param peerId The unique id of the peer.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didToggleAudio:(BOOL)isMuted peerId:(null_unspecified NSString *)peerId;

/*!
 @method
 @abstract Called when a peer mutes/unmutes its video.
 @param connection The underlying connection object.
 @param isMuted Flat to specify whether the video is muted.
 @param peerId The unique id of the peer.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didToggleVideo:(BOOL)isMuted peerId:(null_unspecified NSString *)peerId;

/*!
 @method
 @abstract Called when a peer mutes/unmutes its video.
 @param connection The underlying connection object.
 @param skylinkMedia The Skylink media object that is changed.
 @param peerId The unique id of the peer.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didChangeSkylinkMedia:(nonnull SKYLINKMedia *)skylinkMedia peerId:(null_unspecified NSString *)peerId;

/*!
 @method
 @abstract Called when a peer mutes/unmutes its video.
 @param connection The underlying connection object.
 @param videoSize The new video size.
 @param skylinkMedia The Skylink media object that is changed.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didChangeVideoSize:(CGSize)videoSize ofSkylinkMeida:(nonnull SKYLINKMedia *)skylinkMedia;

/*!
 @method
 @abstract Called when a peer mutes/unmutes its video.
 @param connection The underlying connection object.
 @param localMedia The newly created local Skylink media object.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didCreateLocalMedia:(nonnull SKYLINKMedia *)localMedia;
@end

/*!
 @protocol
 @abstract Protocol to receive events related to remote peer messages.
 @discussion Delegate methods are called on the main thread.
 */
@protocol SKYLINKConnectionMessagesDelegate <NSObject>

@optional

/*!
 @method
 @abstract Called upon receiving a private or public message.
 @param connection The underlying connection object.
 @param message User defined message. May be an NSString, NSDictionary or NSArray.
 @param isPublic Flag to specify whether the message was a broadcast.
 @param peerId The unique id of the peer.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didReceiveCustomMessage:(null_unspecified id)message public:(BOOL)isPublic peerId:(null_unspecified NSString *)peerId;

/*!
 @method
 @abstract Called upon receiving a data channel chat message.
 @param connection The underlying connection object.
 @param message User defined message. May be an NSString, NSDictionary or NSArray.
 @param isPublic Flag to specify whether the message was a broadcast.
 @param peerId The unique id of the peer.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didReceiveDCMessage:(null_unspecified id)message public:(BOOL)isPublic peerId:(null_unspecified NSString *)peerId;


/*!
 @method
 @abstract Called when receving a data channel message
 @param connection The underlying connection object.
 @param message User defined message. May be an NSString, NSDictionary or NSArray.
 @param isPrivate Flag to specify whether the message was private.
 @param sender The message sender
 @param targets The message receiver
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didReceiveDCMessage:(null_unspecified id)message isPrivate:(BOOL)isPrivate sender:(null_unspecified NSString *)sender targets:(null_unspecified id)targets;

/*!
 @method
 @abstract Called upon receiving binary data on data channel.
 @param connection The underlying connection object.
 @param data Binary data.
 @param peerId The unique id of the peer.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didReceiveBinaryData:(null_unspecified NSData *)data peerId:(null_unspecified NSString *)peerId;

@end

/*!
 @protocol
 @abstract Protocol to receive events related to file transfer.
 @discussion Delegate methods are called on the main thread.
 */
@protocol SKYLINKConnectionFileTransferDelegate <NSObject>

@optional

/*!
 @method
 @abstract Called upon receiving a file transfer request from a peer.
 @param connection The underlying connection object.
 @param filename The name of the file in request.
 @param peerId The unique id of the peer.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didReceiveRequest:(null_unspecified NSString *)filename peerId:(null_unspecified NSString *)peerId;

/*!
 @method
 @abstract Called upon receiving a file transfer permission from a peer.
 @param connection The underlying connection object.
 @param isPermitted Flag to specify whether the request was accepted.
 @param filename The name of the file in request.
 @param peerId The unique id of the peer.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didReceivePermission:(BOOL)isPermitted filename:(null_unspecified NSString *)filename peerId:(null_unspecified NSString *)peerId;

/*!
 @method
 @abstract Called when the file being transferred is halted.
 @param connection The underlying connection object.
 @param filename The name of the file in request.
 @param message The message specifying reason for the file transfer drop.
 @param isExplicit Flag to specify whether the transfer was halted explicity by the sender.
 @param peerId The unique id of the peer.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didDropTransfer:(null_unspecified NSString *)filename reason:(null_unspecified NSString *)message isExplicit:(BOOL)isExplicit peerId:(null_unspecified NSString *)peerId;

/*!
 @method
 @abstract Called upon every file transfer progress update.
 @param connection The underlying connection object.
 @param percentage The perccentage representing the progress of the transfer (CGFloat from 0 to 1).
 @param isOutgoing Boolean to specify if the transfer is a file beign sent (value would be YES) or received (value would be NO).
 @param filename The name of the file in transmission.
 @param peerId The unique id of the peer thie file is sent to or received from.
 @discussion Alternatively, if many of your objects need to get these informations, it can register to the notification with identifier: @"SKYLINKFileProgress".
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didUpdateProgress:(CGFloat)percentage isOutgoing:(BOOL)isOutgoing filename:(null_unspecified NSString *)filename peerId:(null_unspecified NSString *)peerId;


/*!
 @method
 @abstract Called upon file transfer completion.
 @param connection The underlying connection object.
 @param filename The name of the file in request.
 @param fileData NSData object holding the data transferred.
 @param peerId The unique id of the peer.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didCompleteTransfer:(null_unspecified NSString *)filename fileData:(null_unspecified NSData *)fileData peerId:(null_unspecified NSString *)peerId;

@end

/*!
 @protocol
 @abstract Protocol to receive backend events related to room recording (BETA).
 @discussion This works only on Skylink Media Relay enabled App Keys. Delegate methods are called on the main thread.
 */
@protocol SKYLINKConnectionRecordingDelegate <NSObject>

@optional

/*!
 @method
 @abstract Called upon recording start event.
 @warning This feature is in BETA.
 @param connection The underlying connection object.
 @param recordingID The id of the generated recording.
 @discussion This will be triggered after you call startRecording successfully.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection recordingDidStartWithID:(null_unspecified NSString *)recordingID;

/*!
 @method
 @abstract Called upon recording stop event.
 @warning This feature is in BETA.
 @param connection The underlying connection object.
 @param recordingID The id of the recording.
 @discussion This will be triggered after you call stopRecording successfully or if the backend notifies of recording stoped.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection recordingDidStopWithID:(null_unspecified NSString *)recordingID;

/*!
 @method
 @abstract Called upon recording error event.
 @warning This feature is in BETA.
 @param connection The underlying connection object.
 @param recordingID The id of the recording (might be nil if unknown).
 @param errorMessage The error description as a string.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection recording:(null_unspecified NSString *)recordingID didError:(null_unspecified NSString *)errorMessage;

/*!
 @method
 @abstract Called upon recording completion event.
 @warning This feature is in BETA.
 @param connection The underlying connection object.
 @param recordingId The id of the recording.
 @param videoLink The mixing recording URL as a string.
 @param peerId The peerId who's recording the link is for. If nil then the URL is a mixin recording link.
 @discussion For this to be called you need to make sure the app key used is configured for recording.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection recordingVideoLink:(null_unspecified NSString *)videoLink peerId:(null_unspecified NSString *)peerId recordingId:(null_unspecified NSString *)recordingId;

@end

@protocol SKYLINKConnectionStatsDelegate <NSObject>

@optional

/*!
 @method
 @abstract Called if the remote peer's stats are changed
 @param connection The underlying connection object.
 @param statsDict The stats dictionary
 @param peerID The peer id that is changed
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didChangeStats:(nonnull NSDictionary<NSString *, id> *)statsDict ofPeerID:(nonnull NSString *)peerID;

/*!
 @method
 @abstract Called when the remote peer's input stats are changed
 @param connection The underlying connection object.
 @param statsDict The stats dictionary
 @param width The video width
 @param height The video height
 @param fps The video frame rate
 @param peerID The peer id for the input stats
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didInputVideoResolutionChange:(nonnull NSDictionary<NSString *, id> *)statsDict width:(NSInteger)width height:(NSInteger)height fps:(NSInteger)fps ofPeerID:(nonnull NSString *)peerID;

/*!
 @method
 @abstract Called when the received stats are changed
 @param connection The underlying connection object.
 @param statsDict The stats dictionary
 @param width The video width
 @param height The video height
 @param fps The video frame rate
 @param peerID The peer id for the input stats
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didReceivedVideoResolutionChange:(nonnull NSDictionary<NSString *, id> *)statsDict width:(NSInteger)width height:(NSInteger)height fps:(NSInteger)fps ofPeerID:(nonnull NSString *)peerID;

/*!
 @method
 @abstract Called when the sent stats are changed
 @param connection The underlying connection object.
 @param statsDict The stats dictionary
 @param width The video width
 @param height The video height
 @param fps The video frame rate
 @param peerID The peer id for the input stats
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didSentVideoResolutionChange:(nonnull NSDictionary<NSString *, id> *)statsDict width:(NSInteger)width height:(NSInteger)height fps:(NSInteger)fps ofPeerID:(nonnull NSString *)peerID;
@end

#endif /* SKYLINKProtocol_h */
