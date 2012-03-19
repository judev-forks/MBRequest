# MBRequest

MBRequest is a simple networking library for iOS and OS X. It uses a [blocks-based][blocks] API built on top of [NSURLConnection][NSURLConnection] and [NSOperation][NSOperation]. MBRequest follows the style of Apple's [CLGeocoder][CLGeocoder] class to create simple, easy-to-use classes that encapsulate the entire network request. The goals of MBRequest are as follows:

* Create the simplest possible API for making network requests. With only a few lines of code, developers should be able to start a network request and pass along a single block for handling the results of that particular request.
* Give developers an extremely simple way to create their own CLGeocoder-like classes. These subclasses should only need to worry about setting up the request and parsing the response.

## Requirements

MBRequest runs on iOS 4.0 and above and OS X 10.6 and above.

MBRequest also requires [MBCommon][MBCommon]. MBCommon is included as a git submodule to this project. Or, if you'd rather, MBCommon can be downloaded directly from its [GitHub project page][MBCommon] or by running:

    $ git clone git://github.com/mobiata/MBCommon.git

## Usage

To include MBRequest in your applications, clone the MBRequest repository and include all of the MBRequest and MBCommon source files in your project.

    $ git clone --recursive git://github.com/mobiata/MBRequest.git

To reference any of the functionality defined in MBRequest, simply `#import "MBRequest.h"` at the top of your source file.

### Basic JSON Example

It is possible to use `MBJSONRequest` to quickly grab JSON data at any URL. For example, the following code will print out the titles and authors of the top-rated YouTube videos of the past week:

    NSURL *url = [NSURL URLWithString:@"https://gdata.youtube.com/feeds/api/standardfeeds/top_rated?alt=json?time=this_week"];
    NSMutableURLRequest *urlRequest = [NSMutableURLRequest requestWithURL:url];
    [urlRequest setValue:@"gzip" forHTTPHeaderField:@"Accept-Encoding"];
    MBJSONRequest *jsonRequest = [[[MBJSONRequest alloc] init] autorelease];
    [jsonRequest performJSONRequest:urlRequest completionHandler:^(id responseJSON, NSError *error) {
        if (error != nil)
        {
            NSLog(@"Error requesting YouTube data: %@", error);
        }
        else
        {
            NSArray *videos = [[responseJSON objectForKey:@"feed"] objectForKey:@"entry"];
            for (NSDictionary *videoInfo in videos)
            {
                NSString *title = [[videoInfo objectForKey:@"title"] objectForKey:@"$t"];
                NSString *author = [[[[videoInfo objectForKey:@"author"] objectAtIndex:0] objectForKey:@"name"] objectForKey:@"$t"];
                NSLog(@"'%@' by %@", title, author);
            }
        }
    }];

### Custom Request Subclass

Even though it is possible to download JSON data directly with `MBJSONRequest` (as shown in the above example), it is highly recommended that you create your own `MBJSONRequest` subclass that handles that specific request for you. It would be silly to force everyone who wants to perform a specific request to understand how to setup the request as well as parse the data that they need out of the resulting JSON object. So, we could take the previous example and instead create an `MBRYouTubeRequest` class that handles much of this for you. For an example, please see [`MBRYouTubeRequest.h`][MBRYouTubeRequest.h] and [`MBRYouTubeRequest.m`][MBRYouTubeRequest.m].

## ARC Support

MBRequest and MBCommon do not currently support [ARC (Automatic Reference Counting)][ARC]. This may change in the future. For now, if you are using ARC in your own projects, you will need to set the `-fno-objc-arc` compiler flag on all MBRequest and MBCommon files. To do this:

1. Launch Xcode for your project.
2. Navigate to the "Builds Phases" tab of your target(s).
3. Find all MBRequest and MBCommon source files and add `-fno-objc-arc` to the "Compiler Flags" column.

## JSON Support

MBCommon defines a couple of methods in `MBJSON.h` that allow MBCommon and MBRequest to easily encode and decode [JSON][JSON] strings. These methods should work without configuration and will automatically use whichever JSON library you have included in your project. Or, if your project targets OS X 10.7 (Lion) or iOS 5, you don't need to include any library as [`NSJSONSerialization`](NSJSONSerialization) can be used, instead. The currently supported JSON libraries are:

* [JSONKit][JSONKit]
* [SBJson][SBJson]

## Localization

MBRequest defines a few strings that could theoretically be shown to users. These are most often error messages placed into the `userInfo` dictionary of `NSError` objects. MBRequest uses the `MBRequestLocalizedString` macro to try and find translated versions of these strings for your users. This macro gives you a couple of choices if you decide to localize your application for languages other than English. `MBRequestLocalizedString` is defined as follows.

    #ifdef MBRequestLocalizationTable
    #define MBRequestLocalizedString(key, default) \
    [[NSBundle mainBundle] localizedStringForKey:(key) value:(default) table:MBRequestLocalizationTable]
    #else
    #define MBRequestLocalizedString(key, default) \
    [[NSBundle mainBundle] localizedStringForKey:(key) value:(default) table:nil]
    #endif

The first parameter of this macro is the string key while the second is the default (English) translation.

This macro allows you to add MBRequest strings directly to your standard `Localizable.strings` file. Or, if you wish, you can put all MBRequest strings into their own `.strings` file. If you opt for the latter, you must define `MBRequestLocalizationTable` to be the name of this file. For example, if you want to use a file called `MBRequest.strings`, you would add the following to the `Prefix.pch` file of your project:

    #define MBRequestLocalizationTable @"MBRequest"

You can look for all strings used by MBRequest by grepping for `MBRequestLocalizedString` in this project. You should see a number of hits like the following:

    NSString *msg = MBRequestLocalizedString(@"request_unsuccessful_could_not_download_image", @"Request failed. Unable to download image.");

MBCommon also defines a number of localized strings by using `MBLocalizedString` and `MBLocalizationTable.`

[blocks]: http://developer.apple.com/library/ios/documentation/cocoa/Conceptual/Blocks/Articles/00_Introduction.html
[NSURLConnection]: http://developer.apple.com/documentation/Cocoa/Reference/Foundation/Classes/nsurlconnection_Class/Reference/Reference.html
[NSOperation]: http://developer.apple.com/library/ios/documentation/Cocoa/Reference/NSOperation_class/Reference/Reference.html
[CLGeocoder]: http://developer.apple.com/library/ios/documentation/CoreLocation/Reference/CLGeocoder_class/Reference/Reference.html
[MBCommon]: https://github.com/mobiata/MBCommon
[MBRYouTubeRequest.h]: https://github.com/mobiata/MBRequest/blob/master/Example/MBRequestExample/MBRYouTubeRequest.h
[MBRYouTubeRequest.m]: https://github.com/mobiata/MBRequest/blob/master/Example/MBRequestExample/MBRYouTubeRequest.m
[ARC]: http://clang.llvm.org/docs/AutomaticReferenceCounting.html
[NSJSONSerialization]: http://developer.apple.com/library/ios/documentation/Foundation/Reference/NSJSONSerialization_Class/Reference/Reference.html
[JSONKit]: https://github.com/johnezang/JSONKit
[SBJson]: http://stig.github.com/json-framework/
[JSON]: http://json.org/
