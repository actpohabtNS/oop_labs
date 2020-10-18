#ifndef IPV6_H
#define IPV6_H

#include "ipAddress.h"
#include "IpAddress_types.h"

#include <QTextStream>

constexpr std::size_t MAX_BLOCKS {8};

///
/// \brief The IPv6 class
///
/// Ip address version 6 represented as b1:b2:b3:b4:b5:b6:b7:b8, bi is 1-4 Hexadecimal (0...9A...F) digits.
///
class IPv6 : public IpAddress {
private:
    ///
    /// \brief _blocks
    ///
    /// Stores 8 blocks containing 1-4 Hexadecimal digits, representing ip address v6
    ///
    ushort _blocks[8];

    ///
    /// \brief _blockWithMask
    /// \param block - number of block to use mask to
    /// \param mask - mask to use to block
    /// \param min - whether masked bits will be set to 0 or to 1
    /// \return int - block with mask used
    ///
    /// Use a mask for an block specified
    ///
    int _blockWithMask(std::size_t block, int mask, bool min = true) const override;

public:
    ///
    /// \brief IPv6
    ///
    /// Default constructor
    ///
    IPv6();

    ///
    /// \brief IPv6
    /// \param b1 - block 1
    /// \param b2 - block 2
    /// \param b3 - block 3
    /// \param b4 - block 4
    /// \param b5 - block 5
    /// \param b6 - block 6
    /// \param b7 - block 7
    /// \param b8 - block 8
    ///
    /// Constructor with list of blocks
    ///
    IPv6(ushort b1, ushort b2 = 0, ushort b3 = 0, ushort b4 = 0, ushort b5 = 0, ushort b6 = 0, ushort b7 = 0, ushort b8 = 0);

    ///
    /// \brief IPv6
    /// \param list - initializer list
    ///
    /// Initializer list constructor
    ///
    IPv6(std::initializer_list<ushort> list);

    ///
    /// \brief IPv6
    /// \param data - stores IPv6 address
    ///
    /// Parse constructor, accepts string in (\d| |.)+ (RegExp) or "n1{.| }n2{.| }..." (ni - numbers, {.| } sets of whitespaces or\and dots) form.
    /// If parser encounters not digit, whitespace or dot, zero IPv6 returned.
    /// Then blocks are being attached numbers, if they are less-equal 256, otherwise parsion stops and the remaining blocks initialize with 0.
    ///
    IPv6(QString data);

    ~IPv6() = default;


    ///
    /// \brief QStr
    /// \param base - blocks output base
    /// \return QString - IPv6 translated into QString
    ///
    QString QStr(int base = 16) const override;

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
    /// \param other - other IPv6 address to compare
    /// \return bool - whethet this IPv6 address is less other IPv6
    ///
    bool operator< (const IPv6& other) const;

    ///
    /// \brief operator <=
    /// \param other - other IPv6 address to compare
    /// \return bool - whethet this IPv6 address is less-equal other IPv6
    ///
    bool operator<= (const IPv6& other) const;

    ///
    /// \brief operator >
    /// \param other - other IPv6 address to compare
    /// \return bool - whethet this IPv6 address is greater other IPv6
    ///
    bool operator> (const IPv6& other) const;

    ///
    /// \brief operator >=
    /// \param other - other IPv6 address to compare
    /// \return bool - whethet this IPv6 address is greater-equal other IPv6
    ///
    bool operator>= (const IPv6& other) const;

    ///
    /// \brief operator ==
    /// \param other - other IPv6 address to compare
    /// \return bool - whethet this IPv6 address is equal other IPv6
    ///
    bool operator== (const IPv6& other) const;
};

#endif // IPV6_H
