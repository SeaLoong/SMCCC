#ifndef SMCCCDOWNLOADINFO_H
#define SMCCCDOWNLOADINFO_H

#include <QString>

class SMCCCDownloadInfo
{
public:
    SMCCCDownloadInfo();
    SMCCCDownloadInfo(const QString &_filepath,const QString &_url,const QString &_sha1,int _size);
    QString filepath,url,sha1;
    int size;
};

#endif // SMCCCDOWNLOADINFO_H
