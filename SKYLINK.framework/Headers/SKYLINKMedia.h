/*!
 @header SKYLINKMedia.h
 @abstract Copyright (c) 2015 Temasys. All rights reserved.
 @author Temasys
 */
#import <Foundation/Foundation.h>
#import <WebRTC/WebRTC.h>

/*!
 @enum
 @abstract SKYLINKMediaType
 @description One media track(either audio or video) one SKYLINKMedia object.
 @constant SKYLINKMediaTypeAudio Audio.
 @constant SKYLINKMediaTypeVideoCamera Camera video.
 @constant SKYLINKMediaTypeVideoScreen Screen video.
 @constant SKYLINKMediaTypeVideoCustom If you implement the video capturing in your app, please use this option for the media type.
 @constant SKYLINKMediaTypeVideo This option is read only, please don't send this in.
 */
typedef enum SKYLINKMediaType {
    SKYLINKMediaTypeAudio = 0,
    SKYLINKMediaTypeVideoCamera,
    SKYLINKMediaTypeVideoScreen,
    SKYLINKMediaTypeVideoCustom,
    SKYLINKMediaTypeVideo
} SKYLINKMediaType;

/*!
 @enum
 @abstract SKYLINKMediaState
 @description The state of the SkylinkMedia object.
 @constant SKYLINKMediaStateUnavailable Unavailable.
 @constant SKYLINKMediaStateActive Cuurently active.
 @constant SKYLINKMediaStateMuted The media is muted.
 @constant SKYLINKMediaStateStopped The media stopped.
 */
typedef enum SKYLINKMediaState {
    SKYLINKMediaStateUnavailable = 0,
    SKYLINKMediaStateActive,
    SKYLINKMediaStateMuted,
    SKYLINKMediaStateStopped
} SKYLINKMediaState;

@interface SKYLINKMedia : NSObject

/*!
 @method
 @abstract Get the mediaID of the SkylinkMedia object.
 @discussion xxx.
 @return The mediaID
 */
- (nonnull NSString *)skylinkMediaID;

/*!
 @method
 @abstract Get the media type.
 @discussion xxx.
 @return The media type
 */
- (SKYLINKMediaType)skylinkMediaType;

/*!
 @method
 @abstract Gte the current media state.
 @discussion xxx.
 @return The media state
 */
- (SKYLINKMediaState)skylinkMediaState;

/*!
 @method
 @abstract Get the previous media state.
 @discussion xxx.
 @return The previous media state
 */
- (SKYLINKMediaState)skylinkPreviousMediaState;

/*!
 @method
 @abstract Get the video track if this media is an video.
 @discussion xxx.
 @return The video track, if this is media is a video
 */
- (nullable RTCVideoTrack *)skylinkVideoTrack;

/*!
 @method
 @abstract Get the audio track if this media is an audio.
 @discussion xxx.
 @return The audio track, if this is media is an audio
 */
- (nullable RTCAudioTrack *)skylinkAudioTrack;

/*!
 @method
 @abstract The video view contained in the media.
 @discussion xxx.
 @return The video view
 */
- (nullable UIView *)skylinkVideoView;

/*!
 @method
 @abstract Check if this SkylinkMedia represents a video.
 @discussion xxx.
 @return If this media is a video
 */
- (BOOL)isVideo;

/*!
 @method
 @abstract Check if this SkylinkMedia is a custom video.
 @discussion xxx.
 @return If this media is a custom video
 */
- (BOOL)isCustom;

/*!
 @method
 @abstract Get the custom video capturer.
 @discussion xxx.
 @return The custom video capturer or nil
 */
- (nullable RTCCameraVideoCapturer *)getCustomVideoCapturer;
@end

