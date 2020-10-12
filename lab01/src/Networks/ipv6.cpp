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



// -------------------------------------- OTHER --------------------------------------

QString IPv6::QStr(int base) const {
    QString qStr = "";

    for (std::size_t blcInd = 0; blcInd < MAX_BLOCKS; ++blcInd)
        qStr.append(QString("%1").arg(this->_blocks[blcInd], 0, base) + ':');

    qStr.chop(1);

    return qStr;
}

IA_t IPv6::type() {
    return IA_t::IPv6;
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
