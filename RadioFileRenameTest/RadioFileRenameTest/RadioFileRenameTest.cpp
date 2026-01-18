#include <gtest/gtest.h>
#include "RadioFileRenameCore.hpp"


void mktimeTest(struct tm& t, int week) {

    t.tm_year = 2025 - 1900;  // tm_year は 1900 からの年数
    t.tm_mon = 12 - 1;        // tm_mon は 0〜11
    t.tm_mday = 14 + week;

    t.tm_hour = 0;                /* 時 */
    t.tm_min = 0;                /* 分 */
    t.tm_sec = 0;                /* 秒 */
    t.tm_isdst = -1;            /* 夏時間 */

    mktime(&t);

}

void setWeekTest(RadioInfo& test, int week) {

    test.mon = false;
    test.tue = false;
    test.wed = false;
    test.thu = false;
    test.fri = false;
    test.sat = false;
    test.sun = false;

    switch (week)
    {
    case 0:
        test.sun = true;
        break;
    case 1:
        test.mon = true;
        break;
    case 2:
        test.tue = true;
        break;
    case 3:
        test.wed = true;
        break;
    case 4:
        test.thu = true;
        break;
    case 5:
        test.fri = true;
        break;
    case 6:
        test.sat = true;
        break;

    }

}

TEST(checkValiDayWeek, 放送日と一致) {

    struct tm  t = {};
    RadioInfo test = { "放送局/番組", false, false, false, false, false, false, false };

    //日曜日(0)～土曜日(6)
    for (int i = 0; i < 6; i++) {
        mktimeTest(t, i);
        setWeekTest(test, i);

        EXPECT_EQ(checkValiDayWeek(t, test), false);
    }

}

TEST(checkValiDayWeek, 放送日と不一致) {

    struct tm  t = {};
    RadioInfo test = { "放送局/番組", false, false, false, false, false, false, false };

    //日曜日(0)～土曜日(6)
    for (int i = 0; i < 6; i++) {
        mktimeTest(t, i);

        //放送されない曜日を指定
        auto j = i + 1;
        if (j >= 6) {
            j = 0;
        }

        setWeekTest(test, j);

        EXPECT_EQ(checkValiDayWeek(t, test), true);
    }

}