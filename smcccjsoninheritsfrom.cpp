#include "smcccjsoninheritsfrom.h"

#include "smcccjson.h"

SMCCCJsonInheritsFrom::SMCCCJsonInheritsFrom(){}

bool SMCCCJsonInheritsFrom::process(SMCCCJson *Json){
    QString inheritsFromFilePath = Json->VersionsDirPath + "/" + Json->_inheritsFrom + "/" + Json->_inheritsFrom + ".json";
    if (!Json->isFileExist(inheritsFromFilePath))return false;
    QFile inheritsFromFile(inheritsFromFilePath);
    inheritsFromFile.open(QIODevice::ReadOnly);
    QJsonObject inheritsFromObj = QJsonDocument::fromJson(inheritsFromFile.readAll()).object();
    inheritsFromFile.close();
    QJsonObject _assetIndex = inheritsFromObj.value("assetIndex").toObject();
    QString _assets = inheritsFromObj.value("assets").toString();
    QJsonObject _downloads = inheritsFromObj.value("downloads").toObject();
    QString _id = inheritsFromObj.value("id").toString();
    QJsonArray _libraries = inheritsFromObj.value("libraries").toArray();
    QString _mainClass = inheritsFromObj.value("mainClass").toString();
    QString _minecraftArguments = inheritsFromObj.value("minecraftArguments").toString();
    if(Json->_assetIndex.isEmpty())Json->_assetIndex = _assetIndex;
    if(Json->_assets.isEmpty())Json->_assets = _assets;
    if(Json->_downloads.isEmpty())Json->_downloads = _downloads;
    if(Json->_id.isEmpty())Json->_id = _id;
    if(Json->_mainClass.isEmpty())Json->_mainClass = _mainClass;
    if(Json->_minecraftArguments.isEmpty())Json->_minecraftArguments = _minecraftArguments;
    foreach (QJsonValue v, _libraries) {
        Json->_libraries.append(v);
    }
    return true;
}
