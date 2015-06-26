#import <Foundation/Foundation.h>
#import "PNAPNSEnabledChannelsResult.h"
#import "PNAcknowledgmentStatus.h"
#import "PNErrorStatus.h"
#import "PubNub+Core.h"


#pragma mark Types

/**
 @brief  Push notifications state modification completion block.
 
 @param status Reference on status instance which hold information about processing results.
 
 @since 4.0
 */
typedef void(^PNPushNotificationsStateModificationCompletionBlock)(PNAcknowledgmentStatus *status);

/**
 @brief  Push notifications state audit completion block.
 
 @param status Reference on status instance which hold information about processing results.
 
 @since 4.0
 */
typedef void(^PNPushNotificationsStateAuditCompletionBlock)(PNAPNSEnabledChannelsResult *result,
                                                            PNErrorStatus *status);


#pragma mark - API group interface

/**
 @brief      \b PubNub client core class extension to provide access to 'APNS' API group.
 @discussion Set of API which allow to manage push notifications on separate channels.
             If push notifications has been enabled on channels, then device will start receiving 
             notifications while device inactive.
 
 @author Sergey Mamontov
 @since 4.0
 @copyright © 2009-2015 PubNub, Inc.
 */
@interface PubNub (APNS)


///------------------------------------------------
/// @name Push notifications state manipulation
///------------------------------------------------

/**
 @brief  Enabled push notifications on provided set of \c channels.
 
 @code
 @endcode
 \b Example:
 
 @code
 // Client configuration.
 PNConfiguration *configuration = [PNConfiguration configurationWithPublishKey:@"demo" 
                                                                  subscribeKey:@"demo"];
 self.client = [PubNub clientWithConfiguration:configuration];
 [self.client addPushNotificationsOnChannels:@[@"wwdc",@"google.io"] 
                         withDevicePushToken:self.devicePushToken 
                               andCompletion:^(PNAcknowledgmentStatus *status) {
 
     // Check whether request successfully completed or not.
     if (!status.isError) {
        
        // Handle successful push notification enabling on passed channels.
     }
     // Request processing failed.
     else {
     
        // Handle modification error. Check 'category' property to find out possible issue because
        // of which request did fail.
        //
        // Request can be resend using: [status retry];
     }
 }];
 @endcode
 
 @param channels  List of channel names for which push notifications should be enabled.
 @param pushToken Device push token which should be used to enabled push notifications on specified
                  set of channels.
 @param block     Push notifications addition on channels processing completion block which pass 
                  only one argument - request processing status to report about how data pushing
                  was successful or not.
 
 @since 4.0
 */
- (void)addPushNotificationsOnChannels:(NSArray *)channels withDevicePushToken:(NSData *)pushToken
                         andCompletion:(PNPushNotificationsStateModificationCompletionBlock)block;

/**
 @brief   Disable push notifications on provided set of \c channels.
 @warning If \c nil will be passed as \c channels then client will remove push notifications from 
          all channels which associated with \c pushToken.
 
 @code
 @endcode
 \b Example:
 
 @code
 // Client configuration.
 PNConfiguration *configuration = [PNConfiguration configurationWithPublishKey:@"demo" 
                                                                  subscribeKey:@"demo"];
 self.client = [PubNub clientWithConfiguration:configuration];
 [self.client removePushNotificationsFromChannels:@[@"wwdc",@"google.io"]
                              withDevicePushToken:self.devicePushToken
                                    andCompletion:^(PNAcknowledgmentStatus *status) {
 
     // Check whether request successfully completed or not.
     if (!status.isError) {
        
        // Handle successful push notification enabling on passed channels.
     }
     // Request processing failed.
     else {
     
        // Handle modification error. Check 'category' property to find out possible issue because
        // of which request did fail.
        //
        // Request can be resend using: [status retry];
     }
 }];
 @endcode
 
 @param channels  List of channel names for which push notifications should be disabled.
 @param pushToken Device push token which should be used to disable push notifications on specified
                  set of channels.
 @param block     Push notifications removal from channels processing completion block which pass 
                  only one argument - request processing status to report about how data pushing
                  was successful or not.
 
 @since 4.0
 */
- (void)removePushNotificationsFromChannels:(NSArray *)channels
                        withDevicePushToken:(NSData *)pushToken
                              andCompletion:(PNPushNotificationsStateModificationCompletionBlock)block;

/**
 @brief  Disable push notifications from all channels which is registered with specified 
         \c pushToken.
 
 @code
 @endcode
 \b Example:
 
 @code
 // Client configuration.
 PNConfiguration *configuration = [PNConfiguration configurationWithPublishKey:@"demo" 
                                                                  subscribeKey:@"demo"];
 self.client = [PubNub clientWithConfiguration:configuration];
 [self.client removeAllPushNotificationsFromDeviceWithPushToken:self.devicePushToken
                                                  andCompletion:^(PNAcknowledgmentStatus *status) {
 
     // Check whether request successfully completed or not.
     if (!status.isError) {
        
        // Handle successful push notification disabling for all channels associated with specified
        // device push token.
     }
     // Request processing failed.
     else {
     
        // Handle modification error. Check 'category' property to find out possible issue because
        // of which request did fail.
        //
        // Request can be resend using: [status retry];
     }
 }];
 @endcode
 
 @param pushToken Device push token which should be used to disable push notifications on specified
                  set of channels.
 @param block     Push notifications removal from device processing completion block which pass only
                  one argument - request processing status to report about how data pushing was 
                  successful or not.
 
 @since 4.0
 */
- (void)removeAllPushNotificationsFromDeviceWithPushToken:(NSData *)pushToken
                           andCompletion:(PNPushNotificationsStateModificationCompletionBlock)block;


///------------------------------------------------
/// @name Push notifications state audit
///------------------------------------------------

/**
 @brief  Request for all channels on which push notification has been enabled using specified
         \c pushToken.
 
 @code
 @endcode
 \b Example:
 
 @code
 // Client configuration.
 PNConfiguration *configuration = [PNConfiguration configurationWithPublishKey:@"demo" 
                                                                  subscribeKey:@"demo"];
 self.client = [PubNub clientWithConfiguration:configuration];
 [self.client pushNotificationEnabledChannelsForDeviceWithPushToken:self.devicePushToken
                              andCompletion:^(PNAPNSEnabledChannelsResult *result,
                                              PNErrorStatus *status) {
 
     // Check whether request successfully completed or not.
     if (!status.isError) {
 
        // Handle downloaded list of chanels using: result.data.channels
     }
     // Request processing failed.
     else {
     
        // Handle audition error. Check 'category' property to find out possible issue because of 
        // which request did fail.
        //
        // Request can be resend using: [status retry];
     }
 }];
 @endcode
 
 @param pushToken Device push token against which search on \b PubNub service should be performed.
 @param block     Push notifications status processing completion block which pass two arguments:
                  \c result - in case of successful request processing \c data field will contain
                  results of push notifications audit operation; \c status - in case if error
                  occurred during request processing.
 
 @since 4.0
 */
- (void)pushNotificationEnabledChannelsForDeviceWithPushToken:(NSData *)pushToken
                                  andCompletion:(PNPushNotificationsStateAuditCompletionBlock)block;

#pragma mark -


@end