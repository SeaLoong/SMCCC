#include "smccchttprequest.h"

SMCCCHttpRequest::SMCCCHttpRequest(QObject *parent) : QObject(parent)
{
    _pTimer = new QTimer(this);
    connect(_pTimer,&QTimer::timeout,this,&SMCCCHttpRequest::slot_requestTimeOut);//超时信号
    _TimeOut = 15000;
    _IsTimeOut = false;
}

void SMCCCHttpRequest::setPostData(const QByteArray &postdata){
    _PostData = postdata;
}

void SMCCCHttpRequest::setHeaderList(const QMap<QNetworkRequest::KnownHeaders,QString> &headerlist){
    _HeaderList = headerlist;
}

void SMCCCHttpRequest::setRawHeaderList(const QMap<QByteArray, QByteArray> &rawheaderlist){
    _RawHeaderList = rawheaderlist;
}

void SMCCCHttpRequest::setTimeOut(int timeout){
    _TimeOut = timeout;
}

bool SMCCCHttpRequest::request(const QString &url,int methon){
    QNetworkRequest netRequest;
    netRequest.setUrl(QUrl(url));//地址信息

    for (QMap<QNetworkRequest::KnownHeaders,QString>::ConstIterator it = _HeaderList.constBegin();it != _HeaderList.constEnd();++it){
        netRequest.setHeader(it.key(),it.value());
    }
    for (QMap<QByteArray,QByteArray>::ConstIterator it = _RawHeaderList.constBegin();it != _RawHeaderList.constEnd();++it){
        netRequest.setRawHeader(it.key(),it.value());
    }
    if(netRequest.header(QNetworkRequest::ContentTypeHeader).isNull()){
        netRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    }
    if(url.toLower().startsWith("https")){//https请求，需ssl支持(下载openssl拷贝libeay32.dll和ssleay32.dll文件至Qt bin目录或程序运行目录)
        QSslConfiguration sslConfig;
        sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);
        sslConfig.setProtocol(QSsl::TlsV1SslV3);
        netRequest.setSslConfiguration(sslConfig);
    }
    if(methon == 1)_NetworkManager.post(netRequest,_PostData);//发起post请求
    else _NetworkManager.get(netRequest);//发起get请求
    connect(&_NetworkManager,&QNetworkAccessManager::finished,this,&SMCCCHttpRequest::slot_requestFinished); //请求完成信号
    _pTimer->start(_TimeOut);
    loop.exec();//事件循环，开始阻塞

    //请求完成或超时都停止阻塞
    _pTimer->deleteLater();
    deleteLater();
    return !_IsTimeOut;
}

int SMCCCHttpRequest::getHttpStatusCode(){
    return _HttpStatusCode;
}

QByteArray SMCCCHttpRequest::getReturnData(){
    return _ReturnData;
}

void SMCCCHttpRequest::slot_requestFinished(QNetworkReply *reply){
    _pTimer->stop();
    _HttpStatusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    _ReturnData = reply->readAll();
    loop.exit();
    reply->deleteLater();
}

void SMCCCHttpRequest::slot_requestTimeOut(){
    _pTimer->stop();
    _IsTimeOut = true;
    loop.exit();
}

