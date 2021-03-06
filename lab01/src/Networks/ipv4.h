#ifndef IPV4_H
#define IPV4_H

#include "ipAddress.h"
#include "IpAddress_types.h"

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

    ///
    /// \brief _blockWithMask
    /// \param octet - number of octet to use mask to
    /// \param mask - mask to use to octet
    /// \param min - whether masked bits will be set to 0 or to 1
    /// \return int - octet with mask used
    ///
    /// Use a mask for an octet specified
    ///
    int _blockWithMask(std::size_t octet, int mask, bool min = true) const override;

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
    /// Parse constructor, accepts string in (\d| |.)+ (RegExp) or "n1{.| }n2{.| }..." (ni - numbers, {.| } sets of whitespaces or\and dots) form.
    /// If parser encounters not digit, whitespace or dot, zero IPv4 returned.
    /// Then octets are being attached numbers, if they are less-equal 256, otherwise parsion stops and the remaining octets initialize with 0.
    ///
    IPv4(QString data);

    ~IPv4() = default;


    ///
    /// \brief QStr
    /// \param base - octets output base
    /// \return QString - IPv4 translated into QString
    ///
    QString QStr(int base = 10) const override;

    ///
    /// \brief type
    /// \return IpAddress_type
    ///
    IA_t type() const override;

    ///
    /// \brief base
    /// \return int - Number format of data blocks
    ///
    int base() const override;

    ///
    /// \brief block_size
    /// \return std::size_t - size of data block in bits
    ///
    std::size_t block_size() const override;

    ///
    /// \brief data
    /// \return std::vector<int> - vector of block values
    ///
    std::vector<int> data() const override;


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
    virtual operator QString() override;

    ///
    /// \brief operator <
    /// \param other - other IPv4 address to compare
    /// \return bool - whethet this IPv4 address is less other IPv4
    ///
    bool operator< (const IPv4& other) const;

    ///
    /// \brief operator <=
    /// \param other - other IPv4 address to compare
    /// \return bool - whethet this IPv4 address is less-equal other IPv4
    ///
    bool operator<= (const IPv4& other) const;

    ///
    /// \brief operator >
    /// \param other - other IPv4 address to compare
    /// \return bool - whethet this IPv4 address is greater other IPv4
    ///
    bool operator> (const IPv4& other) const;

    ///
    /// \brief operator >=
    /// \param other - other IPv4 address to compare
    /// \return bool - whethet this IPv4 address is greater-equal other IPv4
    ///
    bool operator>= (const IPv4& other) const;

    ///
    /// \brief operator ==
    /// \param other - other IPv4 address to compare
    /// \return bool - whethet this IPv4 address is equal other IPv4
    ///
    bool operator== (const IPv4& other) const;
};

#endif // IPV4_H
