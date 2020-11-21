#ifndef TIMEVAULT_H
#define TIMEVAULT_H

#include <QtGlobal>
#include <QString>

class TimeVault
{
    quint32 _hours;
    quint8 _minutes;

public:
    TimeVault();
    TimeVault(quint32 hours, quint8 minutes = 0);

    void nullify();

    QString toString() const;

    bool empty() const;

    quint32 hours() const;
    quint8 minutes() const;

    void setHours(int hours);
    void setMinutes(int minutes);

    TimeVault operator+(const TimeVault& other) const;
    TimeVault operator-(const TimeVault& other) const;
    TimeVault& operator+=(const TimeVault& other);
    TimeVault& operator-=(const TimeVault& other);
    bool operator==(const TimeVault& other);
};

#endif // TIMEVAULT_H
