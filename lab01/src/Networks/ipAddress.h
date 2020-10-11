#ifndef IPADDRESS_H
#define IPADDRESS_H

#include <QString>

///
/// \brief The IpAddress class
///
/// Basic class of IpAddresses, intruduces general logic of IpAddresses.
///
class IpAddress {
    IpAddress() = default;
    IpAddress(const QString& data);
    virtual ~IpAddress() = default;
};

#endif // IPADDRESS_H
