#ifndef NET_H
#define NET_H

#include "httprequest.h"

class Net
{
public:
    Net();

    void setProxy(const QString &host, const QString &port, const QString &username, const QString &password, int type = 0);
    int httpGet(const QString &url, QByteArray &retdata, int timeOut = 12000);
    int httpGet(const QString &url, QByteArray &retdata, const QMap<QNetworkRequest::KnownHeaders,QString> &headerlist, int timeOut = 12000);
    int httpPost(const QString &url, QByteArray &retdata, const QByteArray &postdata, int timeOut = 12000);

};

#endif // NET_H
