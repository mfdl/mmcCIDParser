#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>
#include <stdio.h>
#include <string.h>

using namespace std;

namespace mmcCARD {

#define EMMC_CARD_INFO_CSD_LENGTH 16
#define EMMC_CARD_INFO_EXT_CSD_LENGTH 512

typedef struct emmc_card_info_cid_t
{
public:
    uint8_t mid{0x00}; /* Manufacturer ID */
    uint8_t cbx{0x00}; /* Reserved(6)+Card/BGA(2) */ //- Only lower 2 bit valid
    uint8_t oid{0x00}; /* OEM/Application ID */
    uint8_t pnm0{0x00}; /* Product name [0] */
    uint8_t pnm1{0x00}; /* Product name [1] */
    uint8_t pnm2{0x00}; /* Product name [2] */
    uint8_t pnm3{0x00}; /* Product name [3] */
    uint8_t pnm4{0x00}; /* Product name [4] */
    uint8_t pnm5{0x00}; /* Product name [5] */
    uint8_t pdrv{0x00}; /* Product revision */
    uint8_t psn0{0x00}; /* Serial Number [0] */
    uint8_t psn1{0x00}; /* Serial Number [1] */
    uint8_t psn2{0x00}; /* Serial Number [2] */
    uint8_t psn3{0x00}; /* Serial Number [3] */
    uint8_t mdt{0x00}; /* Manufacturer date */
    uint8_t crc7{0x00}; /* CRC7 + stuff bit*/  //--Only top 7 bit
}mmc_cid_t;

typedef struct _card_info_emmc_t
{
    uint32_t ocr; // Info read from OCR (operations Conditions Register) register. provided here to assist OEM /technician
    emmc_card_info_cid_t cid;
    uint8_t csd[EMMC_CARD_INFO_CSD_LENGTH]; // Card Specific Data - info about card operation conditions
    uint8_t ext_csd[EMMC_CARD_INFO_EXT_CSD_LENGTH];  	// Extended Card Specific Data. Contains information about the card capabilities and selected modes.
} card_info_emmc_t;

typedef struct CIDInfo
{
    std::string ManufacturerId{0x00};
    std::string Manufacturer{0x00};
    std::string CardBGA{0x00};
    std::string OEMApplicationId{0x00};
    std::string ProductName{0x00};
    std::string ProductRevision{0x00};
    std::string ProductSerialNumber{0x00};
    std::string ManufacturingDate{0x00};
}CIDInfo;
}
#endif // STRUCTURES_H
