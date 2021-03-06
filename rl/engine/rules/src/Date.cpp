/* This source file is part of Rastullahs Lockenpracht.
 * Copyright (C) 2003-2008 Team Pantheon. http://www.team-pantheon.de
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the Clarified Artistic License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  Clarified Artistic License for more details.
 *
 *  You should have received a copy of the Clarified Artistic License
 *  along with this program; if not you can get it here
 *  http://www.jpaulmorrison.com/fbp/artistic2.htm.
 */
#include "stdinc.h" //precompiled header

#include "Date.h"

namespace rl
{
    static const char* const MONTHS[] = { "Praios", "Rondra", "Efferd", "Travia", "Boron", "Hesinde", "Firun", "Tsa",
        "Phex", "Peraine", "Ingerimm", "Rahja", "???" };

    static const int MONTH_MODIFIER[] = { 0, 2, 4, 6, 1, 3, 5, 0, 2, 4, 6, 1, 3 };

    static const int WEEKDAY_OFFSET[] = { 2, 3, 4, 5, 6, 7, 1 };

    static const char* const DAYS_OF_WEEK[]
        = { "Windstag", "Erdtag", "Markttag", "Praiostag", "Rohalstag", "Feuertag", "Wassertag" };

    const unsigned RL_LONGLONG Date::ONE_SECOND = 1000UL;
    const unsigned RL_LONGLONG Date::ONE_MINUTE = 60000UL;
    const unsigned RL_LONGLONG Date::ONE_HOUR = 3600000UL;
    const unsigned RL_LONGLONG Date::ONE_DAY = 86400000UL;
    const unsigned RL_LONGLONG Date::ONE_WEEK = 604800000UL;
    const unsigned RL_LONGLONG Date::ONE_MONTH = 2592000000UL;
    const unsigned RL_LONGLONG Date::ONE_YEAR = 31536000000ULL;
    const unsigned RL_LONGLONG Date::ONE_AKTION = 1500UL;
    const unsigned RL_LONGLONG Date::ONE_KAMPFRUNDE = 3 * Date::ONE_SECOND;
    const unsigned RL_LONGLONG Date::ONE_SPIELRUNDE = 5 * Date::ONE_MINUTE;

    Date::Date()
    {
        mTimestamp = 0;
        calculateFields();
    }

    Date::Date(const RL_LONGLONG& timestamp)
    {
        mTimestamp = timestamp;
        calculateFields();
    }

    Date::Date(const Date& rhs)
    {
        mTimestamp = rhs.mTimestamp;
        calculateFields();
    }

    Date& Date::operator=(const Date& rhs)
    {
        if (this != &rhs)
        {
            mTimestamp = rhs.mTimestamp;
            calculateFields();
        }
        return *this;
    }

    bool Date::operator==(const Date& rhs)
    {
        return mTimestamp == rhs.mTimestamp;
    }

    bool Date::operator<(const Date& rhs)
    {
        return mTimestamp < rhs.mTimestamp;
    }

    bool Date::operator<=(const Date& rhs)
    {
        return mTimestamp <= rhs.mTimestamp;
    }

    bool Date::operator>=(const Date& rhs)
    {
        return mTimestamp >= rhs.mTimestamp;
    }

    bool Date::operator>(const Date& rhs)
    {
        return mTimestamp > rhs.mTimestamp;
    }

    Date Date::operator+(const RL_LONGLONG& rhs)
    {
        return Date(mTimestamp + rhs);
    }

    Date Date::operator+(const Date& rhs)
    {
        return Date(mTimestamp + rhs.mTimestamp);
    }

    Date Date::operator-(const RL_LONGLONG& rhs)
    {
        return Date(mTimestamp - rhs);
    }

    RL_LONGLONG Date::operator-(const Date& rhs)
    {
        return mTimestamp - rhs.mTimestamp;
    }

    Date Date::operator*(const Ogre::Real& rhs)
    {
        return Date(mTimestamp * rhs);
    }

    Date Date::operator/(const Ogre::Real& rhs)
    {
        return Date(mTimestamp / rhs); ///@todo throw exception if rhs == 0?
    }

    void Date::calculateFields()
    {
        ///@todo aufraeumen!
        mYear = mTimestamp / ONE_YEAR;
        RL_LONGLONG timeInYear = mTimestamp % ONE_YEAR;
        mMonth = timeInYear / ONE_MONTH;
        int timeInMonth = timeInYear % ONE_MONTH;
        mDayOfYear = timeInYear / ONE_DAY;
        mDayOfMonth = timeInMonth / ONE_DAY;
        int timeInDay = timeInMonth % ONE_DAY;
        mHour = timeInDay / ONE_HOUR;
        int timeInHour = timeInDay % ONE_HOUR;
        mMinute = timeInHour / ONE_MINUTE;
        int timeInMinute = timeInHour % ONE_MINUTE;
        mSecond = timeInMinute / ONE_SECOND;
        mMilli = timeInMinute % ONE_SECOND;
    }

    RL_LONGLONG Date::getTimestamp() const
    {
        return mTimestamp;
    }

    int Date::getTimeFraction() const
    {
        return mTimestamp % ONE_DAY;
    }

    int Date::getYear() const
    {
        return mYear;
    }

    int Date::getMonth() const
    {
        return mMonth + 1;
    }

    std::string Date::getMonthName() const
    {
        return std::string(MONTHS[mMonth]);
    }

    int Date::getDayOfYear() const
    {
        return mDayOfYear + 1;
    }

    int Date::getDayOfMonth() const
    {
        return mDayOfMonth + 1;
    }

    int Date::getDayOfWeek() const
    {
        int wd = ((getYear() - 993) + getDayOfMonth() + MONTH_MODIFIER[mMonth]) % 7;

        if (wd < 0)
        {
            wd += 7;
        }

        return WEEKDAY_OFFSET[wd];
    }

    std::string Date::getDayOfWeekName() const
    {
        return std::string(DAYS_OF_WEEK[getDayOfWeek() - 1]);
    }

    int Date::getHour() const
    {
        return mHour;
    }

    int Date::getMinute() const
    {
        return mMinute;
    }

    int Date::getSecond() const
    {
        return mSecond;
    }

    int Date::getMilliSecond() const
    {
        return mMilli;
    }

    const std::string Date::toString() const
    {
        char date[256];
        _snprintf(date, 255, "%s, der %d. %s im Jahre %dBF, %02d:%02d.", getDayOfWeekName().c_str(), getDayOfMonth(),
            getMonthName().c_str(), mYear, mHour, mMinute);
        return std::string(date);
    }

    const Date Date::fromReal(const Ogre::Real& time)
    {
        return Date(time / 1000.0);
    }

    const Ogre::Real Date::toReal() const
    {
        return static_cast<Ogre::Real>(mTimestamp) / 1000.0;
    }

    Date operator+(const RL_LONGLONG& lhs, const Date& rhs)
    {
        return Date(rhs.mTimestamp + lhs);
    }

    Date operator-(const RL_LONGLONG& lhs, const Date& rhs)
    {
        return Date(rhs.mTimestamp - lhs);
    }
}
