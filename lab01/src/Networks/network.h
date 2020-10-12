#ifndef NETWORK_H
#define NETWORK_H

#include "ipAddress.h"

#include <QString>

///
/// \brief The Network class
///
/// The Network class represents IP addresses availible for this network.
///
class Network
{
private:
    IpAddress* _ip;
    uchar _mask;

public:
    ///
    /// \brief Network
    ///
    /// Empty constructor
    ///
    Network();

    ///
    /// \brief Network
    /// \param ip - IpAddress to serve as a host
    /// \param mask - mask in CIDR notation
    ///
    /// Basic constructor
    ///
    Network(IpAddress ip, uchar mask = 0);

    ~Network();


    ///
    /// \brief setMask
    /// \param mask - new mask to be set
    ///
    /// Updates value of Network's mask
    ///
    void setMask(uchar mask);

    ///
    /// \brief QStr
    /// \return QStr - Network's CIDR notation converted into QString
    ///
    QString QStr() const;

    ///
    /// \brief includes
    /// \param ip - IpAddress to check whether it is included into the Network
    /// \return bool - Whether ip is included into the Network
    ///
    bool includes(IpAddress ip) const;
};

#endif // NETWORK_H
