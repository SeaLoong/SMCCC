#ifndef SMCCCJSONASSETS_H
#define SMCCCJSONASSETS_H

#include <QJsonObject>

class SMCCCJson;
class SMCCCJsonAssets
{
public:
    SMCCCJsonAssets();

    bool processIndex(SMCCCJson *Json);
    bool process(SMCCCJson *Json);

private:
    QString assetIndex_id;
    QString assetIndex_sha1;
    int assetIndex_size;
    QString assetIndex_url;
    QJsonObject assetIndexFileObj;
};

#endif // SMCCCJSONASSETS_H
