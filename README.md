# SMCCC

一个开源的Minecraft启动器核心库，使用Qt5.9.0编写

## 功能

- 生成Minecraft启动参数(自动连接服务器,内存,分辨率,versionType等)
- 离线/正版验证(Offline,Yggdrasil)
- 可自定义的Assets,Libraries,Versions,Natives目录位置
- Assets,Libraries,版本jar文件检查+文件大小校验+sha1校验
- 获取文件缺失下载列表
- Natives文件自动解压
- 版本Json文件合并继承(inheritsFrom)
- 网络代理设置(http,socket5)

## 不考虑的功能(考虑到Qt跨平台特性等)

- Java位置自动寻找(可以考虑只支持Windows)
- 启动游戏(也许你需要监视游戏程序什么的,所以不带上启动功能)

## 将来可能支持的功能

- 增加对多个下载源的支持
- Versions目录下游戏版本的自动寻找
- 隐藏游戏版本
- 版本隔离
- 其它验证方式的支持

## 如何使用

- 方法1.将Branch切换到demo，有示例代码
- 方法2.
示例：
1. 在.pro文件中加入 Qt += network 确保网络模块启用

2. 将SMCCC库添加到.pro文件中


	LIBS += -L$$PWD/lib/ -lsmccc
	INCLUDEPATH += $$PWD/include
	DEPENDPATH += $$PWD/include


3. 主程序中使用所示代

	...
	#include "smccc.h"
	int main(){
		...
		SMCCC *smccc = new SMCCC;
		smccc->setDotMinecraftDirPath("/.minecraft");
		smccc->setVersion("1.12");
		smccc->set_username("DemoPlayer");
		qDebug()<<smccc->processLaunchArgs();
		qDebug()<<smccc->getLaunchArgsString();//或者smccc->getLaunchArgsStringList();
		...
	}
	

getLaunchArgsString()返回QString类型的启动参数，之后使用QProcess等启动javaw.exe带上此参数即可

- 方法3.将SMCCC库源代码直接加入到工程中使用


## 注意

- Windows下动态编译后，带上SMCCC.dll与zlib1.dll才可运行
- 如果需要其它平台库，请直接用源码在其它平台编译成库或直接使用源码

