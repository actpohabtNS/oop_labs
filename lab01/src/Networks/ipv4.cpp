#include "ipv4.h"

#include <algorithm>
#include <bitset>

#include <QDebug>
#include <QRegExp>



// --------------------------------------  INTERNAL METHODS --------------------------------------

int IPv4::_blockWithMask(std::size_t octet, int mask, bool min) const {
    if (octet > MAX_OCTETS - 1)
        return 0;

    std::bitset<8> res_b(this->_octets[octet]);
    std::bitset<8> mask_b(mask);

    res_b &= mask_b;

    if (!min)
        res_b = ((~res_b) ^ mask_b);

    return static_cast<int>(res_b.to_ulong());
}

// -------------------------------------- CONSTRUCTOR, DESTRUCTOR --------------------------------------

IPv4::IPv4() {
    std::fill(this->_octets, this->_octets + MAX_OCTETS, 0);
}

IPv4::IPv4(uchar o1, uchar o2, uchar o3, uchar o4) : _octets {o1, o2, o3, o4} {}

IPv4::IPv4(std::initializer_list<uchar> list) {
    std::fill(this->_octets, this->_octets + MAX_OCTETS, 0);

    std::size_t octIdx = 0;

    for (auto oct : list) {
        if (octIdx >= MAX_OCTETS)
            return;

        this->_octets[octIdx] = oct;
        ++octIdx;
    }
}

IPv4::IPv4(QString data) {
     std::fill(this->_octets, this->_octets + MAX_OCTETS, 0);

    data.replace('.', ' ');
    data = data.simplified();       // remove repetitous whitespaces

    QRegExp rx("[^(\\d| )]");
    if (rx.indexIn(data) != -1)     // if encounters NOT a digit or a whitespace - create zero IPv4
        return;

    QStringList octs = data.split(' ');

    std::size_t octIdx = 0;

    for (auto oct : octs) {         // chech whether numbers are lower-equal than 256
        if (oct.length() > 3 ||
           (oct.length() == 3 && oct.compare("256") > 0) ||
            octIdx >= MAX_OCTETS)
            return;

        this->_octets[octIdx] = static_cast<uchar>(oct.toUShort());
        ++octIdx;
    }
}




// -------------------------------------- OTHER --------------------------------------

QString IPv4::QStr(int base) const {
    QString qStr = "";

    for (std::size_t octInd = 0; octInd < MAX_OCTETS; ++octInd)
        qStr.append(QString("%1").arg(this->_octets[octInd], 0, base) + '.');

    qStr.chop(1);

    return qStr;
}

IA_t IPv4::type() const {
    return IA_t::IPv4;
}

int IPv4::base() const {
    return 10;
}

std::size_t IPv4::block_size() const {
    return 8;
}

std::vector<int> IPv4::data() const {
    std::vector<int> res {};

    for (auto octet : this->_octets)
        res.push_back(octet);

    return res;
}



// -------------------------------------- OVERLOADED OPERATORS --------------------------------------

QTextStream& IPv4::operator<<(QTextStream &ostream) {
    return ostream << this->QStr();
}

IPv4::operator QString() {
    return this->QStr();
}

bool IPv4::operator<(const IPv4 &other) const {
    for (std::size_t octIdx = 0; octIdx < MAX_OCTETS; ++octIdx)
        if (this->_octets[octIdx] != other._octets[octIdx])
            return this->_octets[octIdx] < other._octets[octIdx];

    return false;
}

bool IPv4::operator<=(const IPv4 &other) const {
    return (*this < other || *this == other);
}

bool IPv4::operator>(const IPv4 &other) const {
    for (std::size_t octIdx = 0; octIdx < MAX_OCTETS; ++octIdx)
        if (this->_octets[octIdx] != other._octets[octIdx])
            return this->_octets[octIdx] > other._octets[octIdx];

    return false;
}

bool IPv4::operator>=(const IPv4 &other) const {
    return (*this > other || *this == other);
}

bool IPv4::operator==(const IPv4 &other) const {
    for (std::size_t octIdx = 0; octIdx < MAX_OCTETS; ++octIdx)
        if (this->_octets[octIdx] != other._octets[octIdx])
            return false;

    return true;
}
