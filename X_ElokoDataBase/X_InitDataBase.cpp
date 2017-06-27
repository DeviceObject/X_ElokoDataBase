#include "stdafx.h"
#include "X_ElokoDataBase.h"
#include "X_MachineConfig.h"
#include "X_InitDataBase.h"

void InitLogin()
{
	hMySqlWin7CheckMd5 = mysql_init(NULL);
	if (!mysql_real_connect(hMySqlWin7CheckMd5,SERVERADDR,SERVERUSER_WIN7,SERVERPWD_WIN7,SERVERDB_WIN7,SERVERPORT,NULL,0))
	{
		MessageBoxW(NULL,L"连接数据库服务器失败Windows 7",L"错误提示",NULL);
	}
	mysql_query(hMySqlWin7CheckMd5,"SET NAMES GBK");

/*	hMySqlWinXpCheckMd5 = mysql_init(NULL);
	if (!mysql_real_connect(hMySqlWinXpCheckMd5,SERVERADDR,SERVERUSER_XP,SERVERPWD_XP,SERVERDB_XP,SERVERPORT,NULL,0))
	{
		MessageBoxW(NULL,L"连接数据库服务器失败Windows Xp",L"错误提示",NULL);
	}
	mysql_query(hMySqlWinXpCheckMd5,"SET NAMES GBK");

	hMySqlWinVistaCheckMd5 = mysql_init(NULL);
	if (!mysql_real_connect(hMySqlWinVistaCheckMd5,SERVERADDR,SERVERUSER_VISTA,SERVERPWD_VISTA,SERVERDB_VISTA,SERVERPORT,NULL,0))
	{
		MessageBoxW(NULL,L"连接数据库服务器失败Windows Vista",L"错误提示",NULL);
	}
	mysql_query(hMySqlWinVistaCheckMd5,"SET NAMES GBK");
*/
	hMySqlSoftWareCheckMd5 = mysql_init(NULL);
	if (!mysql_real_connect(hMySqlSoftWareCheckMd5,SERVERADDR,SERVERUSER_SOFT,SERVERPWD_SOFT,SERVERDB_SOFT,SERVERPORT,NULL,0))
	{
		MessageBoxW(NULL,L"连接数据库服务器失败SoftWare",L"错误提示",NULL);
	}
	mysql_query(hMySqlSoftWareCheckMd5,"SET NAMES GBK");

	hMySqlGameCheckMd5 = mysql_init(NULL);
	if (!mysql_real_connect(hMySqlGameCheckMd5,SERVERADDR,SERVERUSER_GAME,SERVERPWD_GAME,SERVERDB_GAME,SERVERPORT,NULL,0))
	{
		MessageBoxW(NULL,L"连接数据库服务器失败Game",L"错误提示",NULL);
	}
	mysql_query(hMySqlGameCheckMd5,"SET NAMES GBK");
}