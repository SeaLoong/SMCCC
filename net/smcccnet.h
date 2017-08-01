#ifndef SMCCCNET_H
#define SMCCCNET_H

#include "smccchttprequest.h"

class SMCCCNet
{
public:
    SMCCCNet();
    void setProxy(const QString &host, const QString &port, const QString &username, const QString &password, int type = 0);
    //设置代理，type代理方式：1:http，2:socket5，3:无代理，其它:默认IE代理
    int httpGet(const QString &url, QByteArray &retdata, int timeOut = 12000);
    int httpGet(const QString &url, QByteArray &retdata, const QMap<QNetworkRequest::KnownHeaders,QString> &headerlist, int timeOut = 12000);
    int httpPost(const QString &url, QByteArray &retdata, const QByteArray &postdata, int timeOut = 12000);
    int httpGet(const QString &url, QByteArray &retdata, const QByteArray &postdata, const QMap<QNetworkRequest::KnownHeaders,QString> &headerlist, int timeOut = 12000);
};

#endif // SMCCCNET_H
