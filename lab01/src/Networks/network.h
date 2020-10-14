#ifndef NETWORK_H
#define NETWORK_H

#include "ipAddress.h"
#include "IpAddress_types.h"

#include <QString>
#include <QTextStream>

#include <memory>

using sh_ptr_ip = std::shared_ptr<IpAddress>;

///
/// \brief The Network class
///
/// The Network class represents IP addresses availible for this network.
///
class Network
{
private:
    sh_ptr_ip _ip;
    uchar _mask;

    ///
    /// \brief _minOrMax
    /// \param min - Defines whether we look for min element or max
    /// \return std::shared_ptr<IpAddress> - Pointer to min or max IpAddress of the Network
    ///
    sh_ptr_ip _minOrMax(bool min) const;

public:
    ///
    /// \brief Network
    ///
    /// Empty constructor
    ///
    Network();

    ///
    /// \brief Network
    /// \param ip - std::shared_ptr to IpAddress to serve as a host
    /// \param mask - mask in CIDR notation
    ///
    /// Basic overloaded constructor for std::shared_ptr
    ///
    Network(sh_ptr_ip ip, uchar mask = 0);

    ~Network() = default;


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
    /// \brief min
    /// \return std::shared_ptr<IpAddress> - Pointer to minimum IpAddress in this network
    ///
    sh_ptr_ip min() const;

    ///
    /// \brief min
    /// \return std::shared_ptr<IpAddress> - Pointer to maximum IpAddress in this network
    ///
    sh_ptr_ip max() const;

    ///
    /// \brief includes
    /// \param ip - Pointer to IpAddress to check whether it is included into the Network
    /// \return bool - Whether ip is included into the Network
    ///
    bool includes(const IpAddress* ip) const;

    ///
    /// \brief maxMaskLength
    /// \param type - type of IpAddress
    /// \return uchar - max length of mask for this IpAddress type
    ///
    uchar maxMaskLength(IpAddress_type type) const;


    ///
    /// \brief operator <<
    /// \param ostream - QTextStream
    /// \return ostream& - reference to QTextSteam
    ///
    /// Operator overloading to perform output to QTextStream
    ///
    QTextStream& operator<<(QTextStream &ostream);
};

#endif // NETWORK_H