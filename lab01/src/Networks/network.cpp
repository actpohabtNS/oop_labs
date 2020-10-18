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

    // edit block separated by position where 1s change to 0s in mask
    int mask = static_cast<int>(std::pow(2, this->_mask % block_size) - 1) << (block_size - this->_mask % block_size);
    int int_block = this->_ip->_blockWithMask(this->_mask / block_size, mask, min);
    data[this->_mask / block_size] = int_block;

    // min or max leftout blocks
    for (std::size_t blcIdx = this->_mask / block_size + 1; blcIdx < data.size(); blcIdx++) {
        if (min)
            data[blcIdx] = 0;
        else
            data[blcIdx] = std::pow(2, block_size) - 1;
    }

    QString str = "";
    for (int block : data)
        str += QString::number(block, this->_ip->base()) + " ";

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

bool Network::includes(sh_ptr_ip ip) const {

    if (this->_ip->type() != ip->type())
        return false;

    std::vector<int> this_data = this->_ip->data();
    std::vector<int> other_data = ip->data();

    std::size_t block_size = this->_ip->block_size();

    std::size_t sepBlockIdx = this->_mask / block_size;

    for (std::size_t blcIdx = 0; blcIdx < sepBlockIdx; blcIdx++)
        if (this_data[blcIdx] != other_data[blcIdx])
            return false;

    int mask = static_cast<int>(std::pow(2, this->_mask % block_size) - 1) << (block_size - this->_mask % block_size);
    int ch_block_min = this->_ip->_blockWithMask(sepBlockIdx, mask, true);
    int ch_block_max = this->_ip->_blockWithMask(sepBlockIdx, mask, false);

    return (ch_block_min <= other_data[sepBlockIdx] && other_data[sepBlockIdx] <= ch_block_max);
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



void Network::setMask(uchar mask) {
    this->_mask = mask % this->maxMaskLength(this->_ip->type());
}

uchar Network::mask() const {
    return this->_mask;
}

sh_ptr_ip Network::ip() const {
    return this->_ip;
}

QTextStream &Network::operator<<(QTextStream &ostream) {
    return ostream << this->QStr();
}

Network::operator QString() const {
    return this->QStr();
}
