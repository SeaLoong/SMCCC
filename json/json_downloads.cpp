#include "json_downloads.h"

bool Json_Downloads::process(){//false:需要下载
    QJsonObject downloads_clientObj = Json::_downloads.value("client").toObject();
    int downloads_client_size = downloads_clientObj.value("size").toInt(0);
    QString downloads_client_sha1 = downloads_clientObj.value("sha1").toString("");
    QString downloads_client_url = downloads_clientObj.value("url").toString("");
    //检查客户端jar文件
    if(!Launcher::isFileExist(Json::_JarFilePath)){
        DownloadInfo info(Json::_JarFilePath,downloads_client_url,downloads_client_sha1,downloads_client_size);
        Json::_DownloadInfoList.append(info);
        return false;
    }
    return true;
}
