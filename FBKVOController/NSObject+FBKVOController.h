/**
  Copyright (c) 2014-present, Facebook, Inc.
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree. An additional grant
  of patent rights can be found in the PATENTS file in the same directory.
 */

#import <Foundation/Foundation.h>

#import "FBKVOController.h"

NS_ASSUME_NONNULL_BEGIN

/**
 Category that adds built-in `KVOController` and `KVOControllerNonRetaining` on any instance of `NSObject`.

 This makes it convenient to simply create and forget a `FBKVOController`, 
 and when this object gets dealloc'd, so will the associated controller and the observation info.
 */
@interface NSObject (FBKVOController)

/**
 @abstract Lazy-loaded FBKVOController for use with any object
 @return FBKVOController associated with this object, creating one if necessary
 @discussion This makes it convenient to simply create and forget a FBKVOController, and when this object gets dealloc'd, so will the associated controller and the observation info.
 */
//适合正常用法：
//通过AssociatedObject给NSObject提供一个retain类型的FBKVOController
@property (nonatomic, strong) FBKVOController *KVOController;

/**
 @abstract Lazy-loaded FBKVOController for use with any object
 @return FBKVOController associated with this object, creating one if necessary
 @discussion This makes it convenient to simply create and forget a FBKVOController.
 Use this version when a strong reference between controller and observed object would create a retain cycle.
 When not retaining observed objects, special care must be taken to remove observation info prior to deallocation of the observed object.
 */
//适合[self observe self]的情况：
//通过AssociatedObject给NSObject提供一个非retain类型的FBKVOController
//需要手动调用removeObserver或者self.KVOControllerNonRetaining unobserve:
//另外，这种self observe self实在没有必要用kvo，直接在setter方法中处理即可嘛；

/*
//注意：要在dealloc方法走之前 remove observation，didMoveToSuperview方法正好合适
 - (void)didMoveToSuperview
 {
     [super didMoveToSuperview];
     if (self.superview) {
         [self.KVOControllerNonRetaining observe:self keyPath: ...]
     }else {
         [self.KVOControllerNonRetaining unobserve:self];
     }
 }
*/
@property (nonatomic, strong) FBKVOController *KVOControllerNonRetaining;

@end

NS_ASSUME_NONNULL_END
