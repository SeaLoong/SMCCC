#include "json_assets.h"

QString Json_Assets::AssetDirPath;
QString Json_Assets::AssetIndexFilePath;

QJsonObject Json_Assets::assetIndexFileObj;
QString Json_Assets::assetIndex_id;
QString Json_Assets::assetIndex_sha1;
int Json_Assets::assetIndex_size;
QString Json_Assets::assetIndex_url;

bool Json_Assets::processIndexFile(){//false:需要下载
    assetIndex_id = Json::_assetIndex.value("id").toString("");
    assetIndex_sha1 = Json::_assetIndex.value("sha1").toString("");
    assetIndex_size = Json::_assetIndex.value("size").toInt(0);
    assetIndex_url = Json::_assetIndex.value("url").toString("");

    AssetDirPath = Json::_GameDirPath + "\\assets";
    AssetIndexFilePath = AssetDirPath + "\\indexes\\" + assetIndex_id + ".json";
    //检查assets\indexes\[version].json文件
    if(!Launcher::isFileExist(AssetIndexFilePath) || (Json::_FileCheck && (!Launcher::checkFileSize(AssetIndexFilePath,assetIndex_size) || !Launcher::checkFileSHA1(AssetIndexFilePath,assetIndex_sha1)))){
        DownloadInfo info(AssetIndexFilePath,assetIndex_url,assetIndex_sha1,assetIndex_size);
        Json::_DownloadInfoList.append(info);
        return false;
    }
    QFile indexFile(AssetIndexFilePath);
    indexFile.open(QIODevice::ReadOnly);
    assetIndexFileObj = QJsonDocument::fromJson(indexFile.readAll()).object();
    indexFile.close();
    return true;
}

bool Json_Assets::processFile(){//false:需要下载
    //检查assets\目录下的文件
    bool ret = true;

    //判断是否虚拟化文件
    bool _virtual = assetIndexFileObj.value("virtual").toBool();
    QString _pathRoot;
    if(_virtual)_pathRoot = AssetDirPath + "\\virtual\\" + assetIndex_id;
    else _pathRoot = AssetDirPath + "\\objects";

    //资源文件信息
    QJsonObject _objects = assetIndexFileObj.value("objects").toObject();
    for(QJsonObject::ConstIterator it = _objects.constBegin();it != _objects.constEnd();++it){
        QString _fileName,_filePath;
        QString _hash = it.value().toObject().value("hash").toString();//sha1
        int _size = it.value().toObject().value("size").toInt(0);
        if(_virtual){
            _fileName = it.key();
            _fileName.replace("/","\\");
        }else{
            _fileName = _hash.left(2) + "\\" + _hash;
        }
        _filePath = _pathRoot + "\\" + _fileName;
        QString _url = "http://resources.download.minecraft.net/" + _hash.left(2) + "/" + _hash;
        if(!Launcher::isFileExist(_filePath) || (Json::_FileCheck && (!Launcher::checkFileSize(_filePath,_size) || !Launcher::checkFileSHA1(_filePath,_hash)))){
            DownloadInfo info(_filePath,_url,_hash,_size);
            Json::_DownloadInfoList.append(info);
            ret = false;
        }
    }
    return ret;
}
