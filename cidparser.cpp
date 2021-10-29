#include "cidparser.h"
#include "qstring.h"

std::string get_card_mfr_id(uint8_t mid)
{
    switch (mid)
    {
        case 0x02:
            return "Sandisk_New";
        case 0x11:
           return"Toshiba";
        case 0x13:
           return "Micron";
        case 0x15:
           return "Samsung";
        case 0x45:
           return "Sandisk";
        case 0x70:
           return "Kingston";
        case 0x74:
           return "Transcend";
        case 0x88:
           return "Foresee";
        case 0x90:
           return "SkHynix";
        case 0x8f:
           return "UNIC";
        case 0xf4:
           return "Biwin";
        case 0xfe:
           return "Micron";
        default:
           return "Unknown";
    }
}

std::string get_card_type(uint8_t type)
{
    switch (type)
    {
        case 0x00:
           return "RemovableDevice";
        case 0x01:
           return "BGA (Discrete embedded)";
        case 0x02:
           return "POP";
        case 0x03:
           return "RSVD";
        default:
           return"Unknown";
    }
}

CIDParser::CIDParser(string raw_cid)
{
    memset(&this->m_cid, 0x00, sizeof(m_cid));
    memcpy(&this->m_cid, raw_cid.c_str(), sizeof(this->m_cid));
}

bool CIDParser::PraseCID(mmcCARD::CIDInfo &cid_info)
{
    cid_info = {};
    struct {
        char pnm[6]{0x00};
    } _pnm = {};
    memcpy(&_pnm.pnm[0], &this->m_cid.pnm0, sizeof(_pnm.pnm[0]));
    memcpy(&_pnm.pnm[1], &this->m_cid.pnm1, sizeof(_pnm.pnm[1]));
    memcpy(&_pnm.pnm[2], &this->m_cid.pnm2, sizeof(_pnm.pnm[2]));
    memcpy(&_pnm.pnm[3], &this->m_cid.pnm3, sizeof(_pnm.pnm[3]));
    memcpy(&_pnm.pnm[4], &this->m_cid.pnm4, sizeof(_pnm.pnm[4]));
    memcpy(&_pnm.pnm[5], &this->m_cid.pnm5, sizeof(_pnm.pnm[5]));
    QByteArray pnm((char*)&_pnm, sizeof(_pnm));

    struct {
        char psn[4]{0x00};
    } _psn = {};
    memcpy(&_psn.psn[0], &this->m_cid.psn0, sizeof(_psn.psn[0]));
    memcpy(&_psn.psn[1], &this->m_cid.psn1, sizeof(_psn.psn[1]));
    memcpy(&_psn.psn[2], &this->m_cid.psn2, sizeof(_psn.psn[2]));
    memcpy(&_psn.psn[3], &this->m_cid.psn3, sizeof(_psn.psn[3]));
    QByteArray psn((char*)&_psn, sizeof(_psn));

    QString prv_min(QString().sprintf("%d", (uint8_t)(this->m_cid.pdrv >> 4)));
    QString prv_maj(QString().sprintf("%d", (uint8_t)(this->m_cid.pdrv & 0xf)));
    QString mdt_month(QString().sprintf("%d", (uint8_t)(this->m_cid.mdt >> 4)));
    QString mdt_year(QString().sprintf("%d", (uint16_t)(this->m_cid.mdt & 0xf) + 2013)); //todo

    cid_info.ManufacturerId = QString("0x%0").arg(QString().setNum(this->m_cid.mid, 0x10)).toStdString();
    cid_info.Manufacturer = get_card_mfr_id(this->m_cid.mid);
    cid_info.CardBGA = get_card_type(this->m_cid.cbx);
    cid_info.OEMApplicationId = QString("0x%0").arg(QString().setNum(this->m_cid.oid, 0x10)).toStdString();
    cid_info.ProductName = QString("%0:%1").arg(pnm.trimmed(), pnm.toHex().data()).toStdString();
    cid_info.ProductRevision = QString(prv_min + "." + prv_maj).toStdString();
    cid_info.ProductSerialNumber = QString("0x%0").arg(psn.toHex().data()).toStdString();
    cid_info.ManufacturingDate = QString(mdt_month + "/" + mdt_year).toStdString();

    return 1;
}
