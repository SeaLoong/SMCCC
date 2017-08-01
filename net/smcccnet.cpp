#include "smcccnet.h"

void SMCCCNet::setProxy(const QString &host, const QString &port, const QString &username, const QString &password, int type){
    if(host.isEmpty() || port <= 0)return;
    QNetworkProxy proxy;
    switch (type) {
    case 1:
        proxy.setType(QNetworkProxy::HttpProxy);
        break;
    case 2:
        proxy.setType(QNetworkProxy::Socks5Proxy);
        break;
    case 3:
        proxy.setType(QNetworkProxy::NoProxy);
        break;
    default:
        proxy.setType(QNetworkProxy::DefaultProxy);
        break;
    }
    proxy.setHostName(host);
    proxy.setPort(port.toInt());
    proxy.setUser(username);
    proxy.setPassword(password);
    QNetworkProxy::setApplicationProxy(proxy);
}

int SMCCCNet::httpGet(const QString &url, QByteArray &retdata, int timeOut){
    SMCCCHttpRequest *_http = new SMCCCHttpRequest;
    _http->setTimeOut(timeOut);
    if(!_http->request(url))return -1;
    int code = _http->getHttpStatusCode();
    retdata = _http->getReturnData();
    delete _http;
    return code;
}

int SMCCCNet::httpGet(const QString &url, QByteArray &retdata, const QMap<QNetworkRequest::KnownHeaders,QString> &headerlist, int timeOut){
    SMCCCHttpRequest *_http = new SMCCCHttpRequest;
    _http->setTimeOut(timeOut);
    _http->setHeaderList(headerlist);
    if(!_http->request(url))return -1;
    int code = _http->getHttpStatusCode();
    retdata = _http->getReturnData();
    delete _http;
    return code;
}

int SMCCCNet::httpPost(const QString &url, QByteArray &retdata, const QByteArray &postdata, int timeOut){
    SMCCCHttpRequest *_http = new SMCCCHttpRequest;
    _http->setTimeOut(timeOut);
    _http->setPostData(postdata);
    if(!_http->request(url,1))return -1;
    int code = _http->getHttpStatusCode();
    retdata = _http->getReturnData();
    delete _http;
    return code;
}

int SMCCCNet::httpPost(const QString &url, QByteArray &retdata, const QByteArray &postdata, const QMap<QNetworkRequest::KnownHeaders,QString> &headerlist, int timeOut){
    SMCCCHttpRequest *_http = new SMCCCHttpRequest;
    _http->setTimeOut(timeOut);
    _http->setPostData(postdata);
    _http->setHeaderList(headerlist);
    if(!_http->request(url,1))return -1;
    int code = _http->getHttpStatusCode();
    retdata = _http->getReturnData();
    delete _http;
    return code;
}
