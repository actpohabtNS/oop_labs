#ifndef IPADDRESS_H
#define IPADDRESS_H

#include "IpAddress_types.h"

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

    virtual IA_t type() const = 0;

    virtual QString QStr(int base = 10) const = 0;
};

#endif // IPADDRESS_H
