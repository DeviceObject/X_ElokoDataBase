#include "stdafx.h"
#include "X_ElokoDataBase.h"
#include "X_MachineConfig.h"
#include "X_InitDataBase.h"

void InitLogin()
{
	hMySqlWin7CheckMd5 = mysql_init(NULL);
	if (!mysql_real_connect(hMySqlWin7CheckMd5,SERVERADDR,SERVERUSER_WIN7,SERVERPWD_WIN7,SERVERDB_WIN7,SERVERPORT,NULL,0))
	{
		MessageBoxW(NULL,L"�������ݿ������ʧ��Windows 7",L"������ʾ",NULL);
	}
	mysql_query(hMySqlWin7CheckMd5,"SET NAMES GBK");

/*	hMySqlWinXpCheckMd5 = mysql_init(NULL);
	if (!mysql_real_connect(hMySqlWinXpCheckMd5,SERVERADDR,SERVERUSER_XP,SERVERPWD_XP,SERVERDB_XP,SERVERPORT,NULL,0))
	{
		MessageBoxW(NULL,L"�������ݿ������ʧ��Windows Xp",L"������ʾ",NULL);
	}
	mysql_query(hMySqlWinXpCheckMd5,"SET NAMES GBK");

	hMySqlWinVistaCheckMd5 = mysql_init(NULL);
	if (!mysql_real_connect(hMySqlWinVistaCheckMd5,SERVERADDR,SERVERUSER_VISTA,SERVERPWD_VISTA,SERVERDB_VISTA,SERVERPORT,NULL,0))
	{
		MessageBoxW(NULL,L"�������ݿ������ʧ��Windows Vista",L"������ʾ",NULL);
	}
	mysql_query(hMySqlWinVistaCheckMd5,"SET NAMES GBK");
*/
	hMySqlSoftWareCheckMd5 = mysql_init(NULL);
	if (!mysql_real_connect(hMySqlSoftWareCheckMd5,SERVERADDR,SERVERUSER_SOFT,SERVERPWD_SOFT,SERVERDB_SOFT,SERVERPORT,NULL,0))
	{
		MessageBoxW(NULL,L"�������ݿ������ʧ��SoftWare",L"������ʾ",NULL);
	}
	mysql_query(hMySqlSoftWareCheckMd5,"SET NAMES GBK");

	hMySqlGameCheckMd5 = mysql_init(NULL);
	if (!mysql_real_connect(hMySqlGameCheckMd5,SERVERADDR,SERVERUSER_GAME,SERVERPWD_GAME,SERVERDB_GAME,SERVERPORT,NULL,0))
	{
		MessageBoxW(NULL,L"�������ݿ������ʧ��Game",L"������ʾ",NULL);
	}
	mysql_query(hMySqlGameCheckMd5,"SET NAMES GBK");
}