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
    bool includes(sh_ptr_ip ip) const;

    ///
    /// \brief maxMaskLength
    /// \param type - type of IpAddress
    /// \return uchar - max length of mask for this IpAddress type
    ///
    uchar maxMaskLength(IpAddress_type type) const;


    ///
    /// \brief setMask
    /// \param mask - new mask to be set
    ///
    /// Updates value of Network's mask
    ///
    void setMask(uchar mask);

    ///
    /// \brief mask
    /// \return uchar - mask of this network
    ///
    uchar mask() const;

    ///
    /// \brief ip
    /// \return std::shared_ptr to IpAddress
    ///
    sh_ptr_ip ip() const;

    ///
    /// \brief operator <<
    /// \param ostream - QTextStream
    /// \return ostream& - reference to QTextSteam
    ///
    /// Operator overloading to perform output to QTextStream
    ///
    QTextStream& operator<<(QTextStream &ostream);

    ///
    /// \brief operator QString
    ///
    /// Operator to build QString from IPv4
    ///
    virtual operator QString() const;

    friend bool operator==(const Network& n1, const Network& n2) {
        return n1._ip->data() == n2._ip->data() && n1._mask == n2._mask;
    }

    friend bool operator<=(const Network& n1, const Network& n2) {
        return n1.min() <= n2.min() && n1.max() <= n2.min();
    }

    friend bool operator<(const Network& n1, const Network& n2) {
        return n1.min() < n2.min() && n1.max() < n2.min();
    }

    friend bool operator>=(const Network& n1, const Network& n2) {
        return n1.min() >= n2.min() && n1.min() >= n2.max();
    }

    friend bool operator>(const Network& n1, const Network& n2) {
        return n1.min() > n2.min() && n1.min() > n2.max();
    }
};

namespace std {
template <>
class hash<Network> {
 public:
  size_t operator()(const Network &network) const
  {
    // computes the hash of an employee using a variant
    // of the Fowler-Noll-Vo hash function
    size_t result = 2166136261;

    for (int e : network.ip()->data()) {
      result = (result * 16777619) ^ e;
    }

    return result ^ (network.mask() << 1);
  }
};
}

#endif // NETWORK_H
