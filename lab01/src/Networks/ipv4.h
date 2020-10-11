#ifndef IPV4_H
#define IPV4_H

#include "ipAddress.h"

#include <QString>
#include <QTextStream>

#include <initializer_list>

constexpr std::size_t MAX_OCTETS {4};

///
/// \brief The IPv4 class
///
/// Ip address version 4 represented as a1.a2.a3.a4, 0 <= ai <= 255
///
class IPv4 : public IpAddress
{
private:
    ///
    /// \brief _octets
    ///
    /// Stores 4 digits 0 to 255, representing ip address v4
    ///
    uchar _octets[4];

public:
    ///
    /// \brief IPv4
    ///
    /// Default constructor
    ///
    IPv4();

    ///
    /// \brief IPv4
    /// \param o1 - octet 1
    /// \param o2 - octet 2
    /// \param o3 - octet 3
    /// \param o4 - octet 4
    ///
    /// Constructor with list of octets
    ///
    IPv4(uchar o1, uchar o2 = 0, uchar o3 = 0, uchar o4 = 0);

    ///
    /// \brief IPv4
    /// \param list - initializer list
    ///
    /// Initializer list constructor
    ///
    IPv4(std::initializer_list<uchar> list);

    ///
    /// \brief IPv4
    /// \param data - stores IPv4 address
    ///
    /// Parse constructor
    ///
    IPv4(const QString& data);

    ~IPv4() = default;


    ///
    /// \brief QStr
    /// \return QString - IPv4 translated into QString
    ///
    QString QStr() const override;

    ///
    /// \brief operator <<
    /// \param ostream - QTextStream
    /// \return ostream& - reference to QTextSteam
    ///
    /// Operator overloading to perform output to QTextStream
    ///
    QTextStream& operator<<(QTextStream &ostream);
};

#endif // IPV4_H
