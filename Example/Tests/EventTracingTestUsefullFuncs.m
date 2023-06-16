//
//  EventTracingTestUsefullFuncs.m
//  EventTracing-iOS_Example
//
//  Created by dl on 2022/12/13.
//  Copyright © 2022 9446796. All rights reserved.
//

#import "EventTracingTestUsefullFuncs.h"
#import <XCTest/XCTest.h>
#import <KIF/KIF.h>
#import <BlocksKit/NSObject+A2DynamicDelegate.h>

void NE_ET_Test_WaitForTimeExecBlock(NSTimeInterval timeout, NE_ET_Test_Wait_ExecBlock execBlock) {
    XCTestExpectation *expectation = [[XCTestExpectation alloc] init];
    expectation.inverted = YES;
    !execBlock ?: execBlock(expectation);
    XCTWaiterResult result = [[[XCTWaiter alloc] init] waitForExpectations:@[expectation] timeout:timeout];
    XCTAssertTrue(result == XCTWaiterResultInvertedFulfillment);
}

void NE_ET_Test_WaitForTime(NSTimeInterval timeout) {
    XCTestExpectation *expectation = [[XCTestExpectation alloc] init];
    expectation.inverted = YES;
    XCTWaiterResult result = [[[XCTWaiter alloc] init] waitForExpectations:@[expectation] timeout:timeout];
    XCTAssertTrue(result == XCTWaiterResultCompleted);
}

__attribute__((overloadable))
void NE_ET_Test_WaitForTimeAtVTreeGenerateWithCondition(NSTimeInterval timeout, NE_ET_Test_Wait_AtVTreeGenerateConditionBlock condition) {
    EventTracingTestLogComing *logComing = [EventTracingTestLogComing logComingWithRandomKey];
    NE_ET_Test_WaitForTimeAtVTreeGenerateWithCondition(timeout, logComing, condition);
}

void NE_ET_Test_WaitForTimeAtVTreeGenerateWithCondition(NSTimeInterval timeout,
                                                     EventTracingTestLogComing *logComing,
                                                     NE_ET_Test_Wait_AtVTreeGenerateConditionBlock condition) {
    NE_ET_Test_WaitForTimeExecBlock(timeout, ^(XCTestExpectation * _Nonnull expectation) {
        [[logComing bk_dynamicDelegateForProtocol:@protocol(EventTracingTestLogComingDelegate)]
         implementMethod:@selector(logComing:didOutputLogJsons:atVTreeGenerateLevel:)
         withBlock:^(EventTracingTestLogComing *logComing, NSArray<NSDictionary *> *logJsons, NEEventTracingVTree *VTree) {
            if (condition && condition(logComing)) {
                [expectation fulfill];
            }
        }];
    });
}
