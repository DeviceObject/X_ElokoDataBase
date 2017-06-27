// X_ElokoDataBase.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "X_MachineConfig.h"
#include "X_InitDataBase.h"
#include "X_QueryCheck.h"
#include "X_ServerIocp.h"
#include "X_Time.h"
#include "X_ElokoDataBase.h"

MYSQL *hMySqlWin7CheckMd5;
MYSQL *hMySqlWinXpCheckMd5;
MYSQL *hMySqlWinVistaCheckMd5;
MYSQL *hMySqlSoftWareCheckMd5;
MYSQL *hMySqlGameCheckMd5;


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	InitLogin();
	//BOOL bIsRunFlag;
	CreateThread(NULL,NULL,CheckTimeOut,NULL,NULL,NULL);
	StartIOCPServer();

 	//QueryInfoFromMd5AndSoftWare("ad2b4a14494ecb265b1dfc99b2c6214a","QQ.exe",&bIsRunFlag,NULL);
	return 0;
}