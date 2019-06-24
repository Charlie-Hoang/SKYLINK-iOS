/*!
 @header SKYLINKConnectionConfig.h
 @abstract Copyright (c) 2015 Temasys. All rights reserved.
 @author Temasys
 */
#import <Foundation/Foundation.h>

/*!
 @enum
 @abstract SKYLINKVideoDevice
 @description Front camera or back camera.
 @constant Front.
 @constant Back.
 */
typedef enum SKYLINKVideoDevice {
    SKYLINKVideoDeviceFrontCamera = 1,
    SKYLINKVideoDeviceBackCamera
} SKYLINKVideoDevice;

/*!
 @enum
 @abstract SKYLINKRoomSize
 @description Specify the size of the room.
 @constant SKYLINKRoomSizeSmall Default size, if you don't specify the size.
 @constant SKYLINKRoomSizeMedium Medium.
 @constant SKYLINKRoomSizeLarge Large.
 @constant SKYLINKRoomSizeExtraLarge Extra Large.
 */
typedef enum SKYLINKRoomSize {
    SKYLINKRoomSizeSmall = 0,
    SKYLINKRoomSizeMedium,
    SKYLINKRoomSizeLarge,
    SKYLINKRoomSizeExtraLarge
} SKYLINKRoomSize;

/*!
 @class
 @discussion The class representing the conversation configuration.
 */
@interface SKYLINKConnectionConfig : NSObject

/*!
 @property
 @abstract enable/disable audio.
 @discussion Default value is NO. This is a convinience property to set both sendAudio and receiveAudio to the same value.
 */
@property (nonatomic, assign) BOOL audio;
/*!
 @property
 @abstract enable/disable video.
 @discussion Default value is NO. This is a convinience property to set both sendVideo and receiveVideo to the same value.
 */
@property (nonatomic, assign) BOOL video;
/*!
 @property
 @abstract enable/disable sending audio.
 @discussion Default value is NO.
 */
@property (nonatomic, assign) BOOL sendAudio;
/*!
 @property
 @abstract enable/disable sending audio.
 @discussion Default value is NO.
 */
@property (nonatomic, assign) BOOL receiveAudio;
/*!
 @property
 @abstract enable/disable sending video.
 @discussion Default value is NO.
 */
@property (nonatomic, assign) BOOL sendVideo;
/*!
 @property
 @abstract enable/disable receiving video.
 @discussion Default value is NO.
 */
@property (nonatomic, assign) BOOL receiveVideo;
/*!
 @property
 @abstract enable/disable dataChannel.
 @discussion Default value is NO.
 */
@property (nonatomic, assign) BOOL dataChannel;
/*!
 @property
 @abstract enable/disable file transfer.
 @discussion Default value is NO.
 */
@property (nonatomic, assign) BOOL fileTransfer;
/*!
 @property
 @abstract number of seconds for file transfer timeout.
 @discussion Default value is 60.
 */
@property (nonatomic, assign) NSInteger timeout;
/*!
 @property
 @abstract Used to limit remote peers audio media bitrate.
 @discussion Default value is 0, meaning not bitrate limit.
 */
@property (nonatomic, assign) NSInteger maxAudioBitrate;
/*!
 @property
 @abstract Used to limit remote peers video media bitrate.
 @discussion Default value is 512.
 */
@property (nonatomic, assign) NSInteger maxVideoBitrate;
/*!
 @property
 @abstract Used to limit remote peers data bitrate.
 @discussion Default value is 0, meaning not bitrate limit.
 */
@property (nonatomic, assign) NSInteger maxDataBitrate;
/*!
 @property
 @abstract Optional configuration for advanced users.
 @discussion The userInfo dictionnary key and associated settings are:
 "STUN" key (NSNumber value): set @"STUN" to @YES to DISABLE STUN server.
 "TURN" key (NSNumber value): set @"TURN" to @YES to DISABLE TURN server.
 "disableHOST" key, set @YES to disable HOST.
 "transport" key (NSString value): expected values are @"TCP" or @"UDP".
 "audio" key (NSString value): preferred audio codec, expected values are @"Opus" or @"iLBC".
 @description userInfo NSDictionary carrying the desired settings. Read the discussion for details.
 @deprecated Use -(BOOL)advancedSetting:(NSString *)settingKey setValue:(id)value instead.
 */
@property (nonatomic, weak) NSDictionary * _Null_unspecified userInfo DEPRECATED_MSG_ATTRIBUTE("Use -(BOOL)advancedSetting:(NSString *)settingKey setValue:(id)value instead.");

/*!
 @property
 @abstract xx
 @description xx
 */
@property (nonatomic, assign) BOOL autoGetStats;

/*!
 @property
 @abstract xx
 @description xx
 */
@property (nonatomic, assign) SKYLINKVideoDevice defaultVideoDevice;

/*!
 @property
 @abstract xx
 @description xx
 */
@property (nonatomic, assign) BOOL audioAutoGainControl;

/*!
 @property
 @abstract xx
 @description xx
 */
@property (nonatomic, assign) BOOL audioEchoCancellation;

/*!
 @property
 @abstract xx
 @description xx
 */
@property (nonatomic, assign) BOOL audioHighPassFilter;

/*!
 @property
 @abstract xx
 @description xx
 */
@property (nonatomic, assign) BOOL audioNoiseSuppression;

/*!
 @property
 @abstract xx
 @description xx
 */
@property (nonatomic, assign) SKYLINKRoomSize roomSize;

/*!
 @method
 @abstract Optional configuration for advanced users.
 @param settingKey the key
 @param settingValue the bool value
 @discussion The settingKey and associated settings values are:
 "STUN" key, (NSNumber value): set @"disableSTUN" to @YES to disable STUN server.
 "TURN" key, (NSNumber value): set @"disableTURN" to @YES to disable TURN server.
 "disableHOST" key, set @YES to disable HOST.
 "transport" key, (NSString value): expected values are @"TCP" or @"UDP".
 "audio" key, (NSString value): preferred audio codec, expected values are @"Opus" or @"iLBC".
 "startWithBackCamera" key, (NSNumber value): if you send the camera, this will determine the local camera to start the video capture. Default is @NO (ie: use front camera)
 "preferedCaptureSessionPresets" key, (NSArray value): ordered array of AVCaptureSessionPreset for the video capture, the first if any that can be used for the device will be picked.
 @return YES if the setting was sucessfully set (valid setting key and associated value).
 */
-(BOOL)advancedSettingKey:(null_unspecified NSString *)settingKey setValue:(null_unspecified id)settingValue;

@end

/*!
 @class
 @abstract Class representing the handshaking peer properties.
 @discussion This class is used in the delegate method called when a peer joins the room to carry informations about the joining peer media properties.
 */
@interface SKYLINKPeerMediaProperties : NSObject

/*!
 @property
 @abstract whether the peer has audio.
 */
@property (nonatomic, assign) BOOL hasAudio;
/*!
 @property
 @abstract is audio stereo.
 @discussion if 'hasAudio' returns false then this property is insignificant.
 */
@property (nonatomic, assign) BOOL isAudioStereo;
/*!
 @property
 @abstract is audio muted.
 @discussion if 'hasAudio' returns false then this property is insignificant.
 */
@property (nonatomic, assign) BOOL isAudioMuted;
/*!
 @property
 @abstract whether the peer has video
 */
@property (nonatomic, assign) BOOL hasVideo;
/*!
 @property
 @abstract is video muted.
 @discussion if 'hasVideo' returns false then this property is insignificant.
 */
@property (nonatomic, assign) BOOL isVideoMuted;
/*!
 @property
 @abstract width of the video frame.
 @discussion if 'hasVideo' returns false then this property is insignificant.
 */
@property (nonatomic, assign) NSInteger videoWidth;
/*!
 @property
 @abstract height of the video frame.
 @discussion if 'hasVideo' returns false then this property is insignificant.
 */
@property (nonatomic, assign) NSInteger videoHeight;
/*!
 @property
 @abstract frame rate of the video.
 @discussion if 'hasVideo' returns false then this property is insignificant.
 */
@property (nonatomic, assign) NSInteger videoFrameRate;

@end
