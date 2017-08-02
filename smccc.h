#ifndef SMCCC_H
#define SMCCC_H

#include "smccc_global.h"
#include "smcccjson.h"
#include "smcccauth.h"

class SMCCCSHARED_EXPORT SMCCC
{
public:
    SMCCC();
    SMCCC(const QString &version,const QString &dotminecraftdirpath);
    /// 初始化SMCCC
    /**
      \param 版本名称
      \param .minecraft目录路径
      \return 无返回值
      */

    void setAssetsCheck(bool assetscheck = true);
    /// 设置是否检查Assets资源文件完整，可选设置，默认为true
    /**
      \param 默认为true
      \return 无返回值
      */
    void setFileCheck(bool filecheck = true);
    /// 设置是否对文件进行SHA1和文件大小检查，可选设置，默认为true
    /**
      \param 默认为true
      \return 无返回值
      */
    void setMergeInheritsFrom(bool mergeinheritsfrom = true);
    /// 设置是否对带有InheritsFrom项的Json文件进行文件合并，即将对应的InheritsFrom文件内容合并到当前Json文件并删除InheritsFrom项，可选设置，默认为true
    /**
      \param 默认为true
      \return 无返回值
      */
    void setOS(const QString &os = QString("windows"));
    /// 设置操作系统，可选设置，默认为"windows"
    /**
      \param 可使用的值有"windows","osx","linux"，默认为"windows"
      \return 无返回值
      */
    void setArch(const QString &arch = QString("32"));
    /// 设置操作系统位数，可选设置，默认为"32"
    /**
      \param 可使用的值有"32","64"，默认为"32"
      \return 无返回值
      */
    void setVersion(const QString &version);
    /// 设置版本名称，要求存在对应.minecraft/versions/<Version>/<Version>.json(可自行设置路径)的文件，必须设置
    /**
      \param 版本名称
      \return 无返回值
      */
    void setDotMinecraftDirPath(const QString &dotminecraftdirpath);
    /// 设置.minecraft目录路径，必须设置
    /**
      \param .minecraft目录路径
      \return 无返回值
      */
    void setAssetsDirPath(const QString &assetsdirpath);
    /// 设置assets目录路径，可选设置，默认为.minecraft/assets
    /**
      \param assets目录路径，默认为.minecraft/assets
      \return 无返回值
      */
    void setLibrariesDirPath(const QString &librariesdirpath);
    /// 设置libraries目录路径，可选设置，默认为.minecraft/libraries
    /**
      \param libraries目录路径，默认为.minecraft/libraries
      \return 无返回值
      */
    void setVersionsDirPath(const QString &versionsdirpath);
    /// 设置versions目录路径，可选设置，默认为.minecraft/versions
    /**
      \param versions目录路径，默认为.minecraft/versions
      \return 无返回值
      */
    void setNativesDirPath(const QString &nativesdirpath);
    /// 设置natives目录路径，可选设置，默认为.minecraft/natives/<Version>
    /**
      \param natives目录路径，默认为.minecraft/natives/<Version>
      \return 无返回值
      */
    void setJarFilePath(const QString &jarfilepath);
    /// 设置<Version>.jar文件路径，可选设置，默认为从json文件中自动寻找
    /**
      \param <Version>.jar文件路径，默认为从json文件中自动寻找
      \return 无返回值
      */

    void setAuthMethod(int authmethod = 0);
    /// 设置验证方式：0:Offline,1:Yggdrasil，可选设置，默认为0
    /**
      \param 验证方式，默认为0
      \return 无返回值
      */
    void set_username(const QString &username);
    /// 设置验证用户名，必须设置
    /**
      \param 用户名，验证方式为Offline时，此项为游戏名
      \return 无返回值
      */
    void set_password(const QString &password);
    /// 设置验证密码，可选设置，验证方式为Yggdrasil时，必须设置
    /**
      \param 密码，验证方式为Yggdrasil时有效
      \return 无返回值
      */
    void set_accessToken(const QString &accessToken);
    /// 设置accessToken，可选设置，验证方式为Yggdrasil时有效，可能加快验证速度
    /**
      \param accessToken，验证方式为Yggdrasil时有效
      \return 无返回值
      */
    void set_clientToken(const QString &clientToken);
    /// 设置clientToken，可选设置，验证方式为Yggdrasil时有效
    /**
      \param clientToken，验证方式为Yggdrasil时有效
      \return 无返回值
      */

    void setArgs_AutoConnect(const QString &host,const QString &port);
    /// 设置自动连接服务器，可选设置，默认为空
    /**
      \param 服务器地址
      \param 服务器端口
      \return 无返回值
      */
    void setArgs_Xmx(int xmx = 1024);
    /// 设置Java参数Xmx分配的最大内存，单位为M，可选设置，默认为1024
    /**
      \param 单位为M，默认为1024
      \return 无返回值
      */
    void setArgs_Resolution(int width = 854,int height = 480,bool fullscreen = false);
    /// 设置Mc分辨率及是否全屏，当fullscreen为true时，前两个参数无效，可选设置，默认为854*480，非全屏
    /**
      \param 宽度，默认为854
      \param 高度，默认为480
      \param 是否全屏，默认为false
      \return 无返回值
      */
    void setArgs_VersionType(const QString &versiontype);
    /// 设置Mc版本类型，即在Mc主界面左下角显示的文字，可选设置，默认为从json文件中读取
    /**
      \param 在Mc主界面左下角显示的文字，默认为从json文件中读取
      \return 无返回值
      */
    void setArgs_AdditionArgsJava(const QString &additionArgs);
    /// 设置Java附加参数，可选设置，默认为空
    /**
      \param Java附加参数
      \return 无返回值
      */
    void setArgs_AdditionArgsMc(const QString &additionArgs);
    /// 设置Mc附加参数，可选设置，默认为空
    /**
      \param Mc附加参数
      \return 无返回值
      */

    QString getLaunchArgsString();
    /// 获取SMCCC处理后的启动参数
    /**
      \return 返回QString类型的启动器参数
      */
    QStringList getLaunchArgsStringList();
    /// 获取SMCCC处理后的启动参数
    /**
      \return 返回QStringList类型的启动器参数
      */
    QLinkedList<SMCCCDownloadInfo> getDownloadInfoList();
    /// 获取需要下载的文件信息列表(链表)
    /**
      \return 返回需要下载的文件信息列表
      */
    QString getAuthError();
    /// 获取验证失败的错误代码
    /**
      \return 返回验证失败的错误代码
      */

    int processLaunchArgs();
    /// 处理启动参数，返回处理启动参数失败的代码：
    /// -1:未设置游戏目录/Json文件路径等,
    /// 0:处理成功,
    /// 1:需要下载文件,
    /// 2:Json文件未找到,
    /// 3:InheritsFromJson文件未找到,
    /// 4:Libraries文件未找到,
    /// 5:Json文件错误,
    /// 6:验证失败,
    /// 7:未知错误
    /**
      \return 返回处理启动参数失败的代码
      */
    /*返回值：
     * -1:未设置游戏目录/Json文件路径等,
     * 0:OK,
     * 1:Download,
     * 2:JsonFileNotFound,
     * 3:InheritsFromJsonFileNotFound
     * 4:LibrariesFileNotFound
     * 5:JsonError
     * 6:AuthFaild
     * 7:UnknownError
    */

private:
    SMCCCJson *_Json;
    SMCCCAuth *_Auth;

    QString ArgsString;
    QStringList ArgsStringList;

    int _Step;
    int _args_Xmx;
    int _args_width,_args_height;
    bool _args_fullscreen;
    QString _args_versionType;
    QString _args_host,_args_port;
    QString _args_additionArgsJava;
    QString _args_additionArgsMc;

};

#endif // SMCCC_H
