//
//  KikiLocalization.m
//  kiki
//

#import <Foundation/Foundation.h>

const char * kikiLocalizedString ( const char * key )
{
    return [NSLocalizedString ([NSString stringWithCString:key], @"") cString];
}