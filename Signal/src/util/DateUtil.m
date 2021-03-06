#import "DateUtil.h"
#import "Environment.h"
#import "PropertyListPreferences+Util.h"

#define ONE_DAY_TIME_INTERVAL (double)60*60*24
#define ONE_WEEK_TIME_INTERVAL (double)60*60*24*7

static NSString* const DATE_FORMAT_WEEKDAY = @"EEEE";
static NSString* const DATE_FORMAT_HOUR_MINUTE = @"h:mm a   ";

@implementation DateUtil

+ (NSDateFormatter*)dateFormatter {
    NSDateFormatter* formatter = [[NSDateFormatter alloc] init];
    [formatter setTimeStyle:NSDateFormatterShortStyle];
    return formatter;
}

+ (NSDateFormatter*)weekdayFormatter {
    NSDateFormatter* formatter = [[NSDateFormatter alloc] init];
    [formatter setDateFormat:DATE_FORMAT_WEEKDAY];
    return formatter;
}

+ (NSDateFormatter*)timeFormatter {
    NSDateFormatter* formatter = [[NSDateFormatter alloc] init];
    [formatter setDateFormat:DATE_FORMAT_HOUR_MINUTE];
    return formatter;
}

+ (BOOL)dateIsOlderThanOneDay:(NSDate*)date {
    return [[NSDate date] timeIntervalSinceDate:date] > ONE_DAY_TIME_INTERVAL;
}

+ (BOOL)dateIsOlderThanOneWeek:(NSDate*)date {
    return [[NSDate date] timeIntervalSinceDate:date] > ONE_WEEK_TIME_INTERVAL;
}

@end
