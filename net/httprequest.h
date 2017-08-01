#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkProxy>
#include <QSslConfiguration>
#include <QTimer>
#include <QEventLoop>

class HttpRequest : public QObject
{
    Q_OBJECT
public:
    explicit HttpRequest(QObject *parent = 0);
    //同步数据传输，可能会出现阻塞现象
    bool request(const QString &url,int methon = 0);//0:get  1:post
    void setPostData(const QByteArray &postdata);//设置post提交的数据
    void setHeaderList(const QMap<QNetworkRequest::KnownHeaders,QString> &headerlist);//设置http协议头
    void setRawHeaderList(const QMap<QByteArray,QByteArray> &rawheaderlist);//设置http协议头
    void setTimeOut(int timeout);//设置超时时间
    int getHttpStatusCode();//获取http状态码
    QByteArray getReturnData();//获取返回数据

private slots:
    void slot_requestFinished(QNetworkReply *reply);//http请求结束
    void slot_requestTimeOut();//请求超时

private:
    QNetworkAccessManager _NetworkManager;//网络管理类
    QTimer* _pTimer;//请求超时计时器
    QEventLoop loop;//事件循环

    QMap<QNetworkRequest::KnownHeaders,QString> _HeaderList;
    QMap<QByteArray,QByteArray> _RawHeaderList;

    QByteArray _PostData;
    int _TimeOut;

    bool _IsTimeOut;
    int _HttpStatusCode;
    QByteArray _ReturnData;
};

#endif // HTTPREQUEST_H
