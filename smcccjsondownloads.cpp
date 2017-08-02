#include "smcccjsondownloads.h"

#include "smcccjson.h"

SMCCCJsonDownloads::SMCCCJsonDownloads(){}

bool SMCCCJsonDownloads::process(SMCCCJson *Json){//false:需要下载
    QJsonObject downloads_clientObj = Json->_downloads.value("client").toObject();
    int downloads_client_size = downloads_clientObj.value("size").toInt();
    QString downloads_client_sha1 = downloads_clientObj.value("sha1").toString();
    QString downloads_client_url = downloads_clientObj.value("url").toString();
    //检查客户端jar文件
    if(!Json->isFileExist(Json->JarFilePath) || (Json->FileCheck && (!Json->checkFileSize(Json->JarFilePath,downloads_client_size) || !Json->checkFileSHA1(Json->JarFilePath,downloads_client_sha1)))){
        SMCCCDownloadInfo info(Json->JarFilePath,downloads_client_url,downloads_client_sha1,downloads_client_size);
        Json->DownloadInfoList.append(info);
        return false;
    }
    return true;
}
