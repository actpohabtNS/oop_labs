#include "ipv6.h"

#include <algorithm>

#include <QDebug>
#include <QRegExp>
#include <QStringList>



// -------------------------------------- CONSTRUCTOR, DESTRUCTOR --------------------------------------

IPv6::IPv6() {
    std::fill(this->_blocks, this->_blocks + MAX_BLOCKS, 0);
}

QString IPv6::QStr() const {
    QString qStr = "";

    for (std::size_t blcInd = 0; blcInd < MAX_BLOCKS; ++blcInd)
        qStr.append(QString::number(this->_blocks[blcInd]) + ':');

    qStr.chop(1);

    return qStr;
}

IA_t IPv6::type() {
    return IA_t::IPv6;
}

QTextStream &IPv6::operator<<(QTextStream &ostream) {
    return ostream << this->QStr();
}
