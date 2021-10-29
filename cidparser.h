#ifndef CIDPARSER_H
#define CIDPARSER_H

#include <structures.h>

class CIDParser
{
public:
    CIDParser(std::string raw_cid);

    bool PraseCID(mmcCARD::CIDInfo &cid_info);

private:
    mmcCARD::emmc_card_info_cid_t m_cid = {};
};

#endif // CIDPARSER_H
