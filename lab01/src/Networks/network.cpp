#include "network.h"
#include "ipv4.h"

#include <QDebug>

// -------------------------------------- CONSTRUCTOR, DESTRUCTOR --------------------------------------

Network::Network() {
    this->_ip = std::shared_ptr<IpAddress>(new IPv4());
    this->_mask = this->maxMaskLength(IA_t::IPv4);
}

Network::Network(const IpAddress *ip, uchar mask) {
    sh_ptr_ip ptr;
    ptr.reset(const_cast<IpAddress*>(ip));      //const_cast here is a necessity to left const pointer as an argument.
    this->_ip = ptr;
    this->_mask = mask % this->maxMaskLength(ip->type());
}

Network::Network(sh_ptr_ip ip, uchar mask) {
    this->_ip = ip;
    this->_mask = mask % this->maxMaskLength(ip->type());
}

void Network::setMask(uchar mask) {
    this->_mask = mask % this->maxMaskLength(this->_ip->type());
}



// -------------------------------------- OTHER --------------------------------------

QString Network::QStr() const {
    return this->_ip->QStr() + '/' + QString::number(this->_mask);
}

uchar Network::maxMaskLength(IpAddress_type type) const {
    switch (type) {
        case IA_t::IPv4:
            return 32;

        case IA_t::IPv6:
            return 128;
    }

    return -1;
}

QTextStream &Network::operator<<(QTextStream &ostream){
    return ostream << this->QStr();
}
