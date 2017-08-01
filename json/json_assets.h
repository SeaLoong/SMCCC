#ifndef JSON_ASSETS_H
#define JSON_ASSETS_H

#include "core/json/json.h"

class Json_Assets
{
public:

    static bool processIndexFile();
    static bool processFile();

private:
    Json_Assets();

    static QString AssetDirPath;
    static QString AssetIndexFilePath;

    static QJsonObject assetIndexFileObj;
    static QString assetIndex_id;
    static QString assetIndex_sha1;
    static int assetIndex_size;
    static QString assetIndex_url;

};

#endif // JSON_ASSETS_H
