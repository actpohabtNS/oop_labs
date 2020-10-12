#ifndef IPADDRESS_H
#define IPADDRESS_H

#include <QString>

///
/// \brief The IpAddress class
///
/// Basic class of IpAddresses, intruduces general logic of IpAddresses.
///
class IpAddress {
public:
    IpAddress() = default;
    IpAddress(const QString& data);
    virtual ~IpAddress() = default;

    virtual QString QStr(int base) const = 0;
};

#endif // IPADDRESS_H
