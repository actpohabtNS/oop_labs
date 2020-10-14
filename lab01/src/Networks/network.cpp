#include "network.h"
#include "ipv4.h"
#include "ipv6.h"

#include <QDebug>

#include <bitset>
#include <math.h>

// -------------------------------------- INTERNAL METHODS --------------------------------------

sh_ptr_ip Network::_minOrMax(bool min) const {
    std::vector<int> data = this->_ip->data();
    std::size_t block_size = this->_ip->block_size();

    int int_block {};

    if (this->_mask % block_size != 0) {
        if (this->_ip->type() == IA_t::IPv4) {
            std::bitset<8> block (data[this->_mask / block_size]);

            for (std::size_t b = 0; b < block_size - this->_mask % block_size; ++b) {
                if (min)
                    block.reset(b);
                else
                    block.set(b);
            }

            int_block = static_cast<int>(block.to_ulong());


        } else if (this->_ip->type() == IA_t::IPv6) {

            std::bitset<16> block (data[this->_mask / block_size]);

            for (std::size_t b = 0; b < block_size - this->_mask % block_size; ++b) {
                if (min)
                    block.reset(b);
                else
                    block.set(b);
            }

            int_block = static_cast<int>(block.to_ulong());
        }

        data[this->_mask / block_size] = int_block;
    } else {
        std::size_t blcIdx = this->_mask / block_size;

        if (blcIdx < data.size()) {
            if (min)
                data[blcIdx] = 0;
            else
                data[blcIdx] = std::pow(2, block_size) - 1;
        }
    }

    int base {};

    if (this->_ip->type() == IA_t::IPv4) {
        base = 10;
    } else if (this->_ip->type() == IA_t::IPv6) {
        base = 16;
    }

    for (std::size_t blcIdx = this->_mask / block_size + 1; blcIdx < data.size(); blcIdx++) {
        if (min)
            data[blcIdx] = 0;
        else
            data[blcIdx] = std::pow(2, block_size) - 1;
    }

    QString str = "";

    for (int block : data)
        str += QString::number(block, base) + " ";

    sh_ptr_ip res = nullptr;

    if (this->_ip->type() == IA_t::IPv4) {
        res.reset(new IPv4(str));
    } else if (this->_ip->type() == IA_t::IPv6) {
        res.reset(new IPv6(str));
    }

    return res;
}



// -------------------------------------- CONSTRUCTOR, DESTRUCTOR --------------------------------------

Network::Network() {
    this->_ip = std::shared_ptr<IpAddress>(new IPv4());
    this->_mask = this->maxMaskLength(IA_t::IPv4);
}

// May be solved in future, though using raw pointers in not recommended
//
//Network::Network( IpAddress *ip, uchar mask) {

//    sh_ptr_ip ptr = std::dynamic_pointer_cast<IpAddress>(ip->shared_from_this()); //will throw an exception: bad_weak_ptr cause Network does not have a shared_ptr pointing to it at start
//    this->_ip = ptr;
//    this->_mask = mask % this->maxMaskLength(ip->type());
//}

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

sh_ptr_ip Network::min() const {
    return this->_minOrMax(true);
}

sh_ptr_ip Network::max() const {
    return this->_minOrMax(false);
}

bool Network::includes(const IpAddress *ip) const {

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