//
//  UIAlertController+EventTracingParams.h
//  EventTracing
//
//  Created by dl on 2021/4/25.
//

#import <UIKit/UIKit.h>
#import "EventTracingEventActionConfig.h"

NS_ASSUME_NONNULL_BEGIN

/// MARK: UIAlertControler 中的点击事件，默认 useForRefer == NO

/// 对 `UIAlertController` 层面做一些特制的扩展
@interface UIAlertAction (EventTracingParams)

/// Alert 上按钮的 oid
@property(nonatomic, copy, readonly) NSString *et_elementId;

/// Alert 按钮的position
@property(nonatomic, assign, readonly) NSUInteger et_position;

/// 判断该 Alert 按钮是否是一个 元素节点
@property(nonatomic, assign, readonly) BOOL et_isElement;

/// 当把该 AlertAction 应用到 AlertController 上时，会关联 `UIAlertController` 对象到这里
@property(nonatomic, weak, readonly) UIAlertController *et_alertController;

/// 给按钮设置 元素oid
/// - Parameters:
///   - elementId: 元素 oid
///   - params: 按钮的 参数
- (void)et_setElementId:(NSString *)elementId
                 params:(NSDictionary<NSString *, NSString *> * _Nullable)params;

/// 给按钮设置 元素 oid，同时指定position
/// - Parameters:
///   - elementId: 元素oid
///   - position: 位置信息
///   - params: 按钮的 参数
- (void)et_setElementId:(NSString *)elementId
                  position:(NSUInteger)position
                 params:(NSDictionary<NSString *, NSString *> * _Nullable)params;

/// 给按钮设置 元素 oid，同时配置按钮点击时的一些特点
/// - Parameters:
///   - elementId: 元素 oid
///   - params: 按钮的 参数
///   - block: 按钮点击的一些配置
- (void)et_setElementId:(NSString *)elementId
                 params:(NSDictionary<NSString *, NSString *> * _Nullable)params
            eventAction:(void(^ NS_NOESCAPE _Nullable)(EventTracingEventActionConfig *config))block;

/// 给按钮设置 元素 oid，同时指定position，以及配置按钮点击时的一些特点
/// - Parameters:
///   - elementId: 元素 oid
///   - position: 位置信息
///   - params: 按钮的 参数
///   - block: 按钮点击的一些配置
- (void)et_setElementId:(NSString *)elementId
                  position:(NSUInteger)position
                 params:(NSDictionary<NSString *, NSString *> * _Nullable)params
            eventAction:(void(^ NS_NOESCAPE _Nullable)(EventTracingEventActionConfig *config))block;
@end

/// 默认 Alert 会自动挂载到当前根page节点，并且设置自动挂载优先级为`最高`，放置被遮挡
@interface UIAlertController (EventTracingParams)

/// MARK: 在UIView维度，该值是默认为NO，在Alert场景，该值默认是 YES
@property(nonatomic, assign, setter=et_setIgnoreReferCascade:, getter=et_isIgnoreReferCascade) BOOL et_ignoreReferCascade;

// MARK: 在UIView维度，该值是默认为NO，在Alert场景，该值默认是 YES
@property(nonatomic, assign, setter=et_setPsreferMute:, getter=et_psreferMute) BOOL et_psreferMute;

/// 给刚刚添加进来的 `UIAlertAction` 做节点配置
/// - Parameters:
///   - elementId: 元素 oid
///   - params: 按钮的 参数
- (void)et_configLastestActionWithElementId:(NSString *)elementId
                                     params:(NSDictionary<NSString *, NSString *> * _Nullable)params;

/// 给刚刚添加进来的 `UIAlertAction` 做节点配置，同时指定按钮位置
/// - Parameters:
///   - elementId: 元素 oid
///   - position: 位置信息
///   - params: 按钮的 参数
- (void)et_configLastestActionWithElementId:(NSString *)elementId
                                      position:(NSUInteger)position
                                     params:(NSDictionary<NSString *, NSString *> * _Nullable)params;

/// 给刚刚添加进来的 `UIAlertAction` 做节点配置，以及配置按钮点击时的一些特点
/// - Parameters:
///   - elementId: 元素 oid
///   - params: 按钮的 参数
///   - block: 按钮点击的一些配置
- (void)et_configLastestActionWithElementId:(NSString *)elementId
                                     params:(NSDictionary<NSString *, NSString *> * _Nullable)params
                                eventAction:(void(^ NS_NOESCAPE _Nullable)(EventTracingEventActionConfig *config))block;

/// 给按钮设置 元素 oid，同时指定position，以及配置按钮点击时的一些特点
/// - Parameters:
///   - elementId: 元素 oid
///   - position: 位置信息
///   - params: 按钮的 参数
///   - block: 按钮点击的一些配置
- (void)et_configLastestActionWithElementId:(NSString *)elementId
                                      position:(NSUInteger)position
                                     params:(NSDictionary<NSString *, NSString *> * _Nullable)params
                                eventAction:(void(^ NS_NOESCAPE _Nullable)(EventTracingEventActionConfig *config))block;
@end

NS_ASSUME_NONNULL_END
