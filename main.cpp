#include <iostream>
#include <string>
#include <qcoreapplication.h>
#include <qdebug.h>
#include <cidparser.h>
#include <qfile.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    a.isSetuidAllowed();

    qInfo("............. MMC CID Parser By Mofadal .............");
    qInfo(".....................................................");

    if(argc < 2)
        qInfo("waiting for user to input a valid cid data (hex)");

    while (1) {

        QByteArray info(0xff, Qt::Uninitialized);
        std::cin.get((char*)info.data(), 0xff);

        qInfo(".....................................................");
        qInfo().noquote() << QString("Reading cid %0").arg(info.data());

        CIDParser cid(QByteArray::fromHex(info.data()).toStdString());
        mmcCARD::CIDInfo m_cid = {};
        cid.PraseCID(m_cid);

        qInfo(".....................................................");
        qInfo().noquote() << QString("CIDInfo::ManufacturerId: %0").arg(m_cid.ManufacturerId.c_str());
        qInfo().noquote() << QString("CIDInfo::Manufacturer: %0").arg(m_cid.Manufacturer.c_str());
        qInfo().noquote() << QString("CIDInfo::Card Type: %0").arg(m_cid.CardBGA.c_str());
        qInfo().noquote() << QString("CIDInfo::OEMApplicationId: %0").arg(m_cid.OEMApplicationId.c_str());
        qInfo().noquote() << QString("CIDInfo::ProductName: %0").arg(m_cid.ProductName.c_str());
        qInfo().noquote() << QString("CIDInfo::ProductRevision: %0").arg(m_cid.ProductRevision.c_str());
        qInfo().noquote() << QString("CIDInfo::ProductSerialNumber: %0").arg(m_cid.ProductSerialNumber.c_str());
        qInfo().noquote() << QString("CIDInfo::ManufacturingDate: %0").arg(m_cid.ManufacturingDate.c_str());
        qInfo(".....................................................");

        QFile results("Results.txt");
        if (results.open(QIODevice::WriteOnly | QIODevice::Append))
        {
            results.write(".....................................................\n");
            results.write(QString("Reading cid %0\n").arg(info.data()).toLatin1());
            results.write(".....................................................\n");
            results.write(QString("CIDInfo::ManufacturerId: %0\n").arg(m_cid.ManufacturerId.c_str()).toLatin1());
            results.write(QString("CIDInfo::Manufacturer: %0\n").arg(m_cid.Manufacturer.c_str()).toLatin1());
            results.write(QString("CIDInfo::Card Type: %0\n").arg(m_cid.CardBGA.c_str()).toLatin1());
            results.write(QString("CIDInfo::OEMApplicationId: %0\n").arg(m_cid.OEMApplicationId.c_str()).toLatin1());
            results.write(QString("CIDInfo::ProductName: %0\n").arg(m_cid.ProductName.c_str()).toLatin1());
            results.write(QString("CIDInfo::ProductRevision: %0\n").arg(m_cid.ProductRevision.c_str()).toLatin1());
            results.write(QString("CIDInfo::ProductSerialNumber: %0\n").arg(m_cid.ProductSerialNumber.c_str()).toLatin1());
            results.write(QString("CIDInfo::ManufacturingDate: %0\n").arg(m_cid.ManufacturingDate.c_str()).toLatin1());
            results.write(".....................................................\n");

        }

        info.clear();

        std::cin.ignore();

        qInfo("waiting for user to input a valid cid data (hex)");

        // break;
    }

    return a.exec();
}
