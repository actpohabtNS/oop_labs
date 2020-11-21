#include "timevault.h"

TimeVault::TimeVault() : _hours{0}, _minutes{0} {}

TimeVault::TimeVault(quint32 hours, quint8 minutes)
    : _hours {hours}, _minutes{minutes} {}

void TimeVault::nullify()
{
    _hours = 0;
    _minutes = 0;
}

QString TimeVault::QString() const
{
    return QString::number(_hours) + " h " + QString::number(_minutes) + " m";
}

bool TimeVault::empty() const
{
    return _hours == 0 && _minutes == 0;
}

quint32 TimeVault::hours() const
{
    return _hours;
}

quint8 TimeVault::minutes() const
{
    return _minutes;
}

void TimeVault::setHours(int hours)
{
    _hours = hours;
}

void TimeVault::setMinutes(int minutes)
{
    _minutes = minutes;
}

TimeVault TimeVault::operator+(const TimeVault &other) const
{
    quint32 hSum = _hours + other._hours;
    quint8 mSum = _minutes + other._minutes;

    if (mSum >= 60) {
        mSum -= 60;
        hSum++;
    }

    return {hSum, mSum};
}

TimeVault TimeVault::operator-(const TimeVault &other) const
{
    quint32 hSum = 0;

    if (_hours >= other._hours)
        hSum = _hours - other._hours;

    quint8 mSum = 0;

    if (_minutes >= other._minutes)
        mSum = _minutes - other._minutes;
    else
        if (hSum != 0)
            hSum--;

    return {hSum, mSum};
}

void TimeVault::operator+=(const TimeVault &other)
{
    _hours += other._hours;
    _minutes += other._minutes;

    if (_minutes >= 60) {
        _minutes -= 60;
        _hours++;
    }
}

void TimeVault::operator-=(const TimeVault &other)
{
    if (_hours <= other._hours)
        _hours = 0;
    else
        _hours -= other._hours;

    if (_minutes < other._minutes) {
        _minutes = 0;

        if (_hours != 0)
            _hours--;
    }
    else
        _minutes -= other._minutes;
}

bool TimeVault::operator==(const TimeVault &other)
{
    return _hours == other._hours && _minutes == other._minutes;
}
