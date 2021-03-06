//
//  MBRequestError.h
//  MBRequest
//
//  Created by Sebastian Celis on 2/28/12.
//  Copyright (c) 2012 Mobiata, LLC. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 Common error codes for MBRequest.
 */
typedef enum {
    MBRequestErrorCodeUnknown = -1,
    MBRequestErrorCodeUnsuccessfulServerResponse = 1
} MBRequestErrorCode;

/**
 An error domain used for all MBRequest-specific errors.
 */
extern NSString * const MBRequestErrorDomain;
