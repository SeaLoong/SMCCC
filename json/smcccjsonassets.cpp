#include "smcccjsonassets.h"

bool SMCCCJsonAssets::processIndex(SMCCCJson *Json){//false:需要下载
    assetIndex_id = Json->_assetIndex.value("id").toString();
    assetIndex_sha1 = Json->_assetIndex.value("sha1").toString();
    assetIndex_size = Json->_assetIndex.value("size").toInt();
    assetIndex_url = Json->_assetIndex.value("url").toString();

    QString AssetIndexFilePath = Json->AssetsDirPath + "/indexes/" + assetIndex_id + ".json";
    //检查assets\indexes\[version].json文件
    if(!Json->isFileExist(AssetIndexFilePath) || (Json->FileCheck && (!Json->checkFileSize(AssetIndexFilePath,assetIndex_size) || !Json->checkFileSHA1(AssetIndexFilePath,assetIndex_sha1)))){
        SMCCC::DownloadInfo info(AssetIndexFilePath,assetIndex_url,assetIndex_sha1,assetIndex_size);
        Json->DownloadInfoList.append(info);
        return false;
    }
    QFile indexFile(AssetIndexFilePath);
    indexFile.open(QIODevice::ReadOnly);
    assetIndexFileObj = QJsonDocument::fromJson(indexFile.readAll()).object();
    indexFile.close();
    return true;
}

bool SMCCCJsonAssets::process(SMCCCJson *Json){//false:需要下载
    //检查assets\目录下的文件
    bool ret = true;

    //判断是否虚拟化文件
    bool _virtual = assetIndexFileObj.value("virtual").toBool();
    QString _pathRoot;
    if(_virtual)_pathRoot = Json->AssetsDirPath + "/virtual/" + assetIndex_id;
    else _pathRoot = Json->AssetsDirPath + "/objects";

    //资源文件信息
    QJsonObject _objects = assetIndexFileObj.value("objects").toObject();
    for(QJsonObject::ConstIterator it = _objects.constBegin();it != _objects.constEnd();++it){
        QString _fileName,_filePath;
        QString _hash = it.value().toObject().value("hash").toString();//sha1
        int _size = it.value().toObject().value("size").toInt();
        if(_virtual){
            _fileName = it.key();
            _fileName.replace("/","/");
        }else{
            _fileName = _hash.left(2) + "/" + _hash;
        }
        _filePath = _pathRoot + "/" + _fileName;
        QString _url = "http://resources.download.minecraft.net/" + _hash.left(2) + "/" + _hash;
        if(!Json->isFileExist(_filePath) || (Json->FileCheck && (!Json->checkFileSize(_filePath,_size) || !Json->checkFileSHA1(_filePath,_hash)))){
            SMCCC::DownloadInfo info(_filePath,_url,_hash,_size);
            Json->DownloadInfoList.append(info);
            ret = false;
        }
    }
    return ret;
}
