#include "smcccdownloadinfo.h"

SMCCCDownloadInfo::SMCCCDownloadInfo(const QString &_filepath, const QString &_url, const QString &_sha1, int _size)
{
    filepath = _filepath,url = _url,sha1 = _sha1,size = _size;
}
