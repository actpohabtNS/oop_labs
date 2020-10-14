#include "ipv6.h"

#include <algorithm>

#include <QDebug>
#include <QRegExp>
#include <QStringList>



// -------------------------------------- CONSTRUCTOR, DESTRUCTOR --------------------------------------

IPv6::IPv6() {
    std::fill(this->_blocks, this->_blocks + MAX_BLOCKS, 0);
}

IPv6::IPv6(ushort b1, ushort b2, ushort b3, ushort b4, ushort b5, ushort b6, ushort b7, ushort b8)
    : _blocks {b1, b2, b3, b4, b5, b6, b7, b8} {}

IPv6::IPv6(std::initializer_list<ushort> list) {
    std::fill(this->_blocks, this->_blocks + MAX_BLOCKS, 0);

    std::size_t blcIdx = 0;

    for (auto blc : list) {
        if (blcIdx >= MAX_BLOCKS)
            return;

        this->_blocks[blcIdx] = blc;
        ++blcIdx;
    }
}

IPv6::IPv6(QString data) {
    std::fill(this->_blocks, this->_blocks + MAX_BLOCKS, 0);

   data.replace(':', ' ');
   data = data.simplified();       // remove repetitous whitespaces

   QRegExp rx("[^(\\d| |[a-fA-F)]");

   if (rx.indexIn(data) != -1)     // if encounters NOT a digit, NOT a whitespace or NOT a letter a-e - create zero IPv6
       return;

   QStringList blocks = data.split(' ');

   std::size_t blcIdx = 0;

   for (auto oct : blocks) {         // chech whether numbers are lower-equal than FFFF
       if (oct.length() > 4 || blcIdx >= MAX_BLOCKS)
           return;

       this->_blocks[blcIdx] = oct.toUShort(nullptr, 16);
       ++blcIdx;
   }
}



// -------------------------------------- OTHER --------------------------------------

QString IPv6::QStr(int base) const {
    QString qStr = "";

    for (std::size_t blcInd = 0; blcInd < MAX_BLOCKS; ++blcInd)
        qStr.append(QString("%1").arg(this->_blocks[blcInd], 0, base) + ':');

    qStr.chop(1);

    return qStr;
}

IA_t IPv6::type() const {
    return IA_t::IPv6;
}

int IPv6::base() const {
    return 16;
}

std::size_t IPv6::block_size() const {
    return 16;
}

std::vector<int> IPv6::data() const {
    std::vector<int> res {};

    for (auto block : this->_blocks)
        res.push_back(block);

    return res;
}



// -------------------------------------- OVERLOADED OPERATORS --------------------------------------

QTextStream &IPv6::operator<<(QTextStream &ostream) {
    return ostream << this->QStr();
}

bool IPv6::operator<(const IPv6 &other) const {
    for (std::size_t blcIdx = 0; blcIdx < MAX_BLOCKS; ++blcIdx)
        if (this->_blocks[blcIdx] != other._blocks[blcIdx])
            return this->_blocks[blcIdx] < other._blocks[blcIdx];

    return false;
}

bool IPv6::operator<=(const IPv6 &other) const {
    return (*this < other || *this == other);
}

bool IPv6::operator>(const IPv6 &other) const {
    for (std::size_t blcIdx = 0; blcIdx < MAX_BLOCKS; ++blcIdx)
        if (this->_blocks[blcIdx] != other._blocks[blcIdx])
            return this->_blocks[blcIdx] > other._blocks[blcIdx];

    return false;
}

bool IPv6::operator>=(const IPv6 &other) const {
    return (*this > other || *this == other);
}

bool IPv6::operator==(const IPv6 &other) const {
    for (std::size_t blcIdx = 0; blcIdx < MAX_BLOCKS; ++blcIdx)
        if (this->_blocks[blcIdx] != other._blocks[blcIdx])
            return false;

    return true;
}
